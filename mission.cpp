#include "mission.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Mission::Mission
///
/// Summary:	Constructor.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// indexOfMission - 	The index of mission. 
/// position - 		 	The position where the mission will be placed on the missionBoard. 
////////////////////////////////////////////////////////////////////////////////////////////////////

Mission::Mission(int indexOfMission, sf::Vector2f position)
{
	font.loadFromFile("Lato-Regular.ttf");

	index = indexOfMission;

	shape[0].position = sf::Vector2f(position.x + 4, position.y + 4);
	shape[1].position = sf::Vector2f(shape[0].position.x, shape[0].position.y + 52);
	shape[2].position = sf::Vector2f(shape[0].position.x + 44, shape[0].position.y + 10);
	shape[3].position = sf::Vector2f(shape[2].position.x, shape[1].position.y + 20);
	shape[4].position = sf::Vector2f(shape[2].position.x + 44, shape[0].position.y);
	shape[5].position = sf::Vector2f(shape[4].position.x, shape[1].position.y);

	std::ifstream file;
	std::string line;

	file.open("text/world_map/missions.txt");

	std::getline(file, line);

	while (line != std::to_string(index))
	{
		if (!std::getline(file, line))
		{
			break;
		}
	}

	if (line == std::to_string(index))
	{
		for (int i = 0; i < 3; i++)
		{
			std::getline(file, line);

			this->line[i].setString(line);
			this->line[i].setCharacterSize(15);
			this->line[i].setFillColor(sf::Color::Black);
			this->line[i].setFont(font);
			this->line[i].setPosition(sf::Vector2f(shape[2].position.x - this->line[i].getGlobalBounds().width / 2, shape[2].position.y + i * 15));
		}
	}
	file.close();




}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Mission::check
///
/// Summary:	Checks if the mission is completed.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// player - 	 	[in,out] the player. 
/// continents - 	[in,out] the continents. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Mission::check(Player* player, std::vector<Continent*>* continents, int citiesBeforeAttacking, int countriesBeforeAttacking, std::vector<int> continentsWithoutPlayer)
{

	if (this->solvedBy == NULL)
	{
		//	0  //
		if (this->index == 0)
		{
			//control Asia
			if (player->isYourContinent(continents->at(4)))
			{
				this->solvedBy = player;
				player->missions++;

			}
		}
		//	1  //
		else if (this->index == 1)
		{
			//conquer 4 cities in one turn
			if (player->amountOfCities() - citiesBeforeAttacking >= 4)
			{
				this->solvedBy = player;
				player->missions++;
			}
		}
		//	2  //
		else if (this->index == 2)
		{
			//control North America
			if (player->isYourContinent(continents->at(2)))
			{
				this->solvedBy = player;
				player->missions++;

			}
		}
		//	3  //
		else if (this->index == 3)
		{
			//control Europe
			if (player->isYourContinent(continents->at(3)))
			{
				this->solvedBy = player;
				player->missions++;

			}

		}
		//	4  //
		else if (this->index == 4)
		{
			//control 1 enemy capital

			int amountOfEnemyCapitals = player->amountOfCapitals();

			if (player->hasOwnCapital() == true)
			{
				amountOfEnemyCapitals--;
			}

			if (amountOfEnemyCapitals >= 1)
			{
				this->solvedBy = player;
				player->missions++;
			}

		}
		//	5  //
		else if (this->index == 5)
		{
			//control 8 cities
			if (player->amountOfCities() >= 8)
			{
				this->solvedBy = player;
				player->missions++;

			}

		}
		//	6  //
		else if (this->index == 6)
		{
			//control 2 continents
			int counter = 0;
			for (auto i : *continents)
			{
				if (player->isYourContinent(i))
				{
					counter++;
				}
			}
			if (counter >= 2)
			{
				this->solvedBy = player;
				player->missions++;
			}
		}
		//	7  //
		else if (this->index == 7)
		{
			//control 2 enemy capitals
			int amountOfEnemyCapitals = player->amountOfCapitals();

			if (player->hasOwnCapital() == true)
			{
				amountOfEnemyCapitals--;
			}
		
			if (amountOfEnemyCapitals >= 2)
			{
				this->solvedBy = player;
				player->missions++;
			}

		}
		//	8  //
		else if (this->index == 8)
		{
			//Control 11 cities
			if (player->amountOfCities() >= 11)
			{
				this->solvedBy = player;
				player->missions++;

			}
		}
		//	9  //
		else if (this->index == 9)
		{
			//conquer a continent in one turn
			for (auto i : continentsWithoutPlayer)
			{
				if (player->isYourContinent(continents->at(i)))
				{
					this->solvedBy = player;
					player->missions++;
					break;
				}
			}
		}
		//	10  //
		else if (this->index == 10)
		{
			//control 20 countries
			 if (player->amountOfCountries() >= 20)
						{
							this->solvedBy = player;
							player->missions++;
			
						}
		}
		//	11  //
		else if (this->index == 11)
		{
			//conquer 10 countries in one turn
			if (player->amountOfCountries() - countriesBeforeAttacking >= 10)
			{
				this->solvedBy = player;
				player->missions++;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Mission::hasAccomplished
///
/// Summary:	Query if 'player' has accomplished the mission.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// player - 	[in,out] If non-null, the player. 
///
/// Returns:	True if the player has accomplished the mission, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Mission::hasAccomplished(Player* player)
{
	if (this->solvedBy == player)
	{
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Mission::draw
///
/// Summary:	Draws the mission in the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Mission::draw(sf::RenderWindow& window)
{
	if (this->solvedBy == NULL)
	{
		window.draw(shape);
		for (int i = 0; i < 3; i++)
		{
			window.draw(line[i]);
		}
	}
}




int Mission::getIndex()
{
	return this->index;
}