#include "game.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Game::run
///
/// Summary:	script for the ClientGame which defines the actions of each frame.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// event -    	[in,out] the event qeue of the current frame. 
/// window -   	[in,out] The window where the game will be drawn. 
/// isMenu -   	[in,out] Status of the Menu to return into the menu. 
/// inClientGame -   	[in,out] Status of the ClientGame - turns into false for leaving the game. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::run(sf::Event* event, sf::RenderWindow& window, bool& isMenu, bool& inGame, sf::View* mapView)
{
	this->receive(window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		std::cout << "Window Closed in Map via Esc" << std::endl;

		window.close();
	}
	this->moveView(mapView, window);

	while (window.pollEvent(*event))
	{

		//Window closed

		if (event->type == sf::Event::Closed)
		{
			window.close();
		}

		//Mouse moved

		else if (event->type == sf::Event::MouseMoved)
		{
			this->getInteraction(window, mapView);
		}

		//Right mouse button pressed

		else if (event->type == sf::Event::MouseButtonPressed)
		{
			if (event->mouseButton.button == sf::Mouse::Right)
			{
				this->newOrder();
			}
		}

		//text entered

		else if (event->type == sf::Event::TextEntered)
		{
			if (isChat == true)
			{
				this->modifyChat(event->text.unicode);
				
			}
		}

		//Mouse Wheel Scrolled

		else if (event->type == sf::Event::MouseWheelScrolled)
		{
			this->scaleView((int)event->mouseWheelScroll.delta, mapView, window);
		}

		//Left Mouse Button Pressed

		if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
		{
			this->leftMouseButtonPressed(window);

		}
	}

	// draw

	this->draw(window, mapView);

	// Endscreen

	if (isEndscreen == true)
	{
		int endScreenInteraction = endScreen.run();
		if (endScreenInteraction == 1)
		{
			inGame = false;
			isMenu = true;
		}
	}

	//handleWindows

	else
	{
		this->handleWindows(window);

	}

	//MenuInterface

	this->menuInterface(window, inGame, isMenu);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::moveView
///
/// Summary:
/// 	Move the given view if W,A,S or D is pressed. After that the View will get checked by
/// 	checkView().
///
/// Author:	Bennet.
///
/// Date:	02.01.2020.
///
/// Parameters:
/// mapView -  	[in,out] If non-null, the map view. 
/// window -   	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::moveView(sf::View* mapView, sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mapView->move(0, -10);
		this->checkView(mapView, window);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		mapView->move(-10, 0);
		this->checkView(mapView, window);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		mapView->move(0, 10);
		this->checkView(mapView, window);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		mapView->move(10, 0);
		this->checkView(mapView, window);
	}




}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::checkView
///
/// Summary:	Check view wether its in a correct Spot.
///
/// Author:	Bennet
///
/// Date:	02.01.2020
///
/// Parameters:
/// mapView -  	[in,out] If non-null, the map view. 
/// window -   	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::checkView(sf::View* mapView, sf::RenderWindow& window)
{
	if (mapView->getSize().x > 1920)
	{
		mapView->setSize((float)window.getSize().x, (float)window.getSize().y);
		mapView->setCenter((float)window.getSize().x / 2, (float)window.getSize().y / 2);
	}


	while (mapView->getCenter().x - mapView->getSize().x / 2 < 0 || mapView->getCenter().x + mapView->getSize().x / 2 > window.getSize().x)
	{
		if (mapView->getSize().x >= window.getSize().x)
		{
			mapView->setCenter((float)window.getSize().x / 2, (float)window.getSize().y / 2);
		}
		else
		{
			if (mapView->getCenter().x - mapView->getSize().x / 2 < 0)
			{
				mapView->move(sf::Vector2f(5, 0));

			}
			else if (mapView->getCenter().x + mapView->getSize().x / 2 > window.getSize().x)
			{
				mapView->move(sf::Vector2f(-5, 0));
			}
		}
	}

	while (mapView->getCenter().y - mapView->getSize().y / 2 < 0 || mapView->getCenter().y + mapView->getSize().y / 2 > window.getSize().y)
	{
		if (mapView->getSize().x >= window.getSize().x)
		{
			mapView->setCenter((float)window.getSize().x / 2, (float)window.getSize().y / 2);
		}
		else
		{
			if (mapView->getCenter().y - mapView->getSize().y / 2 < 0)
			{
				mapView->move(sf::Vector2f(0, 5));
			}
			else if (mapView->getCenter().y + mapView->getSize().y / 2 > window.getSize().y)
			{
				mapView->move(sf::Vector2f(0, -5));
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::scaleView
///
/// Summary:
/// 	Scale the given view when the mouseWheel was scrolled. After that the View will get
/// 	checked by checkCiew().
///
/// Author:	Bennet.
///
/// Date:	02.01.2020.
///
/// Parameters:
/// mapView -  	[in,out] If non-null, the map view. 
/// window -   	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::scaleView(int delta, sf::View* mapView, sf::RenderWindow& window)
{
	if (delta == 1 && mapView->getSize().x > 1150)
	{
		mapView->zoom((float)0.90);
		
	}
	else if (delta == -1)
	{
		mapView->zoom((float)1.11111);
	}

	this->getInteraction(window, mapView);
	this->checkView(mapView, window);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::getInteraction
///
/// Summary:	Sets the interaction with the map.
///
/// Author:	Bennet
///
/// Date:	02.01.2020
///
/// Parameters:
/// window -   	[in,out] The window. 
/// mapView -  	[in,out] the map view. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::getInteraction(sf::RenderWindow& window, sf::View* mapView)
{
	this->map.resetMapInteraction();
	if (!isChoosing && !isConfirming && !isWarning)
	{
		interaction = this->map.mapInteraction(window, mapView);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ClientGame::newOrder
///
/// Summary:	Creates a new order in the country the interaction is pointing to.
///
/// Author:	Bennet
///
/// Date:	02.01.2020
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::newOrder()
{
	if (interaction != 0)
	{
		Country* country = map.getCountryOfIndex(interaction);
		int currentAmount = map.getCountryOfIndex(interaction)->numberOfFigures;
		map.deleteFigure(interaction, currentAmount);
		if (country->getCity() == true)
		{
			country->deleteFigure(0);
			country->placeFigure(0, sf::Color::White);
		}

		if (country->getCapital() == true)
		{
			country->deleteFigure(-1);
			country->replaceCapital();
		}

		map.placeFigure(interaction, currentAmount, 1, 0);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	LocalGame::checkMissions
///
/// Summary:	Checks every mission wether its completed by the current player.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::checkMissions()
{
	for (int i = 0; i < (int)missionBoard.missions.size(); i++)
	{
		missionBoard.missions[i]->check(this->currentPlayer, this->map.getContinentsOfMap(), citiesBeforeAttacking, countriesBeforeAttacking, continentsWithoutPlayer);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	LocalGame::handleWindows
///
/// Summary:	Handles the windows of the game if their Status is true.
///
/// Author:	Bennet
///
/// Date:	02.01.2020
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::handleWindows(sf::RenderWindow& window)
{
	if (isChoosing)
	{
		this->choosing(window);
	}
	if (isConfirming)
	{
		this->confirming(window);
	}
	if (isWarning)
	{
		if (warning.run(window) == 1)
		{
			isWarning = false;
		}
	}
	if (showCards)
	{
		activePlayer->interactWithCards();
	}
	if (isChat)
	{
		this->chat.run(window);
	}
	if (isRolling)
	{
		this->rollingTheDices();
	}
	if (waitingForCubes)
	{
		this->waitForCubes();
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	LocalGame::changeMode
///
/// Summary:	Determines if we can change mode and changes it if true.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	True if it succeeds, false if it fails.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Game::changeMode()
{

	if (isFirstRound == true)
	{
		if (figuresToPlace == 0)
		{
			this->changePlayer();

			if (currentPlayerIndex == firstPlayerIndex)
			{
				isFirstRound = false;
				figuresToPlace = currentPlayer->getAmountOfFigures(this->map.getContinentsOfMap());
			}
			else
			{
				figuresToPlace = firstFiguresToPlace;
			}

			this->bar.changeFiguresToPlace(figuresToPlace);
		}
		else
		{
			return false;
		}
	}
	else
	{

		isChoosing = false;
		isConfirming = false;
		isWarning = false;

		this->modeStatus = 0;

		if (placeMode == true)
		{
			if (figuresToPlace == 0)
			{
				placeMode = false;
				attackMode = true;
			}
			else
			{
				return false;
			}
		}

		else if (attackMode == true)
		{
			attackMode = false;
			moveMode = true;
		}
		else if (moveMode == true)
		{
			moveMode = false;
			placeMode = true;
			this->map.resetIsMoved();

			this->changePlayer();
		}
		this->topBar.changeMode();
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	LocalGame::changePlayer
///
/// Summary:
/// 	Changes the currentplayer and resets the important informations for every turn of a
/// 	player.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::changePlayer()
{
	if (!isFirstRound)
	{
		this->checkMissions();
	}
	this->currentPlayer->resetGetCard();
	if (this->missionBoard.hasWon(this->currentPlayer))
	{
		endScreen.setEndScreen(currentPlayer->getUsername(), currentPlayer->getColor());

		isEndscreen = true;
	}
	else {

		do {
			this->currentPlayerIndex++;
			if (this->currentPlayerIndex >= (int)this->players.size())
			{
				this->currentPlayerIndex = 0;
			}
		} while (players[currentPlayerIndex]->getIsEliminated() == true);

		this->currentPlayer = this->players[this->currentPlayerIndex];

		this->changeActivePlayer();

		this->topBar.setCurrentUsername(currentPlayer->getUsername(), currentPlayer->getColor());

	}
	figuresToPlace = currentPlayer->getAmountOfFigures(this->map.getContinentsOfMap());

	citiesBeforeAttacking = currentPlayer->amountOfCities();

	countriesBeforeAttacking = currentPlayer->amountOfCountries();

	continentsWithoutPlayer.clear();

	this->map.getContinentsWithoutPlayer(currentPlayer, &continentsWithoutPlayer);

	this->bar.changeFiguresToPlace(figuresToPlace);
}


void Game::placeCapital(int location)
{
	//place capital


	this->map.getCountryOfIndex(location)->giveCapital(currentPlayer->getColor());
	this->topBar.giveNews(currentPlayer->getUsername() + " is placing the capital in "  + map.getCountryOfIndex(location)->getName() + "."); /////////////////////////



	interaction = 0;


	//change Player

	this->currentPlayerIndex++;
	if (this->currentPlayerIndex >= (int)this->players.size())
	{
		this->currentPlayerIndex = 0;
	}
	this->currentPlayer = this->players[this->currentPlayerIndex];


	this->topBar.setCurrentUsername(currentPlayer->getUsername(), currentPlayer->getColor());


	if (currentPlayerIndex == firstPlayerIndex)
	{
		placeCapitals = false;
		isFirstRound = true;
	}

}