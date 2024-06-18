#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class ContinentBoard
{
public:
	ContinentBoard();

	void placeBoard(sf::Vector2f position, sf::Color color, std::string nameOfContinent, int countOfContinent, int amountOfContinent);

	void draw(sf::RenderWindow& window);

private:
	sf::Font font;


	sf::RectangleShape shapeOfName;
	sf::RectangleShape shapeOfCount;
	sf::RectangleShape shapeOfAmount;

	sf::Text name;
	sf::Text count;
	sf::Text amount;




};

