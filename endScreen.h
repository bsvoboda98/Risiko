#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class EndScreen
{
public:

	EndScreen();

	void setEndScreen(std::string username, sf::Color color);

	int	run();

	void draw(sf::RenderWindow& window);


private:
	sf::Font font;

	sf::Texture texture;

	sf::Sprite shape;

	sf::Text winner;

	sf::Text action;

	sf::Text confirm;

	bool isButtonPressed = false;

};

