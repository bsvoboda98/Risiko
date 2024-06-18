#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "figure.h"
#include "explosion.h"

class Country
{
public:
	Country(std::string filename, sf::Color color);
	void draw(sf::RenderWindow& window);
	void setColor(int mode);

	sf::Vector2i getRandomPositionForFigure();

	void refreshAmount();

	void placeFigure(int value, sf::Color color);
	void drawFigure(sf::RenderWindow& window);

	void deleteFigure(int value);

	int getNumbOfValue(int value);
	std::string getName();
	bool getCity();
	bool isNeighbor(int index);

	void giveCapital(sf::Color color);
	void replaceCapital();
	bool getCapital();
	sf::Color getColorOfCapital();

	void explode();

	int numberOfFigures = 0;
	int indexOfOwner = -1;
	int numberOfMovedFigures = 0;

	

private:
	sf::Font font;

	std::vector<sf::VertexArray> surface;

	std::vector<int> neighbors;
	sf::Color colorOfCapital = sf::Color::Black;

	std::vector<sf::Vector2i> figurePositions;
	std::vector<bool> figurePositionIsUsed;
	int originalColor[3];
	int numberOfUnits = 0;
	int maxNumberOfUnits = 0;
	std::vector<Figure*> figureList;

	std::vector<Explosion*> explosionList;

	std::string name = "test";
	sf::Text countryname;
	sf::Text amount;

	bool hasCity = false;
	bool hasCapital = false;
};

