#include "figureBoard.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	FigureBoard::FigureBoard
///
/// Summary:	places the figureBoard on the given Position.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// position - 	The position. 
////////////////////////////////////////////////////////////////////////////////////////////////////

FigureBoard::FigureBoard() {};

void FigureBoard::start(sf::Vector2f position)
{
	texture.loadFromFile("pictures/star1.png");
	font.loadFromFile("Lato-Regular.ttf");
	shape.setSize(sf::Vector2f(247, 90));
	shape.setPosition(position);
	shape.setFillColor(sf::Color::Black);
	starBox[0].setPosition(shape.getPosition().x + 7, shape.getPosition().y + 7);
	for (int i = 0; i < 3; i++)
	{
		starBox[i].setSize(sf::Vector2f(32, 16));
		if (i != 0)
		{
			starBox[i].setPosition(figureBox[i-1].getPosition().x + figureBox[i-1].getGlobalBounds().width + 6, starBox[i-1].getPosition().y);
		}
		starBox[i].setFillColor(sf::Color::Black);
		starBox[i].setOutlineThickness(2);
		starBox[i].setOutlineColor(sf::Color(60, 60, 60));
		stars[i].setTexture(texture);
		stars[i].setOrigin(13, 13);
		stars[i].setPosition(sf::Vector2f(starBox[i].getPosition().x + 16, starBox[i].getPosition().y + 8));
		stars[i].setColor(sf::Color::Red);
		stars[i].setScale(0.5, 0.5);

		figureBox[i].setSize(sf::Vector2f(32, 16));
		figureBox[i].setPosition(starBox[i].getPosition().x + starBox[i].getGlobalBounds().width + 3, starBox[i].getPosition().y);
		figureBox[i].setFillColor(sf::Color::Black);
		figureBox[i].setOutlineThickness(2);
		figureBox[i].setOutlineColor(sf::Color(60, 60, 60));
		figures[i] = new Figure(7, sf::Vector2i(figureBox[i].getPosition().x + 16, figureBox[i].getPosition().y + 8), sf::Color(155, 155, 155));


		for (int j = 0; j < 3; j++)
		{

			amountBox[j + 3 * i].setSize(sf::Vector2f(32, 16));
			amountBox[j + 3 * i].setPosition(starBox[i].getPosition().x, starBox[i].getPosition().y + starBox[i].getGlobalBounds().height + j * (amountBox[j + i * 3].getGlobalBounds().height + 2) + 4);
			amountBox[j + 3 * i].setFillColor(sf::Color(120, 2, 20));
			amountBox[j + 3 * i].setOutlineThickness(2);
			amountBox[j + 3 * i].setOutlineColor(sf::Color(60, 60, 60));

			amount[j + 3 * i].setFont(font);
			amount[j + 3 * i].setCharacterSize(15);
			amount[j + 3 * i].setString(std::to_string(j + 3 * i + 2));
			amount[j + 3 * i].setPosition(amountBox[j + 3 * i].getPosition().x + 16 - amount[j + 3 * i].getGlobalBounds().width / 2, amountBox[j + 3 * i].getPosition().y + 6 - amount[j + 3 * i].getGlobalBounds().height / 2 - 2);

			

			worthBox[j + 3 * i].setSize(sf::Vector2f(32, 16));
			worthBox[j + 3 * i].setPosition(figureBox[i].getPosition().x, figureBox[i].getPosition().y + figureBox[i].getGlobalBounds().height + j * (worthBox[j + i * 3].getGlobalBounds().height + 2) + 4);
			worthBox[j + 3 * i].setFillColor(sf::Color(180, 180, 180));
			worthBox[j + 3 * i].setOutlineThickness(2);
			worthBox[j + 3 * i].setOutlineColor(sf::Color(60, 60, 60));

			worth[j + 3 * i].setFont(font);
			worth[j + 3 * i].setCharacterSize(15);
			worth[j + 3 * i].setString(std::to_string(worthValue[j + 3 * i]));
			worth[j + 3 * i].setPosition(worthBox[j + 3 * i].getPosition().x + 16 - worth[j + 3 * i].getGlobalBounds().width / 2, worthBox[j + 3 * i].getPosition().y + 6 - worth[j + 3 * i].getGlobalBounds().height / 2 - 2);
			worth[j + 3 * i].setFillColor(sf::Color::Black);

		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	FigureBoard::getWorth
///
/// Summary:	Gets a amount of figures from a given worth.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// amount - 	The worth. 
///
/// Returns:	The amount of figures.
////////////////////////////////////////////////////////////////////////////////////////////////////

int FigureBoard::getWorth(int amount)
{
	std::cout << amount << std::endl;
	std::cout << worthValue[amount - 2] << std::endl;
	return worthValue[amount - 2];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	FigureBoard::draw
///
/// Summary:	Draws the FigureBoard in the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void FigureBoard::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	for (int i = 0; i < 3; i++)
	{
		window.draw(starBox[i]);
		window.draw(figureBox[i]);
		for (int j = 0; j < 3; j++)
		{
			window.draw(amountBox[j + 3 * i]);
			window.draw(amount[j + 3 * i]);
			window.draw(worthBox[j + 3 * i]);
			window.draw(worth[j + 3 * i]);
		}
		figures[i]->draw(window);
		window.draw(stars[i]);
	}


}