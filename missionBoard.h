#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "mission.h"
class MissionBoard
{

public:
	MissionBoard();

	void start(sf::Vector2f position);

	void startWithMissions(sf::Vector2f position, int missionsIndex[8]);

	void draw(sf::RenderWindow& window);

	bool hasWon(Player* player);

	int getIndexOfMission(int index);

	std::vector<Mission*> missions;
private:
	sf::Font font;
	sf::Text basicMission;
	sf::Text specialMission;
	
	sf::Sprite shape;
	sf::Texture texture;

	std::vector<sf::VertexArray> missionHeader;

	std::vector<sf::VertexArray> missionBox;





};

