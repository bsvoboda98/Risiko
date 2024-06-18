#include "menu.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Menu::Menu
///
/// Summary:	Constructor which is placing the Menu options in the window above the background.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// width -    	The width of the window. 
/// height -   	The height of the window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

Menu::Menu(float width, float height) { //Constructor, creates the main Menu

	backgroundtexture.loadFromFile("pictures/Mainmenu_Background.jpg");
	background.setTexture(backgroundtexture);



	if (!font.loadFromFile("SIXTY.ttf")) {
		//handle Error
	}

	
	//set the title of the Menu "RISIKO"
	text[0].setFont(font);
	text[0].setFillColor(sf::Color(150, 0, 0));
	text[0].setString("RISIKO");
	text[0].setPosition(sf::Vector2f((width / 2) - 150, (height / (MAX_NUMBER_OF_ITEMS - 1) * 1) - 50));
	text[0].setCharacterSize(100);


	//reads the following menu options out of a .txt
	std::ifstream file;
	std::string line;
	file.open("text/menu/menu.txt");
	int i = 1;
	for (int i = 1; i <= 4; i++)
	{
		std::getline(file, line);
		text[i].setFont(font);
		text[i].setString(line);
		text[i].setPosition(sf::Vector2f((width / 2) - 150, height / (MAX_NUMBER_OF_ITEMS - 1) * (i + 1)));
		text[i].setCharacterSize(50);
	}

	for (int i = 0; i < 2; i++)
	{
		std::getline(file, line);
		text[i + 5].setFont(font);
		text[i + 5].setString(line);
		text[i + 5].setPosition(sf::Vector2f(text[2].getPosition().x + text[2].getGlobalBounds().width + 50, text[2].getPosition().y - text[2].getGlobalBounds().height + i * 2 * text[2].getGlobalBounds().height));
		text[i + 5].setCharacterSize(50);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Menu::run
///
/// Summary:
/// 	Runs a frame of the menu. first gets the interaction and acting if the Mousebutton was
/// 	pressed.
///
/// Author:	Bennet.
///
/// Date:	04.01.2020.
///
/// Parameters:
/// window - 	  	[in,out] The window. 
/// event - 	  	[in,out] If non-null, the event. 
/// lobby - 	  	[in,out] If non-null, the lobby. 
/// clientLobby - 	[in,out] If non-null, the client lobby. 
/// gameMode -    	[in,out] The game mode. 
/// isMenu - 	  	[in,out] True if is menu, false if not. 
/// isLobby - 	  	[in,out] True if is lobby, false if not. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Menu::run(sf::RenderWindow& window, sf::Event* event, Lobby** lobby, int& gameMode, bool& isMenu, bool& isLobby)
{
		
	while (window.pollEvent(*event))
	{
		if (event->type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event->type == sf::Event::TextEntered)
		{
			if (lookForConnection == true)
			{
				std::string ipAddress = this->prompt.textEntered(event->text.unicode);
				if (ipAddress != "")
				{
					if (ipAddress == "ESC")
					{
						lookForConnection = false;
					}
					else
					{
						lookForConnection = false;
						*lobby = new ClientLobby();
						bool startStatus = (*lobby)->startLobby(ipAddress);
						if (startStatus)
						{
							gameMode = 2;
							isMenu = false;
							isLobby = true;
						}
						else
						{
							//lobby = new MainLobby();
						}
						
					}
				}
			}
		}
	}

	this->resetMenuIntersection();
	option = this->getMenuIntersection(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPressed == false)
	{
		isPressed = true;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPressed == true)
	{
		isPressed = false;
		if (option != -1)
		{
			if (lookForConnection == false)
			{
				if (option == 1)
				{
					//Singleplayer
					isMenu = false;
					gameMode = 0;
					*lobby = new MainLobby();
					(*lobby)->startLobby(gameMode);
					isLobby = true;
				}
				else if (option == 2)
				{
					//Multiplayer
					if (chooseMultiplayer == false)
					{
						chooseMultiplayer = true;
					}
					else
					{
						chooseMultiplayer = false;
					}
				}
				else if (option == 3)
				{
					//Options
				}
				else if (option == 4)
				{
					//Quit
					window.close();
				}
				else if (option == 5)
				{
					//Host
					isMenu = false;
					gameMode = 1;
					*lobby = new MainLobby();
					(*lobby)->startLobby(gameMode);
					isLobby = true;
				}
			}
			if (option == 6)
			{
				//Connect
				if (lookForConnection == false)
				{
					lookForConnection = true;
				}
				else
				{
					lookForConnection = false;
				}
			}
		}

	}
	this->draw(window);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Menu::draw
///
/// Summary:	Draws the menu into the window.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(background);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS - 2; i++) {
		window.draw(text[i]);
	}

	if (chooseMultiplayer == true)
	{
		for (int i = MAX_NUMBER_OF_ITEMS - 2; i < MAX_NUMBER_OF_ITEMS; i++) {
			window.draw(text[i]);
		}
	}

	if(lookForConnection == true)
	{
		this->prompt.draw(window);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Menu::getMenuIntersection
///
/// Summary:	Gets the interaction with the menu options.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	[in,out] The window. 
///
/// Returns:	the number for the option over which the mouse is hovering.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Menu::getMenuIntersection(sf::RenderWindow& window) {
	sf::Vector2i position2i = sf::Mouse::getPosition(window);
	sf::Vector2f position2f = sf::Vector2f(position2i);
	for (int i = 1; i < MAX_NUMBER_OF_ITEMS - 2; i++) {
		if (text[i].getGlobalBounds().contains(position2f)) {
			text[i].setFillColor(sf::Color(150, 0, 0));
			return i;
		}
	}
	if (chooseMultiplayer == true)
	{
		for (int i = MAX_NUMBER_OF_ITEMS - 2; i < MAX_NUMBER_OF_ITEMS; i++) {
			if (text[i].getGlobalBounds().contains(position2f)) {
				text[i].setFillColor(sf::Color(150, 0, 0));
				return i;
			}
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Menu::resetMenuIntersection
///
/// Summary:	Resets the menu interaction described by option.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// option - 	The menu option which is choosen. 
///
/// Returns:	resets the option to no option choosed.
////////////////////////////////////////////////////////////////////////////////////////////////////

void Menu::resetMenuIntersection() {
	for (int i = 1; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		text[i].setFillColor(sf::Color::White);
	}
}

