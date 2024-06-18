#include "figure.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Figure::Figure
///
/// Summary:
/// 	Constructor. Creates a figure with a given amount (loads the texture depending on the
/// 	amount), on the given position and the given color.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// amount -   	The amount. 
/// position - 	The position. 
/// color -    	The color. 
////////////////////////////////////////////////////////////////////////////////////////////////////

Figure::Figure(int amount, sf::Vector2i position, sf::Color color)
{
	this->value = amount;

	
	if (amount > 0 && amount < 7)
	{
		std::string file = "pictures/figure";
		std::stringstream strAmount;
		strAmount << amount;
		file += strAmount.str();
		file += ".png";
		this->texture.loadFromFile(file);
		this->arrow.setRotation(rand() % 360);
		this->arrow.setColor(color);
		this->arrow.setOrigin(12, 15);

	}
	else if (amount == 7)
	{
		this->texture.loadFromFile("pictures/figure3.png");
		this->arrow.setRotation(45);
		this->arrow.setOrigin(12, 15);
		this->arrow.setScale(0.5, 0.5);
		this->arrow.setColor(sf::Color(155, 155, 155));
	}
	else if(amount == 0)
	{
		this->texture.loadFromFile("pictures/symbol-hersteller.png");
		this->arrow.setOrigin(10, 9);
	}
	else if(amount == -1)
	{
		this->texture.loadFromFile("pictures/capital.png");
		this->arrow.setOrigin(10, 10);
		this->arrow.setColor(color);

	}

	
	
	
	
	coordinates = position;
	this->arrow.setTexture(texture);	
	this->arrow.setPosition(position.x, position.y);
	coordinates = position;
	texture.setSmooth(true);
	this->coordinates = position;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Figure::draw
///
/// Summary:	Draws the figure in the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Figure::draw(sf::RenderWindow& window)
{
	window.draw(this->arrow);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Figure::getPosition
///
/// Summary:	Gets the position of the figure.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	The position.
////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Vector2i Figure::getPosition()
{
	return coordinates;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Figure::getValue
///
/// Summary:	Gets the value of the figure.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	The value.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Figure::getValue()
{
	return value;
}