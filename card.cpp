#include "card.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Card::Card
///
/// Summary:	Constructor. Defines the Value of the Card and the color of the Card.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// position - 	The position of the Card - depends on the position in the Card-vector of the
/// 			player which is the owner of the Card. 
/// color -    	The color of the Card. 
////////////////////////////////////////////////////////////////////////////////////////////////////

Card::Card(int position, sf::Color color)
{
	this->worth = rand() % 2 + 1;


	this->font.loadFromFile("Lato-Regular.ttf");


	textureOfBody.loadFromFile("pictures/card.png");
	textureOfMark.loadFromFile("pictures/mark.png");

	if (worth == 1)
	{
		this->textureOfStar.loadFromFile("pictures/star1.png");	
	}
	else
	{
		this->textureOfStar.loadFromFile("pictures/star2.png");		
	}

	cardbody.setTexture(textureOfBody);
	cardbody.setColor(sf::Color(127, 127, 127));
	cardbody.setPosition(500 + position * 75, 930);
	this->originalPosition = cardbody.getPosition();

	mark.setTexture(textureOfMark);
	mark.setPosition(originalPosition);
	mark.setColor(sf::Color::Red);


	stars.setTexture(textureOfStar);
	stars.setColor(color);
	stars.setPosition(cardbody.getPosition().x + cardbody.getGlobalBounds().width / 2 - stars.getGlobalBounds().width / 2, cardbody.getPosition().y + cardbody.getGlobalBounds().height * 0.25 - stars.getGlobalBounds().height / 2);							//ABHÄNGIG VON POSITION DES CARDBODYS
	

	number.setFont(font);
	number.setCharacterSize(40);
	number.setString(std::to_string(worth));
	number.setPosition(cardbody.getPosition().x + cardbody.getGlobalBounds().width / 2	- number.getGlobalBounds().width / 2, cardbody.getPosition().y + cardbody.getGlobalBounds().height * 0.75 - number.getGlobalBounds().height / 2 );							//ABHÄNGIG VON POSITION DES CARDBODYS

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Card::draw
///
/// Summary:	Draws the Card into the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Card::draw(sf::RenderWindow& window)
{
	window.draw(cardbody);
	window.draw(stars);
	window.draw(number);
	if (this->marked == true)
	{
		window.draw(mark);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Card::hover
///
/// Summary:	Hovers this object.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	True if it succeeds, false if it fails.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Card::hover()
{
	if (this->cardbody.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y) && sf::Mouse::getPosition().y < 1030)
	{
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Card::show
///
/// Summary:	moves this Card upwards but not more than 50 pixels.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void Card::show()
{
	if (cardbody.getPosition().y > originalPosition.y - 50)
	{
		cardbody.move(0, -5);
		stars.move(0, -5);
		number.move(0, -5);
		mark.move(0, -5);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Card::resetCard
///
/// Summary:	Resets the card to its original position.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void Card::resetCard()
{
	if (cardbody.getPosition() != this->originalPosition)
	{
		cardbody.setPosition(originalPosition);
		mark.setPosition(originalPosition);
		stars.setPosition(cardbody.getPosition().x + cardbody.getGlobalBounds().width / 2 - stars.getGlobalBounds().width / 2, cardbody.getPosition().y + cardbody.getGlobalBounds().height * 0.25 - stars.getGlobalBounds().height / 2);							
		number.setPosition(cardbody.getPosition().x + cardbody.getGlobalBounds().width / 2 - number.getGlobalBounds().width / 2, cardbody.getPosition().y + cardbody.getGlobalBounds().height * 0.75 - number.getGlobalBounds().height / 2);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Card::getWorth
///
/// Summary:	Gets the worth of the Card.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	The worth of the Card.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Card::getWorth()
{
	
	return this->worth;
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Card::replace
///
/// Summary:
/// 	Replaces the Card on a new Position depending on the position in the vector of the acting
/// 	player.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// position - 	The position int the vector of the Player. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Card::replace(int position)
{
	//wie im Konstruktor anhand der Position im array versetzen
	cardbody.setPosition(500 + position * 50, 930);
	mark.setPosition(cardbody.getPosition());
	stars.setPosition(cardbody.getPosition().x + cardbody.getGlobalBounds().width / 2 - stars.getGlobalBounds().width / 2, cardbody.getPosition().y + cardbody.getGlobalBounds().height * 0.25 - stars.getGlobalBounds().height / 2);							//ABHÄNGIG VON POSITION DES CARDBODYS
	number.setPosition(cardbody.getPosition().x + cardbody.getGlobalBounds().width / 2 - number.getGlobalBounds().width / 2, cardbody.getPosition().y + cardbody.getGlobalBounds().height * 0.75 - number.getGlobalBounds().height / 2);							//ABHÄNGIG VON POSITION DES CARDBODYS
	this->originalPosition = cardbody.getPosition();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Card::changeMark
///
/// Summary:	Change the mark of the Card.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////

void Card::changeMark()
{
	if (this->marked == false)
	{
		this->marked = true;
	}
	else
	{
		this->marked = false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Card::isMarked
///
/// Summary:	checks if this object is marked.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	True if marked, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Card::isMarked()
{
	return this->marked;
}