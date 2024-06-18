#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Card
{

public:
	Card(int position, sf::Color color);

	void draw(sf::RenderWindow& window);

	bool isMarked();
	bool hover();
	void show();
	void resetCard();
	int getWorth();
	void replace(int position);
	void changeMark();

private:


	int worth;
	sf::Sprite cardbody;
	sf::Sprite stars;
	sf::Sprite mark;
	sf::Texture textureOfBody;
	sf::Texture textureOfStar;
	sf::Texture textureOfMark;


	sf::Text number;
	sf::Font font;
	sf::Vector2f originalPosition;
	bool marked = false;

};

