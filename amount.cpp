#include "amount.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Amount::Amount
///
/// Summary:	Default constructor of the AmountWindow.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

Amount::Amount()
{
	font.loadFromFile("Lato-Regular.ttf");
	placeInCountry.setOutlineColor(sf::Color::Black);
	placeInCountry.setOutlineThickness(3);

	name.setFont(font);
	name.setCharacterSize(15);

	number.setFont(font);
	number.setCharacterSize(40);

	place.setFont(font);
	place.setCharacterSize(15);

	maxValue.setFont(font);
	maxValue.setCharacterSize(15);
	maxValue.setString("max");

	minValue.setFont(font);
	minValue.setCharacterSize(15);
	minValue.setString("min");

	increase.setFillColor(sf::Color(0, 100, 0));
	increase.setFont(font);
	increase.setCharacterSize(30);
	increase.setString("+");

	decrease.setFillColor(sf::Color(100, 0, 0));
	decrease.setFont(font);
	decrease.setCharacterSize(50);
	decrease.setString("-");

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Amount::placeAmount
///
/// Summary:	Places amount the amountWindow.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// mode - 			The mode of the AmountWindow. 
/// country -   	The country the AmountWindow is pointing to. 
/// action -    	The action it has to do. 
/// maxNumber - 	The maximum number the amount can be. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Amount::placeAmount(int mode, std::string country, std::string action, int maxNumber)
{
	max = maxNumber;
	placeInCountry.setSize(sf::Vector2f(150, 100));
	placeInCountry.setFillColor(sf::Color(100, 100, 100, 235));

	if (mode == 1)
	{
		sf::Vector2i rectanglePosition2i = sf::Mouse::getPosition();
		placeInCountry.setPosition(rectanglePosition2i.x, rectanglePosition2i.y);
		if (placeInCountry.getPosition().x + placeInCountry.getGlobalBounds().width > 1920)
		{
			placeInCountry.setPosition(rectanglePosition2i.x - 150, placeInCountry.getPosition().y);
		}
	}
	else if (mode == 2)
	{
		sf::Vector2i rectanglePosition2i = sf::Mouse::getPosition();
		placeInCountry.setPosition(rectanglePosition2i.x - 150, rectanglePosition2i.y);
	}

	name.setString(country);
	name.setPosition(placeInCountry.getPosition().x + placeInCountry.getGlobalBounds().width / 2 - name.getGlobalBounds().width / 2, placeInCountry.getPosition().y + (placeInCountry.getGlobalBounds().height * 0.05));


	increase.setPosition(placeInCountry.getPosition().x + placeInCountry.getGlobalBounds().width * 0.90 - increase.getGlobalBounds().width, placeInCountry.getPosition().y + (placeInCountry.getGlobalBounds().height / 2) - increase.getGlobalBounds().height / 2 - 13);


	decrease.setPosition(placeInCountry.getPosition().x + placeInCountry.getGlobalBounds().width * 0.05, placeInCountry.getPosition().y + (placeInCountry.getGlobalBounds().height / 2) - 35);

	maxValue.setPosition(placeInCountry.getPosition().x + placeInCountry.getGlobalBounds().width * 0.95 - maxValue.getGlobalBounds().width, placeInCountry.getPosition().y + (placeInCountry.getGlobalBounds().height * 0.75));

	minValue.setPosition(placeInCountry.getPosition().x + placeInCountry.getGlobalBounds().width * 0.05, placeInCountry.getPosition().y + (placeInCountry.getGlobalBounds().height * 0.75));

	this->value = 0;
	this->setNumber(value);
	number.setPosition(placeInCountry.getPosition().x + (placeInCountry.getGlobalBounds().width / 2) - number.getGlobalBounds().width / 2, placeInCountry.getPosition().y + (placeInCountry.getGlobalBounds().height / 2) - number.getGlobalBounds().height);

	
	place.setString(action);
	place.setPosition(placeInCountry.getPosition().x + (placeInCountry.getGlobalBounds().width / 2) - 15, placeInCountry.getPosition().y + (placeInCountry.getGlobalBounds().height * 0.75));
	
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Amount::run
///
/// Summary:	Runs the AmountWindow and acting with the return value depending on the current Mode.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
///
/// Returns:	An int.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Amount::run(sf::RenderWindow& window)
{
	this->resetInteraction();
	int interaction = this->getInteraction();
	this->draw(window);



	if (interaction != 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isButtonPressed)
	{
		isButtonPressed = true;
	}
	else if (isButtonPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && interaction != 0)
	{
		isButtonPressed = false;

		if (interaction == 1)
		{
			value++;
			if (value > max)
			{
				value = max;
			}
			this->setNumber(value);
			return -1;
		}
		else if (interaction == 2)
		{
			if (value != 0)
			{
				value--;
				this->setNumber(value);
			}
			return -1;
		}
		else if (interaction == 3)
		{
			this->setNumber(0);
			return value;

		}
		else if (interaction == 4)
		{
			value = max;
			this->setNumber(value);
			return -1;
		}
		else if (interaction == 5)
		{
			value = 0;
			this->setNumber(value);
			return -1;
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Amount::resetInteraction
///
/// Summary:	Resets the interaction, so every object in the AmountWindow has its original Color.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////

void Amount::resetInteraction()
{
	increase.setFillColor(sf::Color(0, 100, 0));
	decrease.setFillColor(sf::Color(100, 0, 0));
	place.setFillColor(sf::Color::White);
	maxValue.setFillColor(sf::Color::White);
	minValue.setFillColor(sf::Color::White);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Amount::getInteraction
///
/// Summary:
/// 	Gets the interaction and sets the Color into Blue when the Mouse is pointing on a Object
/// 	in the Color.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	The interaction.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Amount::getInteraction()
{
	if (increase.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		increase.setFillColor(sf::Color(0, 0, 100));
		return 1;
	}
	else if (decrease.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		decrease.setFillColor(sf::Color(0, 0, 100));
		return 2;
	}
	else if (place.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		place.setFillColor(sf::Color(100, 0, 0));
		return 3;
	}
	else if (maxValue.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		maxValue.setFillColor(sf::Color(100, 0, 0));
		return 4;
	}
	else if (minValue.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		minValue.setFillColor(sf::Color(100, 0, 0));
		return 5;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Amount::setNumber
///
/// Summary:	Sets the number of the current Amount.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// value - 	The new value. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Amount::setNumber(int value)
{

	number.setString(std::to_string(value));
	
	number.setPosition(placeInCountry.getPosition().x + (placeInCountry.getGlobalBounds().width / 2) - number.getGlobalBounds().width / 2, placeInCountry.getPosition().y + (placeInCountry.getGlobalBounds().height / 2) - number.getGlobalBounds().height);


	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Amount::draw
///
/// Summary:	Draws the AmountWindow into the given window.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Amount::draw(sf::RenderWindow& window)
{
	window.draw(placeInCountry);
	window.draw(increase);
	window.draw(decrease);
	window.draw(number);
	window.draw(place);
	window.draw(name);
	window.draw(maxValue);
	window.draw(minValue);
}
