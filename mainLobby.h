#pragma once

#include "lobby.h"
#include <SFML/Audio.hpp>

class MainLobby : public Lobby
{
public:

	MainLobby();

	void startLobby(int gameMode);

	int getInteraction();

	void resetInteraction();

	void run(sf::RenderWindow& window, sf::Event* event, Game** game, bool& isLobby, bool& inGame);

	void changeColor(int interaction);

	void changeConnection(int interaction);

	void start(Game** game, bool& isLobby, bool& inGame, sf::RenderWindow& window);



	void draw(sf::RenderWindow& window);

	void sendToAll(sf::Packet& packet);

	void sendToAll(sf::Packet& packet, int exclusion);

	void clientTakesSpot(sf::Packet& packet, int socketNumber);

	void clientChangeColor(sf::Packet& packet, int socketNumber);

	void clientChangeUsername(sf::Packet& packet, int socketNumber);



	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//functions of ClientLobby which wont be used by mainLobby
	
	bool startLobby(std::string ipAddress) { return false; }

	void changeUsernameByNetwork(sf::Packet& packet) {}

	void changeColorByNetwork(sf::Packet& packet) {}

	void changeConnectionByNetwork(sf::Packet& packet) {}

	void resetByNetwork(sf::Packet& packet) {}

	void increaseByNetwork(sf::Packet& packet) {}

	void decreaseByNetwork(sf::Packet& packet) {}

	void getSpotByNetwork(sf::Packet& packet){}



private:

	sf::Sound lobbySound;
	sf::SoundBuffer newConnection;

	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*> sockets;
	int socketIndex[6];

	sf::RectangleShape ipAdressBox;
	sf::Text ipString;

	int typeInField = -1;

	bool multiplayer = false;

};

