#pragma once
#include <SFML/Graphics.hpp>

class Help
{

public:

	Help() {}

	void start() {
		texture.loadFromFile("pictures/help.png");
		graphic.setTexture(texture);
	}

	void draw(sf::RenderWindow& window) { window.draw(graphic); }

private:
	sf::Sprite graphic;
	sf::Texture texture;

};

