#include "hostGame.h"

HostGame::HostGame() { 

	fightSound.setVolume(0.88);

	afterFight.loadFromFile("Sound/Explosion.wav");
	fightSound.setBuffer(afterFight);

	useCardsSound.loadFromFile("Sound/UseCard.wav");
	cardSound.setBuffer(useCardsSound);

	newMessageSound.loadFromFile("Sound/Receive.wav");
	messageSound.setBuffer(newMessageSound);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	HostGame::startGame
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

void HostGame::startGame(int amountOfPlayerValue, std::vector<std::string>* username, std::vector<sf::Color>* playerColor, std::vector<sf::TcpSocket*> sockets, int indexOfHost)
{
	sf::Packet received;
	clients = sockets;
	

	

	this->areAllReady();



	received.clear();

	this->rollTheDice.start();
	this->missionBoard.start(sf::Vector2f(50, 600));
	this->figureBoard.start(sf::Vector2f(1235, 890));
	this->map.start();

	for (int i = 0; i < amountOfPlayerValue; i++)
	{
		players.push_back(new Player(playerColor->at(i), username->at(i)));
		this->topBar.givePlayerBox(players[i]);
	}



	this->map.givePlayers(&players);

	firstFiguresToPlace = this->map.distributeCountries((int) players.size());
	figuresToPlace = firstFiguresToPlace;
	currentPlayerIndex = rand() % (int) players.size();
	currentPlayerIndex = 1; ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::Packet packet;

	packet << currentPlayerIndex << figuresToPlace;

	this->sendToAll(packet);

	packet.clear();


	

	this->areAllReady();

	


	for (int i = 0; i < this->map.getNumberOfCountries(); i++)
	{
		Country* country = this->map.getCountryOfIndex(i + 1);
		int indexOfOwner = country->indexOfOwner;

		packet << i << indexOfOwner;

		this->sendToAll(packet);
		packet.clear();

	}


	this->bar.changeFiguresToPlace(figuresToPlace);

	firstPlayerIndex = currentPlayerIndex;
	currentPlayer = players[currentPlayerIndex];
	activePlayer = players[indexOfHost];

	citiesBeforeAttacking = currentPlayer->amountOfCities();
	countriesBeforeAttacking = currentPlayer->amountOfCountries();

	continentsWithoutPlayer.clear();
	this->map.getContinentsWithoutPlayer(currentPlayer, &continentsWithoutPlayer);

	this->topBar.setCurrentUsername(currentPlayer->getUsername(), currentPlayer->getColor());




	this->areAllReady();

	int missionIndex[8];

	for (int i = 0; i < 8; i++)
	{
		missionIndex[i] = this->missionBoard.getIndexOfMission(i);
		packet << missionIndex[i];
	}

	this->sendToAll(packet);
	packet.clear();


	help.start();


}



////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	HostGame::confirming
///
/// Summary:	Runs the confirmWindow and acting with the return value depending on the current Mode.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void HostGame::confirming(sf::RenderWindow& window)
{
	int confirmInteraction = confirm.run(window);

	if (attackMode == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && confirmInteraction == 1)
		{
			int start = map.chooseStart;
			int destination = map.chooseGoal;
			int amount = map.chooseAmount;

			if (map.getCountryOfIndex(start)->numberOfFigures - attackerAmount < 1)
			{
				isWarning = true;
				warning.placeWarning("You cant attack", "with this amount", "of units!!", window);
			}
			else
			{
				if (map.getCountryOfIndex(destination)->numberOfFigures >= 2)
				{
					defenderAmount = 2;
				}
				else
				{
					defenderAmount = 1;
				}




				std::string action = "willAttack";
				sf::Packet broadcast;
				broadcast << action << start << attackerAmount << destination << defenderAmount;
				this->sendToAll(broadcast);
				broadcast.clear();
				this->topBar.giveNews(currentPlayer->getUsername() + " is attacking " + map.getCountryOfIndex(destination)->getName() + " from " + map.getCountryOfIndex(start)->getName() + " with " + std::to_string(attackerAmount) + " figures."); /////////////////////////

				isRolling = true;
				this->rollTheDice.setAmountOfCubes(attackerAmount);
				waitingForCubes = true;

			}


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
			if (this->map.move() == 1)
			{
				isWarning = true;
				warning.placeWarning("you cant", "move this amount", "of units!!", window);
			}
			else
			{
				std::string action = "move";
				int amount = map.chooseAmount;
				int destination = map.chooseGoal;
				int start = map.chooseStart;
				sf::Packet broadcast;
				broadcast << action << amount << destination << start;
				this->sendToAll(broadcast);
				broadcast.clear();
				this->topBar.giveNews(currentPlayer->getUsername() + " is moving " + std::to_string(amount) + " figures from " + map.getCountryOfIndex(start)->getName() + " to " + map.getCountryOfIndex(destination)->getName()); /////////////////////////

			}
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
			//place capital


			int location = interaction;
			this->placeCapital(interaction);
			std::string action = "placeCapital";
			sf::Packet broadcast;
			broadcast << action << location;
			this->sendToAll(broadcast);
			broadcast.clear();

			interaction = 0;

			isConfirming = false;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && confirmInteraction == 2)
		{
			isConfirming = false;
			interaction = 0;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	HostGame::choosing
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

void HostGame::choosing(sf::RenderWindow& window)
{

	int amountValue = choosingHelp.run(window);

	if (placeMode == true)
	{
		if (amountValue != -1)
		{
			int destination = map.chooseStart;
			if (this->map.placeFigure(-1, amountValue, 0, figuresToPlace) == false)
			{
				isWarning = true;
				warning.placeWarning("you cant place", "this amount", "of units!!", window);
			}
			else
			{
				figuresToPlace -= amountValue;
				this->bar.changeFiguresToPlace(figuresToPlace);
				this->topBar.giveNews(currentPlayer->getUsername() + " is placing " + std::to_string(amountValue) + " figures in " + map.getCountryOfIndex(destination)->getName()); /////////////////////////


				
				sf::Packet broadcast;
				std::string action = "place";
				broadcast << action << destination << amountValue;
				this->sendToAll(broadcast);
				broadcast.clear();
			}
			isChoosing = false;
			interaction = 0;
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
/// Function:	HostGame::menuInterface
///
/// Summary:	Interacting with the top and bottom bar of the menu.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window -   	[in,out] The window. 
/// inHostGame -   	[in,out] True to in game. 
/// isMenu -   	[in,out] True if is menu, false if not. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void HostGame::menuInterface(sf::RenderWindow& window, bool& inGame, bool& isMenu)
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
				int worthOfCards = activePlayer->useCards();
				if (worthOfCards != -1)
				{
					int amount = this->figureBoard.getWorth(worthOfCards);
					this->figuresToPlace += amount;
					this->bar.changeFiguresToPlace(figuresToPlace);
					showCards = false;

					std::string action = "useCards";
					sf::Packet broadcast;
					broadcast << action << amount;
					this->sendToAll(broadcast);
					broadcast.clear();

					cardSound.play();


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
		else if (menuInteraction == 4 && placeCapitals == false)
		{
			if (this->changeMode() == false)
			{
				isWarning = true;
				warning.placeWarning("You have", "to place", "all Units!!", window);
			}
			else
			{
				sf::Packet broadcast;
				std::string action = "changeMode";
				broadcast << action;
				this->sendToAll(broadcast);
				broadcast.clear();
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	HostGame::draw
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

void HostGame::draw(sf::RenderWindow& window, sf::View* mapView)
{
	if (isEndscreen == false)
	{
		window.setView(*mapView);

		map.draw(window);
		if (showCards == true)
		{
			window.setView(window.getDefaultView());
			activePlayer->showCards(window);
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
/// Function:	HostGame::leftMouseButtonPressed
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

void HostGame::leftMouseButtonPressed(sf::RenderWindow& window)
{
	if (activePlayer == currentPlayer)
	{
		if (!isWarning && !showCards && interaction != 0 && !isChoosing && !isEndscreen && !isChat && !placeCapitals && !isGameMenu)
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


void HostGame::sendToAll(sf::Packet packet)
{

	for (auto i : clients)
	{

		if (i != NULL)
		{
			sf::Socket::Status status = i->send(packet);

			while (status == sf::Socket::Partial)
			{
				status = i->send(packet);
			}
		}
	}
}




void HostGame::areAllReady()
{
	bool goForwards = false;
	sf::Packet received;
	std::string status;

	while (goForwards == false)
	{
		for (auto i : clients)
		{
			if (i != NULL)
			{
				if (i->receive(received) != sf::Socket::NotReady)
				{
					received >> status;
					received.clear();
					if (status == "ready")
					{
						goForwards = true;

					}
				}
			}
		}
	}
}



void HostGame::runPlaceMode()
{
	if (currentPlayer->isYourCountry(map.getCountryOfIndex(interaction)))
	{
		map.chooseStart = interaction;
		this->choosingHelp.placeAmount(1, this->map.getCountryOfIndex(interaction)->getName(), "place", figuresToPlace);
		isChoosing = true;
		interaction = 0;
	}
}

void HostGame::runAttackMode(sf::RenderWindow& window)
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

void HostGame::runMoveMode(sf::RenderWindow& window)
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


void HostGame::receive(sf::RenderWindow& window)
{
	std::string action;
	sf::Packet received;
	for (auto i : clients)
	{
		if (i != NULL)
		{
			
			if (i->receive(received) != sf::Socket::NotReady)
			{
				received >> action;


				if (action == "place" )
				{
					int destination;
					int amount;

					received >> destination >> amount;


					if (this->map.placeFigure(destination, amount, 0, figuresToPlace) == false)
					{
						sf::Packet answer;
						std::string request = "placeRequest";
						std::string result = "wrong";
						answer << request << result;
						i->send(answer);
						answer.clear();
					}
					else
					{

						figuresToPlace -= amount;
						this->bar.changeFiguresToPlace(figuresToPlace);

						sf::Packet broadcast;
						broadcast << action << destination << amount;
						this->sendToAll(broadcast);
						broadcast.clear();
						this->topBar.giveNews(currentPlayer->getUsername() + " is placing " + std::to_string(amount) + " figures in " + map.getCountryOfIndex(destination)->getName()); /////////////////////////

					}

				}
				else if (action == "attack" )
				{
					int amount;
					int destination;
					int start;

					received >> amount >> destination >> start;

					map.chooseAmount = amount;
					map.chooseGoal = destination;
					map.chooseStart = start;
					
					attackerAmount = amount;

					if (this->map.getCountryOfIndex(this->map.chooseGoal)->numberOfFigures >= 2)
					{
						this->defenderAmount = 2;
					}
					else
					{
						this->defenderAmount = 1;

					}




					if (map.getCountryOfIndex(start)->numberOfFigures - attackerAmount < 1)
					{
						sf::Packet answer;
						std::string request = "attackRequest";
						std::string result = "wrong";
						answer << request << result;
						i->send(answer);
						answer.clear();
					}
					else
					{
						sf::Packet broadcast;
						action = "willAttack";

						broadcast << action << start << attackerAmount << destination << defenderAmount;
						this->sendToAll(broadcast);
						broadcast.clear();
						this->topBar.giveNews(currentPlayer->getUsername() + " is attacking " + map.getCountryOfIndex(destination)->getName() + " from " + map.getCountryOfIndex(start)->getName() + " with " + std::to_string(amount) + " figures."); /////////////////////////
						if (activePlayer->isYourCountry(this->map.getCountryOfIndex(destination)))
						{
							isRolling = true;
							this->rollTheDice.setAmountOfCubes(defenderAmount);
						}
						
						waitingForCubes = true;
					}
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

					if (this->map.move() == 1)
					{
						sf::Packet answer;
						std::string request = "attackRequest";
						std::string result = "wrong";
						answer << request << result;
						i->send(answer);
						answer.clear();
					}
					else
					{
						sf::Packet broadcast;
						broadcast << action << amount << destination << start;
						this->sendToAll(broadcast);
						broadcast.clear();
						this->topBar.giveNews(currentPlayer->getUsername() + " is moving " + std::to_string(amount) + " figures from " + map.getCountryOfIndex(start)->getName() + " to " + map.getCountryOfIndex(destination)->getName()); /////////////////////////

					}

				}
				else if (action == "changeMode")
				{
					if (this->changeMode())
					{
						sf::Packet broadcast;
						broadcast << action;
						this->sendToAll(broadcast);
						broadcast.clear();
					}
				}
				else if (action == "placeCapital")
				{
					int location;
					received >> location;

					this->placeCapital(location);

					sf::Packet broadcast;
					broadcast << action << location;
					this->sendToAll(broadcast);
					broadcast.clear();


				}
				else if (action == "useCards")
				{
					int amount;
					received >> amount;

					figuresToPlace += amount;
					this->bar.changeFiguresToPlace(figuresToPlace);

					this->topBar.giveNews(currentPlayer->getUsername() + " gets " + std::to_string(amount) + " figures by using cards.");


					sf::Packet broadcast;
					broadcast << action << amount;
					this->sendToAll(broadcast);
					broadcast.clear();


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

					sf::Packet broadcast;
					broadcast << action << username << r << g << b << message;
					this->sendToAll(broadcast);
					broadcast.clear();

					messageSound.play();

				}
				else if (action == "attacker")
				{
					int value;

					for (int i = 0; i < attackerAmount; i++)
					{
						received >> value;
						cubesOfAttacker.push_back(value);
					}
				}
				else if (action == "defender")
				{
					int value;

					for (int i = 0; i < defenderAmount; i++)
					{
						received >> value;
						std::cout << value << std::endl;
						cubesOfDefender.push_back(value);
					}
				}
			}
		}
	}

	received.clear();

}


void HostGame::modifyChat(sf::Uint32 unicode)
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

		messageSound.play();

		this->chat.newNetworkMessage(username, sf::Color(r, g, b), message);

		this->sendToAll(packet);

		packet.clear();
	}

}


void HostGame::rollingTheDices()
{
	std::vector<int>* results = this->rollTheDice.run();

	if (results != NULL)
	{
		if (activePlayer == currentPlayer)
		{
			for (int i = 0; i < attackerAmount; i++)
			{
				cubesOfAttacker.push_back(results->at(i));
				std::cout << cubesOfAttacker[i] << std::endl;
			}
			this->rollTheDice.setAmountOfCubes(defenderAmount);
		}
		else
		{
			for (int i = 0; i < defenderAmount; i++)
			{
				cubesOfDefender.push_back(results->at(i));
				std::cout << cubesOfDefender[i] << std::endl;
			}
		}
		isRolling = false;
	}
	
}

void HostGame::waitForCubes()
{
	if (cubesOfAttacker.size() != 0 && cubesOfDefender.size() != 0)
	{
		std::sort(cubesOfAttacker.begin(), cubesOfAttacker.end(), std::greater<int>());
		std::sort(cubesOfDefender.begin(), cubesOfDefender.end(), std::greater<int>());

		int count = 0;

		if (cubesOfAttacker.size() >= cubesOfDefender.size())
		{
			count = (int)cubesOfDefender.size();
		}
		else
		{
			count = (int)cubesOfAttacker.size();
		}


		int lossOfAttacker = 0;
		int lossOfDefender = 0;

		for (int i = 0; i < count; i++)
		{
			std::cout << cubesOfAttacker[i] << " (attacker) vs. (defender) " << cubesOfDefender[i] << std::endl;

			if (cubesOfAttacker[i] > cubesOfDefender[i])
			{
				lossOfDefender++;
			}
			else
			{
				lossOfAttacker++;
			}
		}

		for (int i = 0; i < lossOfAttacker; i++)
		{
			map.getCountryOfIndex(map.chooseStart)->explode();
		}
		for (int i = 0; i < lossOfDefender; i++)
		{
			map.getCountryOfIndex(map.chooseGoal)->explode();
		}

		this->map.deleteFigure(map.chooseStart, lossOfAttacker);
		this->map.deleteFigure(map.chooseGoal, lossOfDefender);

		cubesOfAttacker.clear();
		cubesOfDefender.clear();

		if (map.getCountryOfIndex(map.chooseGoal)->numberOfFigures == 0)
		{
			Country* defending = map.getCountryOfIndex(map.chooseGoal);
			Player* defender = players.at(defending->indexOfOwner);
			int indexOfDefender = defending->indexOfOwner;
			this->map.deleteFigure(map.chooseStart, map.chooseAmount);
			this->map.takePossesion(map.chooseGoal, map.chooseAmount, currentPlayer);

			this->topBar.giveNews(currentPlayer->getUsername() + " conquered " + map.getCountryOfIndex(map.chooseGoal)->getName() + ".");


			if (currentPlayer == activePlayer)
			{
				activePlayer->getCard();
			}
			if (defender->amountOfCountries() == 0)
			{
				this->topBar.giveNews(defender->getUsername() + "is eliminated!!");


				defender->eliminate();

			}
		}

		std::string action = "attack";
		int start = map.chooseStart;
		int destination = map.chooseGoal;
		int amount = attackerAmount;

		sf::Packet broadcast;

		broadcast << action << start << lossOfAttacker << destination << lossOfDefender << amount;

		this->sendToAll(broadcast);

		fightSound.play();


		isRolling = false;
		waitingForCubes = false;

	}
}