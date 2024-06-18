#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "mainLobby.h"
#include "clientLobby.h"
#include "commandPrompt.h"

#define MAX_NUMBER_OF_ITEMS 7

class Menu
{
public:
	Menu(float width, float height); //Constructor
	void draw(sf::RenderWindow& window);
	void run(sf::RenderWindow& window, sf::Event* event, Lobby** lobby, int& gameMode, bool& isMenu, bool& isLobby);
	int getMenuIntersection(sf::RenderWindow& window);
	void resetMenuIntersection();

 private:
	 CommandPrompt prompt;

	 sf::Texture backgroundtexture;
	 sf::Sprite background;

	 sf::Font font;
	 sf::Text text[MAX_NUMBER_OF_ITEMS];

	
	 bool isPressed = false;
	 bool chooseMultiplayer = false;
	 bool lookForConnection = false;
	 int option = 5;


};



