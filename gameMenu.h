#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameMenu
{
public:

	GameMenu();

	void resetInteraction();

	int getInteraction();

	int run();

	void draw(sf::RenderWindow& window);


private:

	sf::Texture texture;
	sf::Sprite shape;

	sf::Font font;
	sf::Text option[4];


	bool button = false;

};

