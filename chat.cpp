#include "chat.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Chat::Chat
///
/// Summary:	Default constructor which creates the Chat window and the lines of the chat.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

Chat::Chat()
{
	chatShape.setSize(sf::Vector2f(400, 400));
	chatShape.setFillColor(sf::Color::Black);
	chatShape.setPosition(1200, 1080 - 50 - chatShape.getGlobalBounds().height);

	font.loadFromFile("Lato-Regular.ttf");

	for (int i = 0; i < 11; i++)
	{
		authors[i].setCharacterSize(20);
		authors[i].setFont(font);
		authors[i].setString("");
		authors[i].setPosition(sf::Vector2f(chatShape.getPosition().x + 10, chatShape.getPosition().y + i * 30 + 20));

		chatBodies[i].setCharacterSize(20);
		chatBodies[i].setFont(font);
		chatBodies[i].setString("");
		chatBodies[i].setPosition(sf::Vector2f(authors[i].getPosition().x + 150, authors[i].getPosition().y));
	
		
	}

	enteredText.setCharacterSize(20);
	enteredText.setFont(font);
	enteredText.setString("");
	enteredText.setPosition(authors[10].getPosition().x, authors[10].getPosition().y + 30);
	enteredText.setFillColor(sf::Color::Black);

	enteredTextShape.setSize(sf::Vector2f(chatShape.getSize().x - 20, enteredText.getCharacterSize() + 5));
	enteredTextShape.setPosition(sf::Vector2f(chatShape.getPosition().x + 10, enteredText.getPosition().y - 2.5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Chat::run
///
/// Summary:	script for the Chat which defines the actions of each frame.
///
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Chat::run(sf::RenderWindow& window)
{
	this->draw(window);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Chat::textEntered
///
/// Summary:	adds the entered Text to the String in the input shape.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// unicode -  	The unicode of the entered Text. 
/// username - 	The username of the typing player. 
/// color -    	The color of the typing player. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Chat::textEntered(sf::Uint32 unicode, std::string username, sf::Color color)
{
	if (unicode == 13)
	{
		this->newMessage("", username, color);
	}
	else if (unicode != 8)
	{
		enteredText.setString(enteredText.getString() + unicode);
		if (enteredText.getPosition().x + enteredText.getGlobalBounds().width > enteredTextShape.getPosition().x + enteredTextShape.getGlobalBounds().width)
		{
			std::string reducedUsername = enteredText.getString();
			enteredText.setString(reducedUsername.substr(0, (int)reducedUsername.size() - 1));
		}
	}
	else
	{
		std::string reducedUsername = enteredText.getString();
		enteredText.setString(reducedUsername.substr(0, (int)reducedUsername.size() - 1));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Chat::newMessage
///
/// Summary:	Puts a new Message in the qeue - the messages will be shown in the new position.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// message -  	The new message. 
/// username - 	The username of the player who typed the message. 
/// color -    	The colorof the player who typed the message.
////////////////////////////////////////////////////////////////////////////////////////////////////

void Chat::newMessage(std::string message, std::string username, sf::Color color)
{
	if (message == "")
	{
		if (enteredText.getString() != "")
		{
			messages.push_back(enteredText.getString());
			if ((int)username.size() < 14)
			{
				usernames.push_back(username);
			}
			else
			{

				sf::Text help;
				help.setCharacterSize(20);
				help.setFont(font);
				help.setString(username);
				help.setPosition(sf::Vector2f(chatShape.getPosition().x + 10, chatShape.getPosition().y + 20));

				for (int i = 0; i < (int)username.length(); i++)
				{
					
					if (help.findCharacterPos(i).x > chatBodies[0].getPosition().x)
					{
						usernames.push_back(username.substr(0, i - 1));
						break;
					}
				}
			}
			usercolors.push_back(color);
			enteredText.setString("");
		}
		else
		{
			return;
		}
	}
	else
	{
		messages.push_back(message);
	}

	
	int counter = 0;

	if ((int)message.size() > 25)
	{
		messages.erase(messages.begin());
		usernames.erase(usernames.begin());
		usercolors.erase(usercolors.begin());
	}


	for (int i = (int)messages.size() - 1; i > (int)messages.size() - 12; i--)
	{
		if (i >= 0)
		{
			chatBodies[10 - counter].setString(messages[i]);
			authors[10 - counter].setString(usernames[i]);
			authors[10 - counter].setFillColor(usercolors[i]);
			counter++;
		}
	}

	if (chatBodies[10].getPosition().x + chatBodies[10].getGlobalBounds().width - chatShape.getPosition().x > 400)
	{
		for (int i = 0; i < (int)chatBodies[10].getString().getSize(); i++)
		{
			if (chatBodies[10].findCharacterPos(i).x > chatShape.getPosition().x + chatShape.getGlobalBounds().width)
			{
				std::string nextMessage = messages.back().substr(i - 2, messages.back().length());
				enteredText.setString(nextMessage);
				messages.back() = messages.back().substr(0, i - 2);
				chatBodies[10].setString(messages.back());
				newMessage("", "", color);
			}
		}
	}
}

void Chat::newNetworkMessage(std::string username, sf::Color color, std::string message)
{
	if (message != "")
	{
		messages.push_back(message);
		if ((int)username.size() < 14)
		{
			usernames.push_back(username);
		}
		else
		{

			sf::Text help;
			help.setCharacterSize(20);
			help.setFont(font);
			help.setString(username);
			help.setPosition(sf::Vector2f(chatShape.getPosition().x + 10, chatShape.getPosition().y + 20));

			for (int i = 0; i < (int)username.length(); i++)
			{

				if (help.findCharacterPos(i).x > chatBodies[0].getPosition().x)
				{
					usernames.push_back(username.substr(0, i - 1));
					break;
				}
			}
		}
		usercolors.push_back(color);
	}
	else
	{
		return;
	}
	
	int counter = 0;

	if ((int)messages.size() > 25)
	{
		messages.erase(messages.begin());
		usernames.erase(usernames.begin());
		usercolors.erase(usercolors.begin());
	}


	for (int i = (int)messages.size() - 1; i > (int)messages.size() - 12; i--)
	{
		if (i >= 0)
		{
			chatBodies[10 - counter].setString(messages[i]);
			authors[10 - counter].setString(usernames[i]);
			authors[10 - counter].setFillColor(usercolors[i]);
			counter++;
		}
	}

	if (chatBodies[10].getPosition().x + chatBodies[10].getGlobalBounds().width - chatShape.getPosition().x > 400)
	{
		for (int i = 0; i < (int)chatBodies[10].getString().getSize(); i++)
		{
			if (chatBodies[10].findCharacterPos(i).x > chatShape.getPosition().x + chatShape.getGlobalBounds().width)
			{
				std::string nextMessage = messages.back().substr(i - 2, messages.back().length());
				messages.back() = messages.back().substr(0, i - 2);
				chatBodies[10].setString(messages.back());
				newNetworkMessage("", color, nextMessage);
			}
		}
	}


}




////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Chat::draw
///
/// Summary:	Draws the Chat into the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Chat::draw(sf::RenderWindow& window)
{
	window.draw(chatShape);
	window.draw(enteredTextShape);

	window.draw(enteredText);
	for (int i = 0; i < 11; i++)
	{
		window.draw(chatBodies[i]);
		window.draw(authors[i]);
	}
}


std::string Chat::getMessageForSending()
{
	std::string message = enteredText.getString();
	enteredText.setString("");
	return message;
}