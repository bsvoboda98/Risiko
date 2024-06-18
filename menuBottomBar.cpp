#include "menuBottomBar.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuBottomBar::MenuBottomBar
///
/// Summary:	Default constructor which is placing the bottomBar in the window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

MenuBottomBar::MenuBottomBar()
{
	font.loadFromFile("Lato-Regular.ttf");
	texture.loadFromFile("pictures/bottom_wood_bar.jpg");
	bar.setTexture(texture);
	bar.setPosition(0, 1030);


	for (int i = 0; i < 5; i++)
	{
		menuElements[i].setFont(font);
		menuElements[i].setFillColor(sf::Color::White);
		menuElements[i].setCharacterSize(35);
	}

	menuElements[0].setString("Figures : 0");
	menuElements[0].setPosition(bar.getPosition().x + bar.getGlobalBounds().width * 0.01,
								bar.getPosition().y + 5);


	menuElements[1].setString("Show cards");
	menuElements[1].setPosition(menuElements[0].getPosition().x + menuElements[0].getGlobalBounds().width + 260,
								menuElements[0].getPosition().y);


	menuElements[2].setString("Use selected cards");
	menuElements[2].setPosition(menuElements[1].getPosition().x + menuElements[1].getGlobalBounds().width + 260,
								menuElements[0].getPosition().y);


	menuElements[3].setString("Chat");
	menuElements[3].setPosition(menuElements[2].getPosition().x + menuElements[2].getGlobalBounds().width + 260,
								menuElements[0].getPosition().y);


	menuElements[4].setString("Continue");
	menuElements[4].setPosition(bar.getPosition().x + bar.getGlobalBounds().width * 0.99 - menuElements[4].getGlobalBounds().width,
								menuElements[0].getPosition().y);


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuBottomBar::run
///
/// Summary:	script which runs the MenuBottomBar, gets the interaction and returns.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	returns the interactionValue when the mouse is pressed.
////////////////////////////////////////////////////////////////////////////////////////////////////

int MenuBottomBar::run()
{
	this->resetInteraction();
	int interaction = this->getInteraction();

	if (interaction != 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isButtonPressed)
	{
		isButtonPressed = true;
	}
	else if (isButtonPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && interaction != 0)
	{
		isButtonPressed = false;
		return interaction;
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuBottomBar::getInteraction
///
/// Summary:	Gets the interactionValue which navigates to the option the mouse is pointing to.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	The interactionValue.
////////////////////////////////////////////////////////////////////////////////////////////////////

int MenuBottomBar::getInteraction()
{
	//interacting Menu Punkte einfärben und jeweiligen Int zurückgeben
	if (menuElements[1].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		menuElements[1].setFillColor(sf::Color(100, 0, 0));
		return 1;
	}
	else if (menuElements[2].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		menuElements[2].setFillColor(sf::Color(100, 0, 0));
		return 2;
	}
	else if (menuElements[3].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		menuElements[3].setFillColor(sf::Color(100, 0, 0));
		return 3;
	}
	else if (menuElements[4].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		menuElements[4].setFillColor(sf::Color(100, 0, 0));
		return 4;
	}


	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuBottomBar::resetInteraction
///
/// Summary:	Resets the interaction.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuBottomBar::resetInteraction()
{
	for (int i = 0; i < 5; i++)
	{
		menuElements[i].setFillColor(sf::Color::White);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuBottomBar::changeFiguresToPlace
///
/// Summary:	Change figures to place.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// amount - 	The new amount. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuBottomBar::changeFiguresToPlace(int amount)
{
	menuElements[0].setString("Figures : " + std::to_string(amount));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MenuBottomBar::draw
///
/// Summary:	Draws the bottomBar into the window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window -    	[in,out] The window. 
/// placeMode - 	if true draws the figuresToPlace amount, if false not. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuBottomBar::draw(sf::RenderWindow& window, bool placeMode)
{
	window.draw(bar);

	if (placeMode == true)
	{
		window.draw(menuElements[0]);

	}

	for (int i = 1; i < 5; i++)
	{
		window.draw(menuElements[i]);
	}
}

