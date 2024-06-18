#include "map.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Map		:: Construcotr liest die Borders und Surfaces der Countries aus einer .txt Datei                 //
//                                                                                                           //
//variable	::                                                                                               //
//			::                                                                                               //
//                                                                                                           //
//                                                                                                           //
//return	:: no return                                                                                     //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Map::Map()
{

}


void Map::start()
{
	
	//create the ocean in the background of the Map.
	
	
	ocean.setSize(sf::Vector2f(1920, 1080));
	oceanTexture.loadFromFile("pictures/water.jpg");
	oceanTexture.setRepeated(true);
	ocean.setTexture(&oceanTexture);
	oceanShader.loadFromFile("Shader/oceanShader.frag", sf::Shader::Fragment);
	oceanShader.setUniform("texture", sf::Shader::CurrentTexture);



	//operators for reading the lines of the txt
	std::ifstream file;
	std::string line;

	//variables to write in the correct fields of the 2-dimensional Array;
	int length;
	int i = 0;
	int realI = i;
	int iteration = 0;
	std::string check;

	//opens the file with the coordinates and the array sizes for the VertexArrays
	file.open("text/world_map/world_borders.txt");

	while (std::getline(file, line)) //next line
	{
		check = line.substr(0, 1);
		if (check == "/")
		{
			std::getline(file, line);
			continue;
		}
		else if (line == "") //if the new line begins
		{
			//read new line
			std::getline(file, line);


			//string to int convert
			std::stringstream sstr_line(line);
			sstr_line >> length;

			//new instance of VertexArray in the Array
			borders[i] = sf::VertexArray(sf::LineStrip, length);

			//read new line
			std::getline(file, line);

			//go to the next field of the array and reset the iteration for the VertexArray
			realI = i;
			i++;
			iteration = 0;
			
		}
		//get the first part of the string (0 till the ",") as x-coordinate
		int strpos = line.find(",");
		std::string first = line.substr(0, strpos);
		std::stringstream sstr_first(first);
		int firstpart;
		sstr_first >> firstpart;

		//get the second part of the string ("," till the end of the line) as y-coordinate
		std::string last = line.substr(strpos + 1, line.length());
		std::stringstream sstr_last(last);
		int lastpart;
		sstr_last >> lastpart;

		//fill the iteration of the right VertexArray with the right coordinates and set the color
		borders[realI][iteration].position = sf::Vector2f(firstpart, lastpart);
		if (realI < 16)
		{
			borders[realI][iteration].color = sf::Color::Black;
		} else
		{
			borders[realI][iteration].color = sf::Color::Black;
		}
		iteration++;
	}
	file.close();

	//create the continents
	
	file.open("text/world_map/continents.txt");

	while (std::getline(file, line)) //next line
	{
		continentsOfMap.push_back(new Continent(line));
	}

	file.close();

	file.open("text/world_map/map_array.txt"); 

	std::stringstream convert;
	std::string convertToIndex;
	for (int x = 0; x < 960; x++)
	{
		for (int y = 0; y < 540; y++)
		{
			std::getline(file, line);
			
			std::stringstream sstr_first(line);
			int index;
			sstr_first >> index;

			if (numberOfCountries < index)
			{
				numberOfCountries = index;
			}

			map_array[x][y] = index;
			
		}
	}
	file.close();
	
	file.open("text/world_map/index_konfig.txt");
	int continent;
	int country;
	for (int i = 0; i < numberOfCountries; i++)
	{
		std::getline(file, line);
		std::string strContinent = line.substr(3, 5);
		std::stringstream sstrContinent(strContinent);
		sstrContinent >> continent;

		std::string strCountry = line.substr(6, 8);
		std::stringstream sstrCountry(strCountry);
		sstrCountry >> country;

		std::vector<int> index;

		indexOfCountry.push_back(index);
		indexOfCountry[i].push_back(continent);
		indexOfCountry[i].push_back(country);

	}
	file.close();
	
	file.open("text/world_map/connections.txt");
	sf::Vector2i test[2];
	while (std::getline(file, line))
	{
		for (int i = 0; i < 2; i++)
		{
			std::getline(file, line);
			//get the first part of the string (0 till the ",") as x-coordinate
			int strpos = line.find(",");
			std::string first = line.substr(0, strpos);
			std::stringstream sstr_first(first);
			int firstpart;
			sstr_first >> firstpart;

			//get the second part of the string ("," till the end of the line) as y-coordinate
			std::string last = line.substr(strpos + 1, line.length());
			std::stringstream sstr_last(last);
			int lastpart;
			sstr_last >> lastpart;

			test[i] = sf::Vector2i(firstpart, lastpart);
		}
		connections.push_back(Connection::Connection(test[0], test[1]));
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Map		:: draw draws all parts of the map into the window                                               //
//             these are : the borders of the continents/countries, the surfaces of the Countries,           //
//             the currentStatus and the currentNumber                                                       //
//                                                                                                           //
//variable	::                                                                                               //
//			::                                                                                               //
//                                                                                                           //
//                                                                                                           //
//return	:: no return                                                                                     //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Map::draw(sf::RenderWindow& window)
{
	oceanShader.setUniform("time", (float) clock.getElapsedTime().asSeconds());
	window.draw(ocean, &oceanShader);

	for (auto j : continentsOfMap)
	{
		j->draw(window);
	}
	
	for (int i = 0; i < NUMBER_OF_WORLD_BORDERS; i++)
	{
		{
			window.draw(borders[i]);
		}	
	}

	

	for (auto& i : connections)
	{
		i.draw(window);
	}

	for (int i = 1; i <= numberOfCountries; i++)
	{
		Country* country = getCountryOfIndex(i);
		country->drawFigure(window);
	}
	


	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Map		:: mapInteraction returns the index of the country the mouse is pointing to.                     //
//             for every 4 pixels on the screen is a number in the map_array.                                //
//             by dividing the mouse position by 2 you get the position of the array the program has to check//
//             in this position of the array is the index of the searched country. the color gets darker there/
//                                                                                                           //
//variable	::                                                                                               //
//			::                                                                                               //
//                                                                                                           //
//                                                                                                           //
//return	:: index of the country.                                                                         //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


int Map::mapInteraction(sf::RenderWindow& window, sf::View* mapView)
{
	window.setView(*mapView);
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	int mousex = worldPos.x / 2;
	int mousey = worldPos.y / 2;
	int mode = 1;

	if (mousex > 0 && mousex < 1920 / 2 && mousey > 0 && mousey < 1080 / 2)
	{
		if (map_array[mousex][mousey] != 0)
		{
			continentsOfMap[indexOfCountry[map_array[mousex][mousey] - 1][0]]->convertInteraction(indexOfCountry[map_array[mousex][mousey] - 1][1], mode);
		}
		window.setView(window.getDefaultView());
		return map_array[mousex][mousey];
	}
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Map		:: resetMapInteraction sets the FillColor of every Country on the Map                            //
//             to its original color.                                                                        //
//                                                                                                           //
//variable	::                                                                                               //
//			::                                                                                               //
//                                                                                                           //
//                                                                                                           //
//return	:: no return                                                                                     //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Map::resetMapInteraction()
{	
	int mode = -1;
	for (Continent* i : continentsOfMap)
	{
		i->convertInteraction(0, mode);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Map		:: placeFigure checks if the given amount can be placed - if not it returns false.               //
//             if placeMode == true it reduces the amount of Figures the player has to place                 //
//             now the amount of figures will be increased by the value of placed Figures.                   //
//             after that the country counts the amount of every type of figures.                            //
//             the next step is to compute how many figures of every type you need for the optimal           //
//             distribution. Now missing figures will be placed and figures which arent needed get deleted.  //
//                                                                                                           //
//variable	::                                                                                               //
//			::                                                                                               //
//                                                                                                           //
//                                                                                                           //
//return	:: bool if the process was succsessfull                                                          //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Map::placeFigure(int index, int value, int mode, int figuresToPlace)
{

	Country* country;
	if (figuresToPlace - value >= 0 || mode == 1)
	{
		
		if (index != -1)
		{
			country = this->getCountryOfIndex(index);
		}
		else
		{
			country = this->getCountryOfIndex(chooseStart);
		}
		country->numberOfFigures += value;
		country->refreshAmount();
		int valueOfFigures = country->numberOfFigures;

		int amount[6];
		int counter[6];

		for (int i = 0; i < 6; i++)
		{
			amount[i] = country->getNumbOfValue(i);
			counter[i] = 0;
		}

		for (int i = 5; i > 0; i -= 2)
		{
			while (valueOfFigures >= i)
			{
				counter[i]++;
				valueOfFigures -= i;
			}
		}
		

		for (int i = 5; i > 0; i -= 2)
		{
			if (counter[i] < amount[i])
			{
				for (int j = 0; j < amount[i] - counter[i]; j++)
				{
					country->deleteFigure(i);
				}
			}
			else if (amount[i] < counter[i])
			{
				for (int j = 0; j < counter[i] - amount[i]; j++)
				{
					
					if (index != -1)
					{
						country->placeFigure(i, players->at(getCountryOfIndex(index)->indexOfOwner)->getColor());
					}
					else
					{
						country->placeFigure(i, players->at(getCountryOfIndex(chooseStart)->indexOfOwner)->getColor());
					}
					
				}
			}
		}
		
		return true;
	}
	else
	{
		return false;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Map		:: deleteFigure - the amount of figures will be increased by the value of placed Figures.		 //
//             after that the country counts the amount of every type of figures.                            //
//             the next step is to compute how many figures of every type you need for the optimal           //
//             distribution. Now missing figures will be placed and figures which arent needed get deleted.  //                                                   
//                                                                                                           //
//variable	::                                                                                               //
//			::                                                                                               //
//                                                                                                           //
//                                                                                                           //
//return	:: no return                                                                                     //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Map::deleteFigure(int index, int value)
{
	Country* country = this->getCountryOfIndex(index);
	if (country->numberOfFigures >= value)
	{
		country->numberOfFigures -= value;
		country->refreshAmount();

		int valueOfFigures = country->numberOfFigures;

		int amount[6];
		int counter[6];

		for (int i = 5; i > 0; i -= 2)
		{
			amount[i] = country->getNumbOfValue(i);
			counter[i] = 0;
		}

		for (int i = 5; i > 0; i -= 2)
		{
			while (valueOfFigures >= i)
			{
				counter[i]++;
				valueOfFigures -= i;
			}
		}

		for (int i = 5; i > 0; i -= 2)
		{
			if (counter[i] < amount[i])
			{
				for (int j = 0; j < amount[i] - counter[i]; j++)
				{
					country->deleteFigure(i);
				}
			}
			else if (amount[i] < counter[i])
			{
				for (int j = 0; j < counter[i] - amount[i]; j++)
				{
					country->placeFigure(i, players->at(getCountryOfIndex(index)->indexOfOwner)->getColor());
				}
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Map		:: draw draws all parts of the map into the window                                               //
//             these are : the borders of the continents/countries, the surfaces of the Countries,           //
//             the currentStatus and the currentNumber                                                       //
//                                                                                                           //
//variable	::                                                                                               //
//			::                                                                                               //
//                                                                                                           //
//                                                                                                           //
//return	:: no return                                                                                     //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Map::attack(Player* player, int& lossOfAttacker, int& lossOfDefender, MenuTopBar* topBar)
{
	
	

	

	Country* attacker = this->getCountryOfIndex(chooseStart);
	Country* defender = this->getCountryOfIndex(chooseGoal);
	
	if (attacker->numberOfFigures - chooseAmount > 0)
	{

		int amountOfDefender = 0;

		if (defender->numberOfFigures >= 2)
		{
			amountOfDefender = 2;
		}
		else
		{
			amountOfDefender = 1;
		}

		std::vector<int> cubesOfAttacker;
		std::vector<int> cubesOfDefender;

		for (int i = 0; i < chooseAmount; i++)
		{
			cubesOfAttacker.push_back(rand() % 6 + 1);
		}
		for (int i = 0; i < amountOfDefender; i++)
		{
			cubesOfDefender.push_back(rand() % 6 + 1);
		}

		std::sort(cubesOfAttacker.begin(), cubesOfAttacker.end(), std::greater<int>());
		std::sort(cubesOfDefender.begin(), cubesOfDefender.end(), std::greater<int>());

		if (cubesOfAttacker[0] > cubesOfDefender[0])
		{

			lossOfDefender++;
		}
		else
		{

			lossOfAttacker++;
		}

		if (chooseAmount >= 2 && amountOfDefender >= 2)
		{
			if (cubesOfAttacker[1] > cubesOfDefender[1])
			{
				lossOfDefender++;
			}
			else
			{
				lossOfAttacker++;
			}
		}



		deleteFigure(chooseStart, lossOfAttacker);
		deleteFigure(chooseGoal, lossOfDefender);

		if (defender->numberOfFigures == 0)
		{

			topBar->giveNews(player->getUsername() + " conquered " + defender->getName() + ".");
			this->deleteFigure(chooseStart, chooseAmount);
			this->takePossesion(chooseGoal, chooseAmount, player);
			player->getCard();
			if (players->at(defender->indexOfOwner)->amountOfCountries() == 0)
			{
				topBar->giveNews(players->at(defender->indexOfOwner)->getUsername() + " is eliminated!");
				players->at(defender->indexOfOwner)->eliminate();

				
			}
		}
		return true;
	}
	else
	{
		return false;
	}

	

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Map		:: draw draws all parts of the map into the window                                               //
//             these are : the borders of the continents/countries, the surfaces of the Countries,           //
//             the currentStatus and the currentNumber                                                       //
//                                                                                                           //
//variable	::                                                                                               //
//			::                                                                                               //
//                                                                                                           //
//                                                                                                           //
//return	:: no return                                                                                     //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Map::move()
{
	Country* start = getCountryOfIndex(chooseStart);
	if (start->numberOfMovedFigures <= start->numberOfFigures - chooseAmount && (start->numberOfFigures - chooseAmount) > 0)
	{
		deleteFigure(chooseStart, chooseAmount);
		placeFigure(chooseGoal, chooseAmount, 1, 0);
		getCountryOfIndex(chooseGoal)->numberOfMovedFigures += chooseAmount;
		return 0;
	}
	else
	{
		return 1;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Map		:: draw draws all parts of the map into the window                                               //
//             these are : the borders of the continents/countries, the surfaces of the Countries,           //
//             the currentStatus and the currentNumber                                                       //
//                                                                                                           //
//variable	::                                                                                               //
//			::                                                                                               //
//                                                                                                           //
//                                                                                                           //
//return	:: no return                                                                                     //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Country* Map::getCountryOfIndex(int index)
{
	return this->continentsOfMap[indexOfCountry[index - 1][0]]->getCountry(indexOfCountry[index - 1][1]);
}


int Map::distributeCountries(int numberOfPlayers)
{
	std::vector<int> mixedCountries;

	for (int i = 0; i < numberOfCountries; i++)
	{
		mixedCountries.push_back(i);
	}

	for (int i = 0; i < numberOfCountries; i++)
	{
		int k = rand() % numberOfCountries;


		int temp = mixedCountries[i];
		mixedCountries[i] = mixedCountries[k];
		mixedCountries[k] = temp;
	}

	int nextPlayer = rand() % numberOfPlayers;
	
	for (auto i : mixedCountries)
	{
		Country* country = getCountryOfIndex(i + 1);
		players->at(nextPlayer)->giveCountry(country);
		country->indexOfOwner = nextPlayer;

		placeFigure(i + 1, 1, 1, 0);

		nextPlayer++;

		if (nextPlayer >= numberOfPlayers)
		{
			nextPlayer = 0;
		}
	}

	float placeableFiguresFloat = (float) numberOfCountries / numberOfPlayers;

	int placeableFiguresInt = ceil(placeableFiguresFloat);

	return placeableFiguresInt;
}

void Map::resetIsMoved()
{
	for (int i = 1; i <= numberOfCountries; i++)
	{
		Country* country = this->getCountryOfIndex(i);
		country->numberOfMovedFigures = 0;
	}
}

void Map::takePossesion(int indexOfDestination, int amount, Player* player)
{
	Country* destination = this->getCountryOfIndex(indexOfDestination);
	Player* oldOwner = players->at(destination->indexOfOwner);
	
	oldOwner->removeCountry(destination);
	player->giveCountry(destination);
	int playerIndex = 0;
	for (int i = 0; i < (int)players->size(); i++)
	{
		if (players->at(i) == player)
		{
			playerIndex = i;
		}
	}


	destination->indexOfOwner = playerIndex;

	this->placeFigure(indexOfDestination, amount, 1, 0);

}



std::vector<Continent*>* Map::getContinentsOfMap()
{
	return &continentsOfMap;
}




void Map::givePlayers(std::vector<Player*>* playerList)
{
	this->players = playerList;
}


void Map::getContinentsWithoutPlayer(Player* player, std::vector<int>* continentsWithout)
{
	for (int i = 0; i < (int )continentsOfMap.size(); i++)
	{
		bool isContinentWithoutPlayer = true;
		for (int j = 0; j < continentsOfMap[i]->getAmountOfCountries(); j++)
		{
			if (player->isYourCountry(continentsOfMap[i]->getCountry(j)))
			{
				isContinentWithoutPlayer = false;
			}
			if (j = continentsOfMap[i]->getAmountOfCountries() - 1)
			{
				if (isContinentWithoutPlayer == true)
				{
					continentsWithout->push_back(i);
				}
			}
		}
	}
}



int Map::getNumberOfCountries()
{
	return this->numberOfCountries;
}