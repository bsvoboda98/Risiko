#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "player.h"
class MenuTopBar
{
public:
	MenuTopBar();

	void givePlayerBox(Player* player);

	void setCurrentUsername(std::string username, sf::Color color);

	void changeMode();

	void showStats(int index);

	void giveNews(std::string message);


	int run(sf::RenderWindow& window);

	int getInteraction();

	void resetInteraction();

	void draw(sf::RenderWindow& window);


private:
	sf::Texture barTexture;
	sf::Sprite bar;

	sf::Texture menuButtonTexture;
	sf::Sprite menuButton;

	int hover = -1;

	sf::Font font;

	sf::Text currentUsername;
	sf::Text currentMode;


	std::vector<Player*> players;
	std::vector<sf::RectangleShape> playerBoxes;

	bool button = false;

	sf::RectangleShape hoverShape;

	sf::Text hoverStats[12];

	sf::Clock clock;
	sf::Time timer;
	std::vector<std::string> messages;
	sf::Text news;

};

