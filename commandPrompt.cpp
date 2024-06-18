#include "commandPrompt.h"

CommandPrompt::CommandPrompt()
{
	font.loadFromFile("Lato-Regular.ttf");

	shape.setSize(sf::Vector2f(480, 150));
	shape.setFillColor(sf::Color::Black);
	shape.setPosition(960 - shape.getGlobalBounds().width / 2, 540 - shape.getGlobalBounds().height / 2);

	title.setFont(font);
	title.setCharacterSize(45);
	title.setString("ipAddress of the Host :");
	title.setFillColor(sf::Color::White);
	title.setPosition(sf::Vector2f(shape.getPosition().x + 3, shape.getPosition().y));

	enteredTextShape.setSize(sf::Vector2f(shape.getSize().x - 10, 50));
	enteredTextShape.setFillColor(sf::Color::White);
	enteredTextShape.setPosition(sf::Vector2f(shape.getPosition().x + 5, shape.getPosition().y + shape.getGlobalBounds().height - 5 - enteredTextShape.getGlobalBounds().height));


	enteredText.setFont(font);
	enteredText.setCharacterSize(45);
	enteredText.setString("");
	enteredText.setFillColor(sf::Color::Black);
	enteredText.setPosition(sf::Vector2f(enteredTextShape.getPosition().x + 3, enteredTextShape.getPosition().y));
}

std::string CommandPrompt::textEntered(sf::Uint32 unicode)
{
	if (unicode == 13)
	{
		std::string ipAddress = enteredText.getString();
		enteredText.setString("");
		return ipAddress;
	}
	else if (unicode == 27)
	{
		enteredText.setString("");
		return "ESC";
	}
	else if (unicode >= 46 && unicode <= 57 && unicode != 47)
	{
		enteredText.setString(enteredText.getString() + unicode);
		if (enteredText.getPosition().x + enteredText.getGlobalBounds().width > enteredTextShape.getPosition().x + enteredTextShape.getGlobalBounds().width)
		{
			std::string ipAddress = enteredText.getString();
			enteredText.setString(ipAddress.substr(0, (int)ipAddress.size() - 1));
		}
	}
	else if(unicode == 8)
	{
		std::string ipAddress = enteredText.getString();
		enteredText.setString(ipAddress.substr(0, (int)ipAddress.size() - 1));
	}
	return "";
}


void CommandPrompt::draw(sf::RenderWindow& window)
{
	window.draw(shape);

	window.draw(title);
	window.draw(enteredTextShape);
	window.draw(enteredText);

}
