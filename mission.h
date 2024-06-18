#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "player.h"
#include "continent.h"

class Mission
{
	
public:

	Mission(int indexOfMission, sf::Vector2f position);

	void check(Player* player, std::vector<Continent*>* continents, int citiesBeforeAttacking, int countriesBeforeAttacking, std::vector<int> continentsWithoutPlayer);

	bool hasAccomplished(Player* player);

	int getIndex();


	void draw(sf::RenderWindow& window);


private:
	int index;

	sf::VertexArray shape = sf::VertexArray(sf::TrianglesStrip, 6);

	sf::Font font;


	sf::Text line[3];
	
	Player* solvedBy = NULL;

};

