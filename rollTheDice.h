#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
class RollTheDice
{
public:

	RollTheDice();

	void start();


	void setAmountOfCubes(int amount);

	std::vector<int>* run();

	bool rollingTheDice();

	int getInteraction();

	void resetInteraction();

	void draw(sf::RenderWindow& window);


private:

	sf::Sound rollTheDiceSound;
	sf::SoundBuffer rollTheDiceSoundBuffer;


	sf::RectangleShape shape;

	sf::Texture cubeAmount[6];

	sf::Sprite cubes[3];
	int currentValue[3];


	sf::Font font;

	sf::Text rolling;

	float interval = 0.01;

	int amountOfCubes = 3;

	bool button = false;
	bool isRolling = false;
	bool finishedRolling = false;

	sf::Clock clock;

	std::vector<int> finalValues;

};

