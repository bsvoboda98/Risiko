#pragma once
#include "game.h"
class HostGame : public Game
{
public:
	HostGame();

	void startGame(int amountOfPlayerValue, std::vector<std::string>* username, std::vector<sf::Color>* playerColor) {}  //LOCAL GAME

	void startGame(int amountOfPlayerValue, std::vector<std::string>* username, std::vector<sf::Color>* playerColor, std::vector<sf::TcpSocket*> sockets, int indexOfHost);  //HOST GAME

	void startGame(int amountOfPlayerValue, std::vector<std::string>* username, std::vector<sf::Color>* playerColor, sf::TcpSocket* socket, int indexOfClient) {}  //CLIENT GAME


	////////////////////////////////////////////////////////////////////////////////////////////////////


	void confirming(sf::RenderWindow& window);

	void choosing(sf::RenderWindow& window);

	void menuInterface(sf::RenderWindow& window, bool& inGame, bool& isMenu);

	void leftMouseButtonPressed(sf::RenderWindow& window);

	void draw(sf::RenderWindow& window, sf::View* mapView);

	void sendToAll(sf::Packet packet);

	void areAllReady();

	void runPlaceMode();

	void runAttackMode(sf::RenderWindow& window);

	void runMoveMode(sf::RenderWindow& window);

	void modifyChat(sf::Uint32 unicode);

	void changeActivePlayer() {}

	void receive(sf::RenderWindow& window);

	void rollingTheDices();

	void waitForCubes();

private:

	std::vector<sf::TcpSocket*> clients;

};


