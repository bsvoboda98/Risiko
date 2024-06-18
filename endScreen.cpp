#include "endScreen.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	EndScreen::EndScreen
///
/// Summary:	Default constructor which creates the EndScreen.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

EndScreen::EndScreen()
{
	font.loadFromFile("Beyond Wonderland.ttf");
	texture.loadFromFile("pictures/Endscreen.jpg");

	shape.setTexture(texture);

	winner.setFont(font);
	action.setFont(font);
	confirm.setFont(font);
	winner.setCharacterSize(75);
	action.setCharacterSize(75);
	confirm.setCharacterSize(75);

	confirm.setString("OK!");
	action.setString(" has won");


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	EndScreen::setEndScreen
///
/// Summary:	Sets the end screen with the given username and the color of the player which has won.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// username - 	The username of the winning player. 
/// color -    	The color of the winning player. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void EndScreen::setEndScreen(std::string username, sf::Color color)
{
	winner.setFillColor(color);
	winner.setString(username);

	winner.setPosition(sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width / 2 - winner.getGlobalBounds().width, shape.getPosition().y + shape.getGlobalBounds().height / 2));
	action.setPosition(sf::Vector2f(winner.getPosition().x + winner.getGlobalBounds().width, winner.getPosition().y));
	confirm.setPosition(sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width * 0.995 - confirm.getGlobalBounds().width, shape.getPosition().y + shape.getGlobalBounds().height * 0.95 - confirm.getGlobalBounds().height));



}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	EndScreen::run
///
/// Summary:	script for the action every frame.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	the interaction when the mouse is pressed.
////////////////////////////////////////////////////////////////////////////////////////////////////

int EndScreen::run()
{
	confirm.setFillColor(sf::Color::White);
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	if (confirm.getGlobalBounds().contains(mousePosition))
	{
		confirm.setFillColor(sf::Color(100, 0, 0));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isButtonPressed)
	{
		isButtonPressed = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && isButtonPressed)
	{
		isButtonPressed = false;
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		if (confirm.getGlobalBounds().contains(mousePosition))
		{
			return 1;
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	EndScreen::draw
///
/// Summary:	Draws the Endscreen in the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void EndScreen::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(winner);
	window.draw(action);
	window.draw(confirm);

}