#include "connection.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Connection::Connection
///
/// Summary:	creates a Connectionline between 2 Posiitons.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// first -    	The first position. 
/// second -   	The second position. 
////////////////////////////////////////////////////////////////////////////////////////////////////

Connection::Connection(sf::Vector2i first, sf::Vector2i second)
{
	sf::Color color = sf::Color(75, 75, 75);

	firstCircle.setRadius(3);
	firstCircle.setOrigin(sf::Vector2f(3, 3));
	firstCircle.setFillColor(color);
	firstCircle.setPosition(first.x, first.y);

	secondCircle.setRadius(3);
	secondCircle.setOrigin(sf::Vector2f(3, 3));
	secondCircle.setFillColor(color);
	secondCircle.setPosition(second.x, second.y);

	line[0] = sf::Vertex(sf::Vector2f(first.x, first.y));
	line[0].color = color;

	line[1] = sf::Vertex(sf::Vector2f(second.x, second.y));
	line[1].color = color;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Connection::draw
///
/// Summary:	Draws the connection in the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Connection::draw(sf::RenderWindow& window)
{
	window.draw(firstCircle);
	window.draw(secondCircle);
	window.draw(line, 2, sf::Lines);
}