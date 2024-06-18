#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "game.h"
#include "warning.h"
#include "lobby.h"
class ClientLobby : public Lobby
{
public:
	ClientLobby(); 

	bool startLobby(std::string ipAddress);

	int getInteraction();

	void resetInteraction();

	void run(sf::RenderWindow& window, sf::Event* event, Game** game, bool& isLobby, bool& inGame);

	void changeColor();

	void changeUsernameByNetwork(sf::Packet& packet);

	void changeColorByNetwork(sf::Packet& packet);

	void changeConnectionByNetwork(sf::Packet& packet); 

	void resetByNetwork(sf::Packet& packet); 

	void increaseByNetwork(sf::Packet& packet);

	void decreaseByNetwork(sf::Packet& packet);

	void getSpotByNetwork(sf::Packet& packet);

	void start(Game** game, bool& isLobby, bool& inGame, sf::RenderWindow& window);  

	void draw(sf::RenderWindow& window);



	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//functions of MainLobby which wont be used by clientLobby

	void startLobby(int gameMode){}

	void changeColor(int interaction){}

	void changeConnection(int interaction){}

	virtual void start(Game** game, bool& isLobby, bool& inGame, sf::RenderWindow& window, std::vector<sf::TcpSocket*>* sockets){}

	void sendToAll(sf::Packet& packet){}

	void sendToAll(sf::Packet& packet, int exclusion){}

	void clientTakesSpot(sf::Packet& packet, int socketNumber){}

	void clientChangeColor(sf::Packet& packet, int socketNumber){}

	void clientChangeUsername(sf::Packet& packet, int socketNumber){}

private:
	sf::TcpSocket* host = new sf::TcpSocket();
	int spot = -1;
	sf::Sprite playerBoxIndicator[6];
	sf::Texture textureOfIndicator;
	bool isTyping = false;

};

