#include "rollTheDice.h"

RollTheDice::RollTheDice()
{

}

void RollTheDice::start()
{
	

	rollTheDiceSoundBuffer.loadFromFile("Sound/Snap.wav");
	rollTheDiceSound.setBuffer(rollTheDiceSoundBuffer);
	rollTheDiceSound.setVolume(1);

	shape.setSize(sf::Vector2f(325, 175));
	shape.setPosition(sf::Vector2f(1920 / 2 - shape.getGlobalBounds().width / 2, 1080 / 2 - shape.getGlobalBounds().height / 2));
	shape.setFillColor(sf::Color::Black);

	for (int i = 0; i < 6; i++)
	{
		std::string value = std::to_string(i + 1);
		cubeAmount[i].loadFromFile("pictures/dice" + value + ".png");
	}


	for (int i = 0; i < 3; i++)
	{
		cubes[i].setPosition(sf::Vector2f(shape.getPosition().x + 25 + i * 100, shape.getPosition().y + 25));
		int startValue = rand() % 6;
		cubes[i].setTexture(cubeAmount[startValue]);
		currentValue[i] = startValue;
	}

	font.loadFromFile("Lato-Regular.ttf");
	rolling.setFont(font);
	rolling.setCharacterSize(35);
	rolling.setString("roll!");
	rolling.setPosition(sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width - 25 - rolling.getGlobalBounds().width, shape.getPosition().y + shape.getGlobalBounds().height - 25 - rolling.getGlobalBounds().height));

}

void RollTheDice::setAmountOfCubes(int amount)
{
	this->amountOfCubes = amount;
	this->finalValues.clear();
}

std::vector<int>* RollTheDice::run()
{
	this->resetInteraction();
	int interaction = this->getInteraction();

	if (isRolling)
	{
		bool result = this->rollingTheDice();
		if (result)
		{
			isRolling = false;
			finishedRolling = true;
		}
	}
	else if (interaction != 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !button)
	{
		button = true;
	}
	else if (button && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && interaction != 0)
	{
		button = false;

		if (interaction == 1)
		{

			if (!finishedRolling)
			{
				isRolling = true;
			}
			else
			{
				finishedRolling = false;
				interval = 0.01;
				return &finalValues;
			}
		}

	}

	return NULL;

}

bool RollTheDice::rollingTheDice()
{
	if (interval < 0.5)
	{
		if (clock.getElapsedTime().asSeconds() >= interval)
		{
			
			rollTheDiceSound.play();
			clock.restart();

			interval *= 1.2;

			for (int i = 0; i < amountOfCubes; i++)
			{
				int value = rand() % 6;

				while (value == currentValue[i])
				{
					value = rand() % 6;
				}
				currentValue[i] = value;


				cubes[i].setTexture(cubeAmount[value]);
			}


		}
	}
	else
	{
		std::vector<int> result;

		for (int i = 0; i < amountOfCubes; i++)
		{
			finalValues.push_back(currentValue[i] + 1);
		}

		rolling.setString("Ok!");

		return true;
	}

	return false;
}

int RollTheDice::getInteraction()
{
	sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	if (rolling.getGlobalBounds().contains(position))
	{
		rolling.setFillColor(sf::Color::Red);
		return 1;
	}
	return -1;
}

void RollTheDice::resetInteraction()
{
	rolling.setFillColor(sf::Color::White);
}

void RollTheDice::draw(sf::RenderWindow& window)
{
	window.draw(shape);

	for (int i = 0; i < amountOfCubes; i++)
	{
		window.draw(cubes[i]);
	}

	window.draw(rolling);

}