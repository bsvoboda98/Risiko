#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "country.h"
#include "continentboard.h"

class Continent
{
public:
	Continent(std::string filename);
	void draw(sf::RenderWindow& window);
	void convertInteraction(int country, int mode);
	Country* getCountry(int country);

	int getAmountOfCountries();
	int getReward();


private:

	std::vector<Country*> countriesOfContinent;

	std::string name;
	sf::Vector2f boardPosition;

	int count;
	int reward;

	sf::Color color;

	ContinentBoard board;
};

