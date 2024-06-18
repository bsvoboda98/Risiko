#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "map.h"

#include "warning.h"
#include "amount.h"
#include "confirm.h"
#include "menuBottomBar.h"
#include "menuTopBar.h"
#include "figureBoard.h"
#include "missionBoard.h"
#include "endScreen.h"
#include "gameMenu.h"
#include "chat.h"
#include "help.h"

#include "player.h"
#include "rollTheDice.h"


class Game
{
public:
	Game(){}

	virtual void startGame(int amountOfPlayerValue, std::vector<std::string>* username, std::vector<sf::Color>* playerColor) = 0;  //LOCAL GAME

	virtual void startGame(int amountOfPlayerValue, std::vector<std::string>* username, std::vector<sf::Color>* playerColor, std::vector<sf::TcpSocket*> sockets, int indexOfHost) = 0;  //HOST GAME

	virtual void startGame(int amountOfPlayerValue, std::vector<std::string>* username, std::vector<sf::Color>* playerColor, sf::TcpSocket* socket, int indexOfClient) = 0;  //CLIENT GAME

	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	 

	virtual void moveView(sf::View* mapView, sf::RenderWindow& window); //überall das selbe!!!!

	virtual void scaleView(int delta, sf::View* mapView, sf::RenderWindow& window); //überall das selbe!!!!

	virtual void checkView(sf::View* mapView, sf::RenderWindow& window); //überall das selbe!!!!

	virtual void getInteraction(sf::RenderWindow& window, sf::View* mapView); //überall das selbe!!!!

	virtual void newOrder(); //überall das selbe!!!!

	virtual void checkMissions(); //überall das selbe!!!!!

	virtual void handleWindows(sf::RenderWindow& window); //überall das selbe!!!!!

	virtual bool changeMode(); //überall das selbe?

	virtual void changePlayer(); //überall das selbe?



	virtual void run(sf::Event* event, sf::RenderWindow& window, bool& isMenu, bool& inGame, sf::View* mapView); //nicht das selbe!

	virtual void confirming(sf::RenderWindow& window) = 0; //nicht das selbe!

	virtual void choosing(sf::RenderWindow& window) = 0; //nicht das selbe!

	virtual void menuInterface(sf::RenderWindow& window, bool& inGame, bool& isMenu) = 0; //überall das selbe?

	virtual void leftMouseButtonPressed(sf::RenderWindow& window) = 0; //nicht das selbe!

	virtual void draw(sf::RenderWindow& window, sf::View* mapView) = 0; //überall das selbe?

	virtual void changeActivePlayer() = 0;

	virtual void runPlaceMode() = 0;

	virtual void runAttackMode(sf::RenderWindow& window) = 0;

	virtual void runMoveMode(sf::RenderWindow& window) = 0;

	virtual void modifyChat(sf::Uint32 unicode) = 0;

	virtual void placeCapital(int location);

	virtual void rollingTheDices() = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Host
	
	virtual void sendToAll(sf::Packet packet) = 0; 

	virtual void areAllReady() = 0; 

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Client




	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Multiplayer

	virtual void receive(sf::RenderWindow& window) = 0;

	virtual void waitForCubes() = 0;



protected:

	Help help;

	sf::Sound fightSound;
	sf::Sound cardSound;
	sf::Sound messageSound;

	sf::SoundBuffer afterFight;
	sf::SoundBuffer useCardsSound;
	sf::SoundBuffer newMessageSound;
	
	sf::Font font;

	Map map;
	
	std::vector<Player*> players;
	int currentPlayerIndex = 0;
	int firstPlayerIndex = 0;
	Player* currentPlayer = NULL;
	Player* activePlayer = NULL;

	bool placeCapitals = true;
	bool isFirstRound = false;


	bool placeMode = true;
	bool attackMode = false;
	bool moveMode = false;

	int interaction = 0;

	Confirm confirm;
	Amount choosingHelp;
	Warning warning;

	MenuBottomBar bar;
	MenuTopBar topBar;

	RollTheDice rollTheDice;

	FigureBoard figureBoard;
	MissionBoard missionBoard;
	GameMenu gameMenu;
	Chat chat;

	EndScreen endScreen;

	bool isConfirming = false;
	bool isChoosing = false;
	bool isWarning = false;
	bool isEndscreen = false;
	bool showCards = false;
	bool isGameMenu = false;
	bool isChat = false;
	bool isRolling = false;
	bool waitingForCubes = false;


	int firstFiguresToPlace = 0;
	int figuresToPlace = 0;

	int attackerAmount;
	int defenderAmount;
	int rollingStatus = 0;
	std::vector<int> cubesOfAttacker;
	std::vector<int> cubesOfDefender;


	int citiesBeforeAttacking = 0;
	int countriesBeforeAttacking = 0;
	std::vector<int> continentsWithoutPlayer;

	int modeStatus = -1;


};

