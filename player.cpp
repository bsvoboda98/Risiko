#include "player.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::Player
///
/// Summary:	Constructor which is setting the color and the name of the player.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// color -    	The color of the player. 
/// name - 	   	The name of the player. 
////////////////////////////////////////////////////////////////////////////////////////////////////

Player::Player(sf::Color color, std::string name) {
	playerColor = color;
	username = name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::getColor
///
/// Summary:	Gets the color of the player.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	The color of the acting player.
////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Color Player::getColor()
{
	return this->playerColor;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::getUsername
///
/// Summary:	Gets the username of the player.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	The username of the player.
////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Player::getUsername()
{

	return this->username;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::giveCountry
///
/// Summary:	Give a country to the player.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// country - 	a pointer to the country which the player gets. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::giveCountry(Country* country)
{
	this->playerCountries.push_back(country);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::getAmountOfFigures
///
/// Summary:	Gets amount of which the player is able to place in the placeMode.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// continentsOfMap - 	[in,out] If non-null, the continents of map whith every country. 
///
/// Returns:	The amount of figures the player is able to place in the placeMode.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::getAmountOfFigures(std::vector<Continent*>* continentsOfMap)
{
	int counter = (int) playerCountries.size() + this->amountOfCities();
	int giveFigure = floor(counter / 3);

	for(auto i : *continentsOfMap)
	{
		if(this->isYourContinent(i))
		{
			giveFigure += i->getReward();
		}
	}

	giveFigure += this->amountOfCapitals();

	if (giveFigure < 3)
	{
		giveFigure = 3;
	}

	return giveFigure;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::isYourContinent
///
/// Summary:	Query if 'continent' is your continent.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// continent - 	[in,out] If non-null, the continent. 
///
/// Returns:	True if its the continent of the player, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Player::isYourContinent(Continent* continent)
{
	bool isYourContinent = true;;
	for (int j = 0; j < continent->getAmountOfCountries(); j++)
	{
		if (!this->isYourCountry(continent->getCountry(j)))
		{
			isYourContinent = false;
		}
	}
	return isYourContinent;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::isYourCountry
///
/// Summary:	Query if 'country' is your country.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// country - 	[in,out] If non-null, the country. 
///
/// Returns:	True if its a country of the player, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Player::isYourCountry(Country* country)
{
	for (auto i : playerCountries)
	{
		if (country == i)
		{
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::amountOfCities
///
/// Summary:	Amount of cities.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	the amount the countries with cities which the player is owning.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::amountOfCities()
{
	int counter = 0;
	for (auto i : this->playerCountries)
	{
		if (i->getCity() == true)
		{
			counter++;
		}
	}
	return counter;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::removeCountry
///
/// Summary:	Removes the given country of the player-countries.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// country - 	[in,out] the country. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::removeCountry(Country* country)
{
	for (int i = 0; i < static_cast<int>(this->playerCountries.size()); i++)
	{
		if (this->playerCountries[i] == country)
		{
			this->playerCountries.erase(this->playerCountries.begin() + i);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::getCard
///
/// Summary:	gives the player a card, if the player didnt get a card in this round already.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::getCard()
{
	if (alreadyGotCard == false)
	{
		playerCards.push_back(new Card((int)playerCards.size(), this->playerColor));
		alreadyGotCard = true;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::resetGetCard
///
/// Summary:	Resets the alreadyGotCard boolean.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::resetGetCard()
{
	this->alreadyGotCard = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::showCards
///
/// Summary:	draws the cards of the player.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// window - 	[in,out] The window where the cards will be drawn. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::showCards(sf::RenderWindow& window)
{
	for(auto i : this->playerCards)
	{
		i->draw(window);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::interactWithCards
///
/// Summary:
/// 	Interact with cards. when the mouse is hovering over the cards the cards will move upwards
/// 	with move()
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::interactWithCards()
{
	for (int i = (int)playerCards.size() - 1; i >= 0; i--)
	{
		if (playerCards[i]->hover() == true)
		{
			playerCards[i]->show();
			if (i != 0)
			{
				playerCards[i - 1]->resetCard();
				i--;
			}
		}
		else
		{
			playerCards[i]->resetCard();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::clickOnCard
///
/// Summary:	when the mouse is hovering over a card the card gets changed with changeMark()
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::clickOnCard()
{
	for (int i = (int)playerCards.size() - 1; i >= 0; i--)
	{
		if (playerCards[i]->hover() == true)
		{
			playerCards[i]->changeMark();
			return;		
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::useCards
///
/// Summary:
/// 	every marked Card will be converted into figures. the cards will be deleted if the amount
/// 	of stars is more than 10 or less than 2 the method stops and returns -1.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	the amount of figures the player can place more after using the cards.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::useCards()
{
	int worth = 0;
	for (auto i : playerCards)
	{
		if (i->isMarked() == true)
		{
			worth += i->getWorth();
		}
	}
	if (worth <= 10 && worth > 1)
	{
		for (int i = 0; i < (int)playerCards.size(); i++)
		{
			if (playerCards[i]->isMarked() == true)
			{
				delete playerCards[i];
				playerCards.erase(playerCards.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < (int)playerCards.size(); i++)
		{
			playerCards[i]->replace(i);
		}
		return worth;
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::amountOfCountries
///
/// Summary:	amount Of Countries.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	returns the amount of Countries the player is owning.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::amountOfCountries()
{
	return (int) this->playerCountries.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::amountOfCards
///
/// Summary:	amount Of Cards.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	returns the amount of Cards the player is owning.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::amountOfCards()
{
	return (int) this->playerCards.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::amountOfFigures
///
/// Summary:	amount Of Figures.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	returns the amount of Figures the player is owning.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::amountOfFigures()
{
	int amount = 0;

	for (auto i : playerCountries)
	{
		amount += i->numberOfFigures;
	}

	return amount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::amountOfCapitals
///
/// Summary:	Amount of capitals the player is owning.
///
/// Author:	Bennet
///
/// Date:	02.01.2020
///
/// Returns:	the amount of capitals the player owns.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Player::amountOfCapitals()
{
	int counter = 0;
	for (auto i : this->playerCountries)
	{
		if (i->getCapital() == true)
		{
			counter++;
		}
	}
	return counter;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Player::hasOwnCapital
///
/// Summary:	Query if this player has its own capital.
///
/// Author:	Bennet
///
/// Date:	02.01.2020
///
/// Returns:	True if own capital, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Player::hasOwnCapital()
{
	for (auto i : this->playerCountries)
	{
		if (i->getCapital() == true)
		{
			if (i->getColorOfCapital() == this->playerColor)
			{
				return true;
			}
		}
	}
	return false;
}



void Player::eliminate()
{
	this->isEliminated = true;
}

bool Player::getIsEliminated()
{
	return this->isEliminated;
}