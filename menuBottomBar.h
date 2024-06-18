#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class MenuBottomBar
{
public:
	MenuBottomBar();
	int run();

	int getInteraction();
	void resetInteraction();

	void draw(sf::RenderWindow& window, bool placeMode);

	void changeFiguresToPlace(int amount);

private:
	sf::Font font;

	sf::Text menuElements[5];

	sf::Texture texture;

	sf::Sprite bar;

	bool isButtonPressed = false;
};

