#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class CommandPrompt
{
public:
	CommandPrompt();

	std::string textEntered(sf::Uint32 unicode);

	void draw(sf::RenderWindow& window);


private:
	sf::RectangleShape shape;

	sf::Font font;

	sf::Text title;

	sf::RectangleShape enteredTextShape;
	sf::Text enteredText;

};