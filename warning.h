#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class Warning
{
public:
	Warning();

	void placeWarning(std::string line1, std::string line2, std::string line3, sf::RenderWindow& window);
		
	int run(sf::RenderWindow& window);


	void draw(sf::RenderWindow& window);


private:
	sf::RectangleShape shape;

	sf::Text lines[3];

	sf::Font font;

	bool releasedButton = false;
};

