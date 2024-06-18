#include "gameMenu.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	GameMenu::GameMenu
///
/// Summary:	Default constructor of the main inGame Menu.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

GameMenu::GameMenu()
{
	texture.loadFromFile("pictures/pergament.png");
	shape.setTexture(texture);

	shape.setOrigin(sf::Vector2f(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2));
	shape.setPosition(sf::Vector2f(960, 540));

	font.loadFromFile("Lato-Regular.ttf");

	option[0].setString("Resume");
	option[1].setString("Sound : on");
	option[2].setString("");
	option[3].setString("Quit");

	for (int i = 0; i < 4; i++)
	{
		option[i].setFillColor(sf::Color::Black);
		option[i].setFont(font);
		option[i].setCharacterSize(40);
		option[i].setOrigin(sf::Vector2f(option[i].getGlobalBounds().width / 2, option[i].getGlobalBounds().height / 2));
		option[i].setPosition(sf::Vector2f(shape.getGlobalBounds().left + shape.getGlobalBounds().width / 2, shape.getGlobalBounds().top + 120 + i * 80));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	GameMenu::resetInteraction
///
/// Summary:	Resets the interaction in the menu.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void GameMenu::resetInteraction()
{
	for (int i = 0; i < 4; i++)
	{
		option[i].setFillColor(sf::Color::Black);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	GameMenu::getInteraction
///
/// Summary:	Gets the interaction for the menu_options.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	The interaction.
////////////////////////////////////////////////////////////////////////////////////////////////////

int GameMenu::getInteraction()
{
	for (int i = 0; i < 4; i++)
	{
		if (option[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
		{
			option[i].setFillColor(sf::Color::Red);
			return i;
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	GameMenu::run
///
/// Summary:	script for the GameMenu which defines the actions of each frame.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	the interaction when the mouse is pressed.
////////////////////////////////////////////////////////////////////////////////////////////////////

int GameMenu::run()
{
	this->resetInteraction();
	int interaction = this->getInteraction();

	if (!button && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		button = true;
	}
	else if (button && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		button = false;
		for (int i = 0; i < 4; i++)
		{
			if (interaction == i)
			{
				if (i == 1)
				{
					if (option[1].getString() == "Sound : on")
					{
						option[1].setString("Sound : off");
					}
					else
					{
						option[1].setString("Sound : on");
					}

				}
				return i;
			}
		}
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	GameMenu::draw
///
/// Summary:	Draws the gameMenu in the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void GameMenu::draw(sf::RenderWindow& window)
{
	window.draw(shape);

	for (int i = 0; i < 4; i++)
	{
		window.draw(option[i]);
	}
}
