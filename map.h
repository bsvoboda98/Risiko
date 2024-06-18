#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//extraction of the map
#include "connection.h"

//objects on the map
#include "continent.h"
#include "country.h"
#include "figure.h"

//player
#include "player.h"

//drawable things/windows
#include "amount.h"
#include "confirm.h"
#include "warning.h"

#include"card.h"
#include "menuTopBar.h"

#define NUMBER_OF_WORLD_BORDERS 66
#define NUMBER_OF_CONTINENTS 6

class Map
{
public:
	Map(); //Constructor, creates the map
	~Map()
	{
		for (auto i : continentsOfMap)
		{
			delete i;
		}
	}
	void start();
	void draw(sf::RenderWindow& window);

	int mapInteraction(sf::RenderWindow& window, sf::View* mapView);
	void resetMapInteraction();

	bool placeFigure(int index, int value, int mode, int figuresToPlace);
	void deleteFigure(int index, int value);
	bool attack(Player* player, int& lossOfAttacker, int& lossOfDefender, MenuTopBar* topBar);
	void takePossesion(int indexOfDestination, int amount, Player* player);
	int move();
	void resetIsMoved();

	int distributeCountries(int numberOfPlayers);

	void givePlayers(std::vector<Player*>* playerList);

	Country* getCountryOfIndex(int index);

	std::vector<Continent*>* getContinentsOfMap();

	void getContinentsWithoutPlayer(Player* player, std::vector<int>* continentsWithout);

	int getNumberOfCountries();

	int chooseAmount = 0;
	int chooseStart = 0;
	int chooseGoal = 0;

private:
	sf::Clock clock;
	sf::Shader oceanShader;
	sf::RectangleShape ocean;
	sf::Texture oceanTexture;

	sf::VertexArray borders[NUMBER_OF_WORLD_BORDERS];
	sf::VertexArray surfaces[NUMBER_OF_CONTINENTS];
	uint8_t map_array[960][540];
	int numberOfCountries = 0;
	std::vector<std::vector<int>> indexOfCountry;
	std::vector<Continent*> continentsOfMap;
	std::vector<Connection> connections;

	std::vector<Player*>* players;

	int attackStatus = 0;
	int amountStatus = 0;

	
};

