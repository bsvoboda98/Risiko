#pragma once
#include <SFML/Graphics.hpp>

class Explosion
{

public:
	Explosion(sf::Vector2f position);

	bool draw(sf::RenderWindow& window);

private:

	sf::Sprite explosionSprite;
	sf::Texture explosionTexture;

	int line = 0;
	int status = 0;

};

