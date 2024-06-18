#include "continentboard.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ContinentBoard::ContinentBoard
///
/// Summary:	Default constructor which sets the font of every part of the continentBoard.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////

ContinentBoard::ContinentBoard()
{
	
	if (!font.loadFromFile("Lato-Regular.ttf"))
		{
			exit(1);
		}
	name.setFont(font);
	count.setFont(font);
	amount.setFont(font);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ContinentBoard::placeBoard
///
/// Summary:	Places the board whith the correct information at the given position.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// position - 				The position of the continentBoard. 
/// color - 				The color of the continent. 
/// nameOfContinent -   	Name of the continent. 
/// countOfContinent -  	The amount of countries of the continent. 
/// amountOfContinent - 	The reward of continent. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void ContinentBoard::placeBoard(sf::Vector2f position, sf::Color color, std::string nameOfContinent, int countOfContinent, int amountOfContinent)
{

	shapeOfName.setSize(sf::Vector2f(105, 21));
	shapeOfName.setOutlineThickness(2);
	shapeOfName.setOutlineColor(sf::Color::Black);
	shapeOfName.setFillColor(sf::Color(100, 100, 100));
	shapeOfName.setPosition(sf::Vector2f(position));

	shapeOfCount.setSize(sf::Vector2f(105, 21));
	shapeOfCount.setOutlineThickness(2);
	shapeOfCount.setOutlineColor(sf::Color::Black);
	shapeOfCount.setFillColor(sf::Color(color.r - 30, color.g - 30, color.b - 30));
	shapeOfCount.setPosition(sf::Vector2f(position.x, position.y + 19));

	shapeOfAmount.setSize(sf::Vector2f(40, 40));
	shapeOfAmount.setOutlineThickness(2);
	shapeOfAmount.setOutlineColor(sf::Color::Black);
	shapeOfAmount.setFillColor(sf::Color(color.r - 30, color.g - 30, color.b - 30));
	shapeOfAmount.setPosition(sf::Vector2f(position.x +103, position.y));
	
	name.setString(nameOfContinent);
	name.setCharacterSize(15);
	name.setPosition(position.x + 98 - name.getGlobalBounds().width, position.y + 1);
	name.setFillColor(sf::Color::White);

	count.setCharacterSize(15);
	std::string strCount = std::to_string(countOfContinent) + " regions";
	count.setString(strCount);
	count.setPosition(position.x + 105 - (int)(count.getString().getSize()) * 8, position.y + 22);
	count.setFillColor(sf::Color::Black);

	amount.setCharacterSize(40);
	amount.setString(std::to_string(amountOfContinent));
	amount.setPosition(position.x + 105 + 5, position.y - 5);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	ContinentBoard::draw
///
/// Summary:	Draws the continentBoard in the given window.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void ContinentBoard::draw(sf::RenderWindow& window)
{
	

	window.draw(shapeOfCount);

	window.draw(shapeOfName);

	window.draw(shapeOfAmount);

	window.draw(name);

	window.draw(count);

	window.draw(amount);
}
