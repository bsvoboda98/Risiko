#include "warning.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Warning::Warning
///
/// Summary:
/// 	Default constructor. Constructor of the Warning window. Its showing up when something
/// 	went wrong.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////

Warning::Warning()
{
	font.loadFromFile("Lato-Regular.ttf");

	shape.setSize(sf::Vector2f(200, 100));
	shape.setFillColor(sf::Color(100, 100, 100, 235));

	for (int i = 0; i < 3; i++)
	{
		lines[i].setCharacterSize(22);
		lines[i].setFont(font);
		lines[i].setFillColor(sf::Color(255,60,60));
	}

	shape.setOutlineThickness(3);
	shape.setOutlineColor(sf::Color(255, 0, 0));

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Warning::placeWarning
///
/// Summary:	Place warning. It sets the text of the warning.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// line1 -    	The first line of the warning. 
/// line2 -    	The second line of the warning. 
/// line3 -    	The third line of the warning. 
/// window -   	[in,out] The window - the shape of the warning will be placed in the middle of
/// 			the window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Warning::placeWarning(std::string line1, std::string line2, std::string line3, sf::RenderWindow& window)
{
	releasedButton = false;
	sf::Vector2i rectanglePosition = sf::Mouse::getPosition();
	shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	lines[0].setString(line1);
	lines[1].setString(line2);
	lines[2].setString(line3);

	int counter = 0;
	for (int i = 0; i < 3; i++)
	{
		if (lines[i].getString() != "")
		{
			counter++;
		}
	}

	shape.setSize(sf::Vector2f(shape.getSize().x, 30 * counter + 10));
	shape.move(-75, -(shape.getSize().y / 2));
	
	for (int i = 0; i < 3; i++)
	{
		lines[i].setPosition(sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width / 2 - lines[i].getGlobalBounds().width / 2, shape.getPosition().y + i * 30 + 5));
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Warning::run
///
/// Summary:	script for the warning interaction.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	The window where the warning is drawn into. 
///
/// Returns:	the value depending on wether the warning is closed or not.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Warning::run(sf::RenderWindow& window)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && releasedButton == false)
	{
		releasedButton = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && releasedButton == true)
	{
		return 1;
	}

	this->draw(window);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Warning::draw
///
/// Summary:	Draws the warning.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	The window where the warning is drawn into. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Warning::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	for (int i = 0; i < 3; i++)
	{
		window.draw(lines[i]);
	}
}
