#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

class Connection
{
public:

	Connection(sf::Vector2i first, sf::Vector2i second);

	void draw(sf::RenderWindow& window);

private:

	sf::CircleShape firstCircle;
	sf::CircleShape secondCircle;
	sf::Vertex line[2];

};

