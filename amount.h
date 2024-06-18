#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>


class Amount
{
public:
	Amount();
	void placeAmount(int mode, std::string name, std::string action, int maxNumber);

	int run(sf::RenderWindow& window);

	void resetInteraction();
	int getInteraction();

	void setNumber(int value);

	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape placeInCountry;

	sf::Text increase;

	sf::Text decrease;

	sf::RectangleShape close;

	sf::Font font;

	sf::Text maxValue;
	sf::Text minValue;

	sf::Text number;

	sf::Text place;

	sf::Text name;

	bool isButtonPressed = false;
	int value = 0;

	int max = 0;
};

