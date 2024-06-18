#include "menuTopBar.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::MenuTopBar
///
/// Summary:	Default constructor which creates the TopBar.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

MenuTopBar::MenuTopBar()
{
	font.loadFromFile("Lato-Regular.ttf");
	for (int i = 0; i < 12; i++)
	{
		hoverStats[i].setFont(font);
		hoverStats[i].setCharacterSize(15);

	}
	hoverShape.setSize(sf::Vector2f(150, 150));
	hoverShape.setFillColor(sf::Color(100, 100, 100, 235));


	currentUsername.setFont(font);
	currentMode.setFont(font);
	news.setFont(font);

	barTexture.loadFromFile("pictures/bottom_wood_bar.jpg");
	bar.setTexture(barTexture);

	menuButtonTexture.loadFromFile("pictures/menuButton.png");
	menuButton.setTexture(menuButtonTexture);
	menuButton.setPosition(sf::Vector2f(bar.getGlobalBounds().width - menuButton.getGlobalBounds().width - 10, bar.getGlobalBounds().height / 2 - menuButton.getGlobalBounds().height / 2));

	currentMode.setCharacterSize(35);
	currentMode.setString("placing");
	currentMode.setPosition(sf::Vector2f(bar.getPosition().x + 5, bar.getPosition().y));

	currentUsername.setCharacterSize(35);
	currentUsername.setString("");
	currentUsername.setPosition(sf::Vector2f(menuButton.getPosition().x - 30 - currentUsername.getGlobalBounds().width, 0));

	news.setCharacterSize(35);
	news.setString("");
	news.setPosition(currentMode.getPosition().x + currentMode.getGlobalBounds().width + 60, 5);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::givePlayerBox
///
/// Summary:	adds a player box to the top bar which the color of the given player.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// player - 	[in,out] If non-null, the player. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuTopBar::givePlayerBox(Player* player)
{
	players.push_back(player);

	int i = (int)playerBoxes.size();
	playerBoxes.push_back(sf::RectangleShape());
	playerBoxes[i].setSize(sf::Vector2f(40, 40));
	playerBoxes[i].setPosition(sf::Vector2f(currentMode.getPosition().x + currentMode.getGlobalBounds().width + 60 + 2 * i * 50, 5));
	playerBoxes[i].setFillColor(players[i]->getColor());
	news.move(sf::Vector2f(50, 0)); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::setCurrentUsername
///
/// Summary:	Sets current username.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// username - 	The new username. 
/// color -    	The color of the player with this username. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuTopBar::setCurrentUsername(std::string username, sf::Color color)
{
	currentUsername.setString(username);
	currentUsername.setPosition(sf::Vector2f(menuButton.getPosition().x - 30 - currentUsername.getGlobalBounds().width, 0));
	currentUsername.setFillColor(color);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::changeMode
///
/// Summary:	Changes the mode.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuTopBar::changeMode()
{
	if (currentMode.getString() == "placing")
	{
		currentMode.setString("attacking");
	}
	else if (currentMode.getString() == "attacking")
	{
		currentMode.setString("moving");
	}
	else if (currentMode.getString() == "moving")
	{
		currentMode.setString("placing");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::showStats
///
/// Summary:	Shows the statistics of the player of the playerBox the mouse is pointing on.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// index - 	index of the playerBox. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuTopBar::showStats(int index)
{
	if (index == -1)
	{
		hoverShape.setPosition(sf::Vector2f(0, 0));
	}
	else
	{
		if (hoverShape.getPosition() != sf::Vector2f(playerBoxes[index].getPosition().x, 50))
		{
			hoverShape.setPosition(sf::Vector2f(playerBoxes[index].getPosition().x, 50));
			hoverShape.setSize(sf::Vector2f(150, 150));
			hoverStats[0].setString("Username");
			hoverStats[1].setString(":  " + players[index]->getUsername());
			hoverStats[2].setString("Countries");
			hoverStats[3].setString(":  " + std::to_string(players[index]->amountOfCountries()));
			hoverStats[4].setString("Cities");
			hoverStats[5].setString(":  " + std::to_string(players[index]->amountOfCities()));
			hoverStats[6].setString("Figures");
			hoverStats[7].setString(":  " + std::to_string(players[index]->amountOfFigures()));
			hoverStats[8].setString("Cards");
			hoverStats[9].setString(":  " + std::to_string(players[index]->amountOfCards()));
			hoverStats[10].setString("Missions");
			hoverStats[11].setString(":  " + std::to_string(players[index]->missions));
		}

		for (int i = 0; i < 12; i += 2)
		{
			hoverStats[i].setPosition(sf::Vector2f(hoverShape.getPosition().x + 5, 50 + i * 10 + 20));
			hoverStats[i + 1].setPosition(sf::Vector2f(hoverStats[i].getPosition().x + 75, hoverStats[i].getPosition().y));
		}

		if (hoverStats[1].getPosition().x + hoverStats[1].getGlobalBounds().width + 5 - hoverShape.getPosition().x > 150)
		{
			hoverShape.setSize(sf::Vector2f(hoverStats[1].getPosition().x + hoverStats[1].getGlobalBounds().width + 5 - hoverShape.getPosition().x, hoverShape.getSize().y));
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::giveNews
///
/// Summary:	adds a message to the NewsFeed.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// message - 	The message. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuTopBar::giveNews(std::string message)
{
	messages.push_back(message);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::run
///
/// Summary:	script of the TopBar which defines the actions of each frame.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	[in,out] The window. 
///
/// Returns:	the interaction when the mouse is pressed.
////////////////////////////////////////////////////////////////////////////////////////////////////

int MenuTopBar::run(sf::RenderWindow& window)
{
	if (clock.getElapsedTime().asSeconds() > 5.5 && messages.size() != 0)
	{
		news.setString(messages[0]);
		news.setPosition(sf::Vector2f(playerBoxes[playerBoxes.size() - 1].getPosition().x + (currentUsername.getPosition().x - playerBoxes[playerBoxes.size() - 1].getPosition().x) / 2 - news.getGlobalBounds().width / 2, 5));
		messages.erase(messages.begin());
		clock.restart();
	}



	this->resetInteraction();
	int interaction = this->getInteraction();

	
	this->showStats(hover);

	
	if(interaction > 5)
	{
		if (!button && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			button = true;
		}
		else if (button && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			button = false;

			if (interaction != -1)
			{

				if (interaction == 6)
				{
					return 1;
				}
				
			}

		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::getInteraction
///
/// Summary:	Gets the interaction of the MenuTopBar.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	The interaction.
////////////////////////////////////////////////////////////////////////////////////////////////////

int MenuTopBar::getInteraction()
{
	sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	hover = -1;


	if (menuButton.getGlobalBounds().contains(position))
	{
		menuButton.setColor(sf::Color::Red);
		return 6;
	}
	else
	{
		for (int i = 0; i < (int)playerBoxes.size(); i++)
		{
			if (playerBoxes[i].getGlobalBounds().contains(position))
			{
				hover = i;
				return i;
			}
		}
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::resetInteraction
///
/// Summary:	Resets the interaction of the topBar.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuTopBar::resetInteraction()
{
	menuButton.setColor(sf::Color::White);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuTopBar::draw
///
/// Summary:	Draws the menuTopBar in the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuTopBar::draw(sf::RenderWindow& window)
{
	window.draw(bar);
	window.draw(currentMode);
	window.draw(currentUsername);

	for (auto& i : playerBoxes)
	{
		window.draw(i);
	}

	if (hover != -1)
	{
		window.draw(hoverShape);
		for (int i = 0; i < 12; i++)
		{
			window.draw(hoverStats[i]);
		}
	}

	if (clock.getElapsedTime().asSeconds() < 5.5)
	{
		window.draw(news);
	}

	window.draw(menuButton);
}




