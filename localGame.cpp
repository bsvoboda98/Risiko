#include "localGame.h"



LocalGame::LocalGame() {

	fightSound.setVolume(0.88);

	afterFight.loadFromFile("Sound/Explosion.wav");
	fightSound.setBuffer(afterFight);

	useCardsSound.loadFromFile("Sound/UseCard.wav");
	cardSound.setBuffer(useCardsSound);

	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	LocalGame::startGame
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

void LocalGame::startGame(int amountOfPlayerValue, std::vector<std::string>* username, std::vector<sf::Color>* playerColor)
{
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

	firstFiguresToPlace = this->map.distributeCountries(static_cast<int>(players.size()));
	figuresToPlace = firstFiguresToPlace;
	this->bar.changeFiguresToPlace(figuresToPlace);


	currentPlayerIndex = rand() % static_cast<int>(players.size());
	firstPlayerIndex = currentPlayerIndex;
	currentPlayer = players[currentPlayerIndex];
	activePlayer = currentPlayer;

	citiesBeforeAttacking = currentPlayer->amountOfCities();
	countriesBeforeAttacking = currentPlayer->amountOfCountries();

	continentsWithoutPlayer.clear();
	this->map.getContinentsWithoutPlayer(currentPlayer, &continentsWithoutPlayer);

	
	this->topBar.setCurrentUsername(currentPlayer->getUsername(), currentPlayer->getColor());
	help.start();

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	LocalGame::confirming
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

void LocalGame::confirming(sf::RenderWindow& window)
{
	int confirmInteraction = confirm.run(window);

	if (attackMode == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && confirmInteraction == 1)
		{
			int fill1 = 0;
			int fill2 = 0;

			if (map.getCountryOfIndex(map.chooseStart)->numberOfFigures - attackerAmount < 1)
			{
				isWarning = true;
				warning.placeWarning("You cant attack", "with this amount", "of units!!", window);
			}
			else
			{
				this->topBar.giveNews(currentPlayer->getUsername() + " is attacking " + map.getCountryOfIndex(map.chooseGoal)->getName() + " from " + map.getCountryOfIndex(map.chooseStart)->getName() + " with " + std::to_string(map.chooseAmount) + " figures."); /////////////////////////
				this->rollTheDice.setAmountOfCubes(attackerAmount);


				if (this->map.getCountryOfIndex(this->map.chooseGoal)->numberOfFigures >= 2)
				{
					this->defenderAmount = 2;
				}
				else
				{
					this->defenderAmount = 1;

				}

				isRolling = true;
				rollingStatus = 1;
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
				this->topBar.giveNews(currentPlayer->getUsername() + " is moving " + std::to_string(map.chooseAmount) + " figures from " + map.getCountryOfIndex(map.chooseStart)->getName() + " to " + map.getCountryOfIndex(map.chooseGoal)->getName()); /////////////////////////

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

			this->placeCapital(interaction);
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
/// Function:	LocalGame::choosing
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

void LocalGame::choosing(sf::RenderWindow& window)
{

	int amountValue = choosingHelp.run(window);

	if (placeMode == true)
	{
		if (amountValue != -1)
		{

			if (this->map.placeFigure(-1, amountValue, 0, figuresToPlace) == false)
			{
				isWarning = true;
				warning.placeWarning("you cant place", "this amount", "of units!!", window);
			}
			else
			{
				figuresToPlace -= amountValue;
				this->bar.changeFiguresToPlace(figuresToPlace);
				this->topBar.giveNews(currentPlayer->getUsername() + " is placing " + std::to_string(amountValue) + " figures in " + map.getCountryOfIndex(map.chooseStart)->getName()); /////////////////////////

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
			this->attackerAmount = amountValue;
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
/// Function:	LocalGame::menuInterface
///
/// Summary:	Interacting with the top and bottom bar of the menu.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window -   	[in,out] The window. 
/// inLocalGame -   	[in,out] True to in game. 
/// isMenu -   	[in,out] True if is menu, false if not. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void LocalGame::menuInterface(sf::RenderWindow& window, bool& inGame, bool& isMenu)
{
	int menuInteraction = bar.run();
	if(this->topBar.run(window) == 1)
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
			}
			else
			{
				fightSound.setVolume(0);
				cardSound.setVolume(0);
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
			if (showCards && placeMode)
			{
				int worthOfCards = currentPlayer->useCards();
				if (worthOfCards != -1)
				{
					int amount = this->figureBoard.getWorth(worthOfCards);
					this->figuresToPlace += amount;
					this->bar.changeFiguresToPlace(figuresToPlace);
					showCards = false;
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
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	LocalGame::draw
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

void LocalGame::draw(sf::RenderWindow& window, sf::View* mapView)
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
/// Function:	LocalGame::leftMouseButtonPressed
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

void LocalGame::leftMouseButtonPressed(sf::RenderWindow& window)
{
	if (!isWarning && !showCards && interaction != 0 && !isChoosing && !isEndscreen && !isChat && !placeCapitals && !isRolling && !isGameMenu)
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
	else if (placeCapitals == true && !isConfirming && interaction != 0 && !isRolling)
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

void LocalGame::changeActivePlayer()
{
	this->activePlayer = this->currentPlayer;
}


void LocalGame::runPlaceMode()
{
	if (currentPlayer->isYourCountry(map.getCountryOfIndex(interaction)))
	{
		map.chooseStart = interaction;
		this->choosingHelp.placeAmount(1, this->map.getCountryOfIndex(interaction)->getName(), "place", figuresToPlace);
		isChoosing = true;
		interaction = 0;
	}
}

void LocalGame::runAttackMode(sf::RenderWindow& window)
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

void LocalGame::runMoveMode(sf::RenderWindow& window)
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

void LocalGame::modifyChat(sf::Uint32 unicode)
{
	this->chat.textEntered(unicode, activePlayer->getUsername(), activePlayer->getColor());
}


void LocalGame::rollingTheDices()
{
	std::vector<int>* results = this->rollTheDice.run();

	if (results != NULL)
	{
		if (rollingStatus == 1)
		{
			for (int i = 0; i < attackerAmount; i++)
			{
				cubesOfAttacker.push_back(results->at(i));
				std::cout << cubesOfAttacker[i] << std::endl;
			}
			rollingStatus = 2;
			this->rollTheDice.setAmountOfCubes(defenderAmount);
		}
		else if (rollingStatus == 2)
		{
			for (int i = 0; i < defenderAmount; i++)
			{
				cubesOfDefender.push_back(results->at(i));
				std::cout << cubesOfDefender[i] << std::endl;
			}
			rollingStatus = 0;
			isRolling = false;
			

			std::sort(cubesOfAttacker.begin(), cubesOfAttacker.end(), std::greater<int>());
			std::sort(cubesOfDefender.begin(), cubesOfDefender.end(), std::greater<int>());

			int count = 0;


			if (cubesOfAttacker.size() >= cubesOfDefender.size())
			{
				count = (int) cubesOfDefender.size();
			}
			else
			{
				count = (int) cubesOfAttacker.size();
			}


			int lossOfAttacker = 0;
			int lossOfDefender = 0;

			for (int i = 0; i < count; i++)
			{
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

			
			fightSound.play();

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
		}
	}
}