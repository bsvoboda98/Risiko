#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>


class Figure
{
public:
	Figure(int amount, sf::Vector2i, sf::Color color);

	void draw(sf::RenderWindow& window);
	sf::Vector2i getPosition();
	int getValue();

private:

	sf::Sprite arrow;

	sf::Texture texture;

	int value;

	sf::Vector2i coordinates;

};

