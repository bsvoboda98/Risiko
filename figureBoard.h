#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "figure.h"

class FigureBoard
{
public:
	FigureBoard();

	void start(sf::Vector2f position);

	int getWorth(int amount);

	void draw(sf::RenderWindow& window);

private:
	sf::Font font;

	sf::RectangleShape shape;

	sf::Texture texture;
	
	sf::Sprite stars[3];
	sf::RectangleShape starBox[3];

	Figure* figures[3];
	sf::RectangleShape figureBox[3];


	sf::Text amount[9];
	sf::RectangleShape amountBox[9];

	int worthValue[9] = {2, 4, 7, 10, 13, 17, 21, 25, 30};
	sf::Text worth[9];
	sf::RectangleShape worthBox[9];



};

