#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "localGame.h"
#include "hostGame.h"
#include "clientGame.h"
#include "clientLobby.h"
#include "mainLobby.h"

int main()
{
	std::ofstream file;
	sf::Event event;

	
					///////////////////////////////////////////////////////////////////////////
					///////              Window & Zustände     ////////////////////////////////
					///////////////////////////////////////////////////////////////////////////

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Risiko", sf::Style::Fullscreen);
	sf::View mapView = window.getDefaultView();

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	bool isMenu = true;
	bool inGame = false;
	bool isPressed = false;
	bool isLobby = false;


	int gameMode = 0;

					///////////////////////////////////////////////////////////////////////////
					///////              ProgramObjects      //////////////////////////////////
					///////////////////////////////////////////////////////////////////////////

	Menu menu(window.getSize().x, window.getSize().y);

	Game* game = NULL;

	Lobby* lobby = NULL;


					///////////////////////////////////////////////////////////////////////////
					///////               MAP EINLESEN             ////////////////////////////
					///////////////////////////////////////////////////////////////////////////
	bool drawMode = false;

	if (drawMode == true)
	{
		
		file.open("text/world_map/fill.txt");
		
	}


	///////////////////////////////////////////////////////////////////////////
	///////               WINDOW START             ////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		window.clear(sf::Color(144, 218, 225));

	///////////////////////////////////////////////////////////////////////////
	///////               MENÜ                     ////////////////////////////
	///////////////////////////////////////////////////////////////////////////
		if (isMenu == true)
		{
			menu.run(window, &event, &lobby, gameMode, isMenu, isLobby);
		}

	///////////////////////////////////////////////////////////////////////////
	///////               MAP DEFINIEREN           ////////////////////////////
	///////////////////////////////////////////////////////////////////////////

		if (drawMode == true)
		{
			
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPressed == true)
			{
				isPressed = false;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPressed == false)
			{
				isPressed = true;
				file << sf::Mouse::getPosition(window).x << "," << sf::Mouse::getPosition(window).y << std::endl;
				
			}
		}



	///////////////////////////////////////////////////////////////////////////
	///////               MAP             /////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
		if (isLobby == true)
		{
			lobby->run(window, &event, &game, isLobby, inGame);
		}



		if (inGame == true)
		{
			game->run(&event, window, isMenu, inGame, &mapView);
		}
		//everything that was drawn since the last clear will be drawn in the window
		window.display();
	}



	return 0;
}


