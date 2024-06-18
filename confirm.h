#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <SFML/Graphics.hpp>

class Confirm
{
public:
	Confirm();
	void placeConfirm(std::string questionPart1, std::string object, std::string questionPart2, sf::RenderWindow& window);

	void resetInteraction();
	int getInteraction();

	int run(sf::RenderWindow& window);

	void draw(sf::RenderWindow& window);

private:

	sf::RectangleShape confirm;

	sf::Font font;

	sf::Text yes;
	sf::Text no;
	
	sf::Text question1;
	sf::Text theme;
	sf::Text question2;


};

