#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Chat
{
public:
	Chat();

	void run(sf::RenderWindow& window);

	void textEntered(sf::Uint32 unicode, std::string username, sf::Color color);

	void newMessage(std::string message, std::string username, sf::Color color);

	void newNetworkMessage(std::string username, sf::Color color, std::string message);

	std::string getMessageForSending();

	void draw(sf::RenderWindow& window);


private:
	sf::Font font;


	sf::RectangleShape chatShape;
	sf::Text chatBodies[11];
	sf::Text authors[11];
	std::vector<std::string> messages;
	std::vector<std::string> usernames;
	std::vector<sf::Color> usercolors;

	sf::RectangleShape enteredTextShape;
	sf::Text enteredText;

};

