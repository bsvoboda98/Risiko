#include "confirm.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Confirm::Confirm
///
/// Summary:	Default constructor of the ConfirmWindow.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

Confirm::Confirm()
{
	font.loadFromFile("Lato-Regular.ttf");
	confirm.setFillColor(sf::Color(100, 100, 100, 235));
	confirm.setSize(sf::Vector2f(170, 100));
	confirm.setOutlineColor(sf::Color::Black);
	confirm.setOutlineThickness(3);


	yes.setString("yes");
	no.setString("no");
	yes.setFillColor(sf::Color::Green);
	no.setFillColor(sf::Color::Red);


	//question1.setFillColor()
	yes.setCharacterSize(20);
	no.setCharacterSize(20);
	question1.setCharacterSize(20);
	question2.setCharacterSize(20);
	theme.setCharacterSize(20);

	yes.setFont(font);
	no.setFont(font);
	question1.setFont(font);
	question2.setFont(font);
	theme.setFont(font);


}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Confirm::placeConfirm
///
/// Summary:	Place confirm with the correct question on the mousePosition.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// questionPart1 - 	The first question part. 
/// object - 			The object of the confirmQuestion. 
/// questionPart2 - 	The second question part. 
/// window - 			[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Confirm::placeConfirm(std::string questionPart1, std::string object, std::string questionPart2, sf::RenderWindow& window)
{
	sf::Vector2i rectanglePosition = sf::Mouse::getPosition();
	confirm.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	
	

	if (sf::Mouse::getPosition().x > window.getSize().x / 2)
	{
		confirm.setPosition(sf::Mouse::getPosition().x - 150, sf::Mouse::getPosition().y);
	}

	

	question1.setString(questionPart1);
	question2.setString(questionPart2);
	theme.setString(object);

	question1.setPosition(confirm.getPosition().x + confirm.getGlobalBounds().width / 2 - question1.getGlobalBounds().width / 2, confirm.getPosition().y + confirm.getGlobalBounds().height * 0.05);

	theme.setPosition(confirm.getPosition().x + confirm.getGlobalBounds().width / 2 - theme.getGlobalBounds().width / 2, confirm.getPosition().y + confirm.getGlobalBounds().height * 0.25);

	question2.setPosition(confirm.getPosition().x + confirm.getGlobalBounds().width / 2 - question2.getGlobalBounds().width / 2, confirm.getPosition().y + confirm.getGlobalBounds().height * 0.45);


	yes.setPosition(confirm.getPosition().x + confirm.getGlobalBounds().width * 0.05, confirm.getPosition().y + confirm.getGlobalBounds().height * 0.65);
	no.setPosition(confirm.getPosition().x + confirm.getGlobalBounds().width * 0.80, confirm.getPosition().y + confirm.getGlobalBounds().height * 0.65);




}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Confirm::resetInteraction
///
/// Summary:	Resets the interaction with yes or no.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void Confirm::resetInteraction()
{
	yes.setFillColor(sf::Color::Green);
	no.setFillColor(sf::Color::Red);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Confirm::getInteraction
///
/// Summary:	Gets the interaction with yes or no.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	The interaction.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Confirm::getInteraction()
{
	if (yes.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		yes.setFillColor(sf::Color::White);
		return 1;
	}
	else if (no.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
	{
		no.setFillColor(sf::Color::White);
		return 2;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Confirm::run
///
/// Summary:	script for the confirmWindow which defines the actions of each frame.
///.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
///
/// Returns:	An int.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Confirm::run(sf::RenderWindow& window)
{
	this->resetInteraction();
	int interaction = this->getInteraction();

	this->draw(window);
	return interaction;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Confirm::draw
///
/// Summary:	Draws the confirmWindow into the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Confirm::draw(sf::RenderWindow& window)
{
	window.draw(confirm);
	window.draw(yes);
	window.draw(no);
	window.draw(question1);
	window.draw(theme);
	window.draw(question2);
}
