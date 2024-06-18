#include "clientGame.h"
ClientGame::ClientGame() { 

	fightSound.setVolume(0.88);

	afterFight.loadFromFile("Sound/Explosion.wav");
	fightSound.setBuffer(afterFight);

	useCardsSound.loadFromFile("Sound/UseCard.wav");
	cardSound.setBuffer(useCardsSound);

	newMessageSound.loadFromFile("Sound/Receive.wav");
	messageSound.setBuffer(newMessageSound);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::startGame
///
/// Summary:	Starts the game with the information from the lobby.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// amountOfPlayerValue - 	The amount of players. 
/// username - 			  	[in,out] a vector with the usernames of every player. 
/// playerColor - 		  	[in,out] a vector with the colors of every player. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void ClientGame::startGame(int amountOfPlayerValue, std::vector<std::string>* username, std::vector<sf::Color>* playerColor, sf::TcpSocket* socket, int indexOfClient)
{
	

	host = socket;
	this->figureBoard.start(sf::Vector2f(1235, 890));
	this->map.start();

	for (int i = 0; i < amountOfPlayerValue; i++)
	{
		players.push_back(new Player(playerColor->at(i), username->at(i)));
		this->topBar.givePlayerBox(players[i]);
	}

	this->map.givePlayers(&players);

	
	
	
	
	//////////////////////////////////////////////////////////////////////////////////
	
	
	host->setBlocking(true);
	sf::Packet received;
	
	std::string check = "ready"; 

	received << check;

	sf::Socket::Status status = host->send(received);
	while (status == sf::Socket::Partial)
	{
		status = host->send(received);
	}



	received.clear();

	host->receive(received);

	int startPlayer;
	int toPlace;


	received >> startPlayer >> toPlace;


	firstFiguresToPlace = toPlace;
	figuresToPlace = firstFiguresToPlace;
	currentPlayerIndex = startPlayer;
	firstPlayerIndex = currentPlayerIndex;

	received.clear();

	check = "ready";
	received << check;
	status = host->send(received);
	while (status == sf::Socket::Partial)
	{
		status = host->send(received);
	}
	received.clear();
	
	
	host->setBlocking(false);
	
	bool hasAllCountries = false;
	while (!hasAllCountries)
	{
		if (host->receive(received) != sf::Socket::NotReady)
		{
			int index;
			int indexOfOwner;

			received >> index >> indexOfOwner;

			players[indexOfOwner]->giveCountry(this->map.getCountryOfIndex(index + 1));
			this->map.getCountryOfIndex(index + 1)->indexOfOwner = indexOfOwner;
			this->map.placeFigure(index + 1, 1, 1, 0);
			received.clear();
		}

		hasAllCountries = true;

		for (int i = 1; i <= this->map.getNumberOfCountries(); i++)
		{
			if (this->map.getCountryOfIndex(i)->indexOfOwner == -1)
			{
				hasAllCountries = false;
			}
		}
	}



	
	
	this->bar.changeFiguresToPlace(figuresToPlace);
	

	currentPlayer = players[currentPlayerIndex];
	activePlayer = players[indexOfClient]; 

	citiesBeforeAttacking = currentPlayer->amountOfCities();
	countriesBeforeAttacking = currentPlayer->amountOfCountries();


	continentsWithoutPlayer.clear();
	this->map.getContinentsWithoutPlayer(currentPlayer, &continentsWithoutPlayer);


	this->topBar.setCurrentUsername(currentPlayer->getUsername(), currentPlayer->getColor());

	

	check = "ready";
	received << check;
	status = host->send(received);
	while (status == sf::Socket::Partial)
	{
		status = host->send(received);
	}
	received.clear();

	host->setBlocking(true);

	host->receive(received);
	int missionsIndex[8];
	for (int i = 0; i < 8; i++)
	{
		received >> missionsIndex[i];
	}

	this->rollTheDice.start();
	this->missionBoard.startWithMissions(sf::Vector2f(50, 600), missionsIndex);


	host->setBlocking(false);

	help.start();




}




void ClientGame::confirming(sf::RenderWindow& window)
{
	int confirmInteraction = confirm.run(window);

	if (attackMode == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && confirmInteraction == 1)
		{
			
			sf::Packet packet;
			std::string action = "attack";
			int amount = map.chooseAmount;
			int destination = map.chooseGoal;
			int start = map.chooseStart;
			packet << action << amount << destination << start;
			sf::Socket::Status status = host->send(packet);
			while (status == sf::Socket::Partial)
			{
				status = host->send(packet);
			}
			packet.clear();
			
			this->modeStatus = 0;
			isConfirming = false;
			interaction = 0;


			
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && confirmInteraction == 2)
		{
			this->modeStatus = 0;
			isConfirming = false;
			interaction = 0;
		}
	}
	else if (moveMode == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && confirmInteraction == 1)
		{

			sf::Packet packet;
			std::string action = "move";
			int amount = map.chooseAmount;
			int destination = map.chooseGoal;
			int start = map.chooseStart;
			packet << action << amount << destination << start;
			sf::Socket::Status status = host->send(packet);
			while (status == sf::Socket::Partial)
			{
				status = host->send(packet);
			}
			packet.clear();

			
			this->modeStatus = 0;
			isConfirming = false;
			interaction = 0;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && confirmInteraction == 2)
		{
			this->modeStatus = 0;
			isConfirming = false;
			interaction = 0;
		}
	}
	else if (placeMode == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && confirmInteraction == 1)
		{
			sf::Packet packet;
			std::string action = "placeCapital";
			int location = interaction;
			packet << action << location;
			sf::Socket::Status status = host->send(packet);
			while (status == sf::Socket::Partial)
			{
				status = host->send(packet);
			}
			packet.clear();
			isConfirming = false;
			interaction = 0;

		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && confirmInteraction == 2)
		{
			isConfirming = false;
			interaction = 0;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::choosing
///
/// Summary:	Runs the chooseWindow and acting with the return value depending on the current Mode.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void ClientGame::choosing(sf::RenderWindow& window)
{

	int amountValue = choosingHelp.run(window);

	if (placeMode == true)
	{
		if (amountValue != -1)
		{
			
			sf::Packet packet;
			std::string action = "place";
			
			int destination = map.chooseStart;
			int amount = amountValue;
			
			packet << action << destination << amount;
			
			sf::Socket::Status status = host->send(packet);
			while (status == sf::Socket::Partial)
			{
				status = host->send(packet);
			}
			isChoosing = false;
			interaction = 0;


			packet.clear();
			
			
			
		}
	}
	else if (attackMode == true)
	{
		if (amountValue == 0)
		{
			isChoosing = false;
			interaction = 0;
		}
		else if (amountValue != -1)
		{
			this->map.chooseAmount = amountValue;
			this->modeStatus = 1;
			isChoosing = false;
			interaction = 0;
		}
	}
	else if (moveMode == true)
	{
		if (amountValue != -1)
		{
			this->map.chooseAmount = amountValue;
			this->modeStatus = 1;
			isChoosing = false;
			interaction = 0;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::menuInterface
///
/// Summary:	Interacting with the top and bottom bar of the menu.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window -   	[in,out] The window. 
/// inClientGame -   	[in,out] True to in game. 
/// isMenu -   	[in,out] True if is menu, false if not. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void ClientGame::menuInterface(sf::RenderWindow& window, bool& inGame, bool& isMenu)
{
	int menuInteraction = bar.run();
	if (this->topBar.run(window) == 1)
	{

		if (isGameMenu == false)
		{
			isGameMenu = true;
		}
		else
		{
			isGameMenu = false;
		}

	}
	else if (isGameMenu == true)
	{
		int gameMenuInteraction = this->gameMenu.run();

		if (gameMenuInteraction == 0)
		{
			isGameMenu = false;
		}
		else if (gameMenuInteraction == 1)
		{
			if (fightSound.getVolume() == 0.0)
			{
				fightSound.setVolume(0.88);
				cardSound.setVolume(1);
				messageSound.setVolume(1);
			}
			else
			{
				fightSound.setVolume(0);
				cardSound.setVolume(0);
				messageSound.setVolume(0);
			}
		}
		else if (gameMenuInteraction == 2)
		{
			//später save Menu öffnen
		}
		else if (gameMenuInteraction == 3)
		{
			inGame = false;
			isMenu = true;
		}
	}
	else if (menuInteraction != -1)
	{
		if (menuInteraction == 1)
		{
			if (activePlayer->amountOfCards() > 0)
			{
				if (showCards == true)
				{
					showCards = false;
				}
				else
				{
					showCards = true;
				}
			}
		}
		else if (menuInteraction == 2)
		{
			if (showCards && placeMode && activePlayer == currentPlayer)
			{
				int worthOfCards = currentPlayer->useCards();
				if (worthOfCards != -1)
				{
					int amount = this->figureBoard.getWorth(worthOfCards);
					this->figuresToPlace += amount;
					this->bar.changeFiguresToPlace(figuresToPlace);

					sf::Packet packet;
					std::string action = "useCards";
					packet << action << amount;
					
					sf::Socket::Status status = host->send(packet);
					while (status == sf::Socket::Partial)
					{
						status = host->send(packet);
					}

					showCards = false;
				}
				else
				{
					isWarning = true;
					warning.placeWarning("You cant use", "this amount", "of Cards!!", window);
				}
			}
		}
		else if (menuInteraction == 3)
		{
			if (isChat == false)
			{
				isChat = true;
			}
			else
			{
				isChat = false;
			}
		}
		else if (menuInteraction == 4 && placeCapitals == false && activePlayer == currentPlayer)
		{
			if (figuresToPlace != 0)
			{
				isWarning = true;
				warning.placeWarning("You have", "to place", "all Units!!", window);
			}
			else if (waitingForCubes)
			{
				return;
			}
			else
			{
				sf::Packet packet;
				std::string action = "changeMode";
				packet << action;
				sf::Socket::Status status = host->send(packet);
				while (status == sf::Socket::Partial)
				{
					status = host->send(packet);
				}
				packet.clear();
			}
		}
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::draw
///
/// Summary:	Draws the game into the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void ClientGame::draw(sf::RenderWindow& window, sf::View* mapView)
{
	if (isEndscreen == false)
	{
		window.setView(*mapView);

		map.draw(window);
		if (showCards == true)
		{
			window.setView(window.getDefaultView());
			currentPlayer->showCards(window);
			window.setView(*mapView);
		}
		figureBoard.draw(window);
		missionBoard.draw(window);

		window.setView(window.getDefaultView());

		bar.draw(window, placeMode);
		topBar.draw(window);

		if (isRolling)
		{
			this->rollTheDice.draw(window);
		}

		if (isGameMenu)
		{
			gameMenu.draw(window);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !isChat)
		{
			help.draw(window);
		}

	}
	else
	{
		endScreen.draw(window);
	}

}



////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::leftMouseButtonPressed
///
/// Summary:	When the Left mouse button pressed this will be done.
///
/// Author:	Bennet
///
/// Date:	02.01.2020
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void ClientGame::leftMouseButtonPressed(sf::RenderWindow& window)
{
	if (activePlayer == currentPlayer)
	{
		if (!isWarning && !showCards && interaction != 0 && !isChoosing && !isEndscreen && !isChat && !placeCapitals && !waitingForCubes && !isGameMenu)
		{
			if (placeMode == true)
			{
				if (figuresToPlace != 0)
				{
					this->runPlaceMode();
				}
			}
			else if (attackMode == true)
			{
				this->runAttackMode(window);
			}
			else if (moveMode == true)
			{
				this->runMoveMode(window);
			}
		}
		else if (placeCapitals == true && !isConfirming && interaction != 0)
		{
			if (currentPlayer->isYourCountry(this->map.getCountryOfIndex(interaction)))
			{
				isConfirming = true;
				this->confirm.placeConfirm("Do you want", "to place your", "capital here?", window);
			}
		}
		else if (showCards == true)
		{
			this->currentPlayer->clickOnCard();
		}
	}
}


void ClientGame::runPlaceMode()
{
	if (currentPlayer->isYourCountry(map.getCountryOfIndex(interaction)))
	{
		map.chooseStart = interaction;
		this->choosingHelp.placeAmount(1, this->map.getCountryOfIndex(interaction)->getName(), "place", figuresToPlace);
		isChoosing = true;
		interaction = 0;
	}
}

void ClientGame::runAttackMode(sf::RenderWindow& window)
{
	if (modeStatus == 1)
	{
		if (!currentPlayer->isYourCountry(map.getCountryOfIndex(interaction)) && map.getCountryOfIndex(map.chooseStart)->isNeighbor(interaction))
		{
			map.chooseGoal = interaction;
			modeStatus = 2;
			isConfirming = true;
			confirm.placeConfirm("Do you want", "to attack", map.getCountryOfIndex(map.chooseGoal)->getName() + "?", window);
		}
		else if (currentPlayer->isYourCountry(map.getCountryOfIndex(interaction)))
		{
			modeStatus = 0;
			interaction = 0;

		}
	}
	else if (modeStatus == 0)
	{
		if (currentPlayer->isYourCountry(map.getCountryOfIndex(interaction)) == true)
		{
			map.chooseStart = interaction;
			isChoosing = true;
			choosingHelp.placeAmount(1, this->map.getCountryOfIndex(interaction)->getName(), "choose", 3);

		}
	}
}

void ClientGame::runMoveMode(sf::RenderWindow& window)
{
	if (modeStatus == 0)
	{
		if (currentPlayer->isYourCountry(map.getCountryOfIndex(interaction)) == true)
		{
			map.chooseStart = interaction;
			choosingHelp.placeAmount(1, this->map.getCountryOfIndex(interaction)->getName(), "choose", map.getCountryOfIndex(map.chooseStart)->numberOfFigures);
			isChoosing = true;
		}
	}
	else if (modeStatus == 1)
	{
		if (currentPlayer->isYourCountry(map.getCountryOfIndex(interaction)) != 0 && map.getCountryOfIndex(interaction)->isNeighbor(map.chooseStart))
		{
			map.chooseGoal = interaction;
			modeStatus = 2;
			isConfirming = true;
			confirm.placeConfirm("Do you want to move", std::to_string(map.chooseAmount), "Units?", window);

		}
		else if (!currentPlayer->isYourCountry(map.getCountryOfIndex(interaction)))
		{
			modeStatus = 0;
			interaction = 0;
		}
	}
}


void ClientGame::receive(sf::RenderWindow& window)
{
	std::string action;
	sf::Packet received;
	
	if (host->receive(received) != sf::Socket::NotReady)
	{
		received >> action;

		if (action == "place")
		{
			int destination;
			int amount;

			received >> destination >> amount;

			std::cout << destination << ";" << amount << std::endl;


			if (this->map.placeFigure(destination, amount, 0, figuresToPlace))
			{
				figuresToPlace -= amount;
				this->bar.changeFiguresToPlace(figuresToPlace);
				this->topBar.giveNews(currentPlayer->getUsername() + " is placing " + std::to_string(amount) + " figures in " + map.getCountryOfIndex(destination)->getName()); /////////////////////////

			}
				
		}
		else if (action == "attack")
		{
			int lossOfAttacker;
			int lossOfDefender;
			int destination;
			int start;
			int amount;

			received >> start >> lossOfAttacker >> destination >> lossOfDefender >> amount; 

			
			this->topBar.giveNews(currentPlayer->getUsername() + " is attacking " + map.getCountryOfIndex(destination)->getName() + " from " + map.getCountryOfIndex(start)->getName() + " with " + std::to_string(amount) + " figures."); /////////////////////////

			for (int i = 0; i < lossOfAttacker; i++)
			{
				map.getCountryOfIndex(start)->explode();
			}
			for (int i = 0; i < lossOfDefender; i++)
			{
				map.getCountryOfIndex(destination)->explode();
			}

			this->map.deleteFigure(start, lossOfAttacker);
			this->map.deleteFigure(destination, lossOfDefender);
			
			if (map.getCountryOfIndex(destination)->numberOfFigures == 0)
			{
				Country* defending = map.getCountryOfIndex(destination);
				Player* defender = players.at(defending->indexOfOwner);
				int indexOfDefender = defending->indexOfOwner;
				this->map.deleteFigure(start, amount);
				this->map.takePossesion(destination, amount, currentPlayer);

				this->topBar.giveNews(currentPlayer->getUsername() + " conquered " + map.getCountryOfIndex(destination)->getName() + "."); /////////////////////////


				if (currentPlayer == activePlayer)
				{
					activePlayer->getCard();
				}
				if (defender->amountOfCountries() == 0)
				{
					this->topBar.giveNews(defender->getUsername() + "is eliminated!!"); /////////////////////////


					defender->eliminate();

				}
			}

			waitingForCubes = false;
			fightSound.play();

		}
		else if (action == "move")
		{
			int amount;
			int destination;
			int start;

			received >> amount >> destination >> start;

			map.chooseAmount = amount;
			map.chooseGoal = destination;
			map.chooseStart = start;

			this->map.move();
			this->topBar.giveNews(currentPlayer->getUsername() + " is moving " + std::to_string(amount) + " figures from " + map.getCountryOfIndex(start)->getName() + " to " + map.getCountryOfIndex(destination)->getName()); /////////////////////////

		}
		else if (action == "changeMode")
		{
			this->changeMode();
		}
		else if (action == "placeCapital")
		{
			int location;
			received >> location;

			this->placeCapital(location);
		}
		else if (action == "placeRequest")
		{
			std::string result;
			received >> result;
			if (result == "wrong")
			{
				isWarning = true;
				warning.placeWarning("you cant place", "this amount", "of units!!", window);
			}
		}
		else if (action == "attackRequest")
		{
			std::string result;
			received >> result;
			if (result == "wrong")
			{
				isWarning = true;
				warning.placeWarning("You cant attack", "with this amount", "of units!!", window);
			}
		}
		else if (action == "moveRequest")
		{
			std::string result;
			received >> result;
			if (result == "wrong")
			{
				isWarning = true;
				warning.placeWarning("you cant", "move this amount", "of units!!", window);
			}
		}
		else if (action == "useCards")
		{
			int amount;
			received >> amount;
			if (currentPlayer != activePlayer)
			{

				figuresToPlace += amount;
				this->bar.changeFiguresToPlace(figuresToPlace);
				received.clear();


			}

			this->topBar.giveNews(currentPlayer->getUsername() + " gets " + std::to_string(amount) + " figures by using cards."); 

			cardSound.play();

		}
		else if (action == "newMessage")
		{
			std::string username;
			int r;
			int g;
			int b;
			std::string message;

			received >> username >> r >> g >> b >> message;

			this->chat.newNetworkMessage(username, sf::Color(r, g, b), message);

			messageSound.play();
		}
		else if (action == "willAttack")
		{
			int start;
			int destination;
			int amount;
			
			received >> start >> attackerAmount >> destination >> defenderAmount;

			if (activePlayer->isYourCountry(map.getCountryOfIndex(start)))
			{
				isRolling = true;
				this->rollTheDice.setAmountOfCubes(attackerAmount);
			}
			else if (activePlayer->isYourCountry(map.getCountryOfIndex(destination)))
			{
				isRolling = true;
				this->rollTheDice.setAmountOfCubes(defenderAmount);
			}
			waitingForCubes = true;

		}
	}

	received.clear();

}


void ClientGame::modifyChat(sf::Uint32 unicode)
{
	if (unicode != 13)
	{
		this->chat.textEntered(unicode, activePlayer->getUsername(), activePlayer->getColor());
	}
	else
	{
		std::string action = "newMessage";
		std::string message = this->chat.getMessageForSending();
		std::string username = activePlayer->getUsername();
		int r = activePlayer->getColor().r;
		int g = activePlayer->getColor().g;
		int b = activePlayer->getColor().b;

		sf::Packet packet;
		packet << action << username << r << g << b << message;


		sf::Socket::Status status = host->send(packet);
		while (status == sf::Socket::Partial)
		{
			status = host->send(packet);
		}
		packet.clear();
	}
}

void ClientGame::rollingTheDices()
{
	std::vector<int>* results = this->rollTheDice.run();

	if (results != NULL)
	{
		if (activePlayer == currentPlayer)
		{
			for (int i = 0; i < attackerAmount; i++)
			{
				cubesOfAttacker.push_back(results->at(i));
			}
			
			sf::Packet packet;
			std::string action = "attacker";
			packet << action;
			for (int i = 0; i < attackerAmount; i++)
			{
				packet << cubesOfAttacker[i];
			}
			sf::Socket::Status status = host->send(packet);
			while (status == sf::Socket::Partial)
			{
				status = host->send(packet);
			}
			packet.clear();
			cubesOfAttacker.clear();
		}
		else
		{
			for (int i = 0; i < defenderAmount; i++)
			{
				cubesOfDefender.push_back(results->at(i));
			}
			sf::Packet packet;
			std::string action = "defender";
			packet << action;
			for (int i = 0; i < defenderAmount; i++)
			{
				packet << cubesOfDefender[i];
			}
			sf::Socket::Status status = host->send(packet);
			while (status == sf::Socket::Partial)
			{
				status = host->send(packet);
			}
			packet.clear();
			cubesOfDefender.clear();

		}

		isRolling = false;
	}
}

void ClientGame::waitForCubes()
{

}