#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "country.h"
#include "continent.h"
#include "card.h"

class Player
{
public:
	Player(sf::Color color, std::string name);

	sf::Color getColor(); 
	std::string getUsername();

	void giveCountry(Country* country);
	void removeCountry(Country* country);

	int getAmountOfFigures(std::vector<Continent*>* continentsOfMap);

	bool isYourCountry(Country* country);
	bool isYourContinent(Continent* continent);
	int amountOfCities();
	int amountOfCountries();


	void getCard();
	void resetGetCard();
	void interactWithCards();
	void clickOnCard();
	int useCards();
	int amountOfCards();
	int amountOfFigures();

	void eliminate();

	bool getIsEliminated();


	void showCards(sf::RenderWindow&);

	int missions = 0;

	bool hasOwnCapital();
	int amountOfCapitals();


private:

	sf::Color playerColor;
	std::vector<Country*> playerCountries;
	std::vector<Card*> playerCards;
	std::string username;
	

	bool isEliminated = false;
	bool alreadyGotCard = false;
};

