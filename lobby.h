#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <sstream>

#include "hostGame.h"
#include "localGame.h"
#include "clientGame.h"

#include "warning.h"

class Lobby
{

public:

	Lobby(){ }

	virtual int getInteraction() = 0; //both

	virtual void resetInteraction() = 0; //both

	virtual void run(sf::RenderWindow& window, sf::Event* event, Game** game, bool& isLobby, bool& inGame) = 0; //both

	virtual void draw(sf::RenderWindow& window) = 0; //both




	////////////////////////////////////////////////////////////////////////////////////////////////////
	//mainLobby

	virtual void startLobby(int gameMode) = 0;

	virtual void changeColor(int interaction) = 0;

	virtual void changeConnection(int interaction) = 0;

	virtual void start(Game** game, bool& isLobby, bool& inGame, sf::RenderWindow& window) = 0;

	virtual void sendToAll(sf::Packet& packet) = 0;

	virtual void sendToAll(sf::Packet& packet, int exclusion) = 0;

	virtual void clientTakesSpot(sf::Packet& packet, int socketNumber) = 0;

	virtual void clientChangeColor(sf::Packet& packet, int socketNumber) = 0;

	virtual void clientChangeUsername(sf::Packet& packet, int socketNumber) = 0;




	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//clientLobby

	virtual bool startLobby(std::string ipAddress) = 0;

	virtual void changeUsernameByNetwork(sf::Packet& packet) = 0;

	virtual void changeColorByNetwork(sf::Packet& packet) = 0; 

	virtual void changeConnectionByNetwork(sf::Packet& packet) = 0; 

	virtual void resetByNetwork(sf::Packet& packet) = 0; 

	virtual void increaseByNetwork(sf::Packet& packet) = 0;

	virtual void decreaseByNetwork(sf::Packet& packet) = 0;

	virtual void getSpotByNetwork(sf::Packet& packet) = 0;



protected:

	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*> sockets;
	int socketIndex[6];

	sf::RectangleShape ipAdressBox;
	sf::Text ipString;



	sf::Texture texture;
	sf::Sprite shape;
	sf::Font font;

	sf::RectangleShape nameOfMapBox;
	sf::Text nameOfMap;

	sf::RectangleShape amountOfPlayersBox;
	sf::Text amountOfPlayer;
	int amountOfPlayerValue = 3;

	sf::Sprite increase;
	sf::Sprite decrease;
	sf::Texture textureOfIncrease;
	sf::Texture textureOfDecrease;

	sf::RectangleShape playerBoxes[6];

	sf::RectangleShape usernameBoxes[6];
	sf::Text username[6];

	sf::RectangleShape connectionBoxes[6];
	sf::Text connection[6];

	sf::Texture textureOfStartButton;
	sf::Sprite startButton;
	sf::Text startText;

	bool button = false;
	bool multiplayer = false;

	int typeInField = -1;

	bool isWarning = false;
	Warning warning;		
};

