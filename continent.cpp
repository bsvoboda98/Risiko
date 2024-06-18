#include "continent.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Continent::Continent
///
/// Summary:	Constructor. Loads the Continent from a file and creates the countries from this file.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// filename - 	Filename of the file. 
////////////////////////////////////////////////////////////////////////////////////////////////////

Continent::Continent(std::string filename)
{

	std::ifstream file;
	std::string line;

	//Integer of the RGB Code of the color 
	int intColor[3];

	//these Integers will be read as a string
	std::string strColor[3];

	//stringstream to convert the Strings to Integer
	std::stringstream sstrColor;

	//file with the list of the RGB-Codes and filenames for the Countries
	file.open(filename);


	//get the new line
	while (std::getline(file, line))
	{
		std::string check = line.substr(0, 1);
		if (check == "*")
		{
			std::getline(file, line);
			name = line;


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

			boardPosition = sf::Vector2f(firstpart, lastpart);

			std::getline(file, line);
			std::stringstream sstr_count(line);
			sstr_count >> count;


			std::getline(file, line);
			std::stringstream sstr_reward(line);
			sstr_reward >> reward;



			std::getline(file, line);
			continue;
		}

		//file which is responsible for creating the countries
		std::string fileOfCountry = line;

		//line with the file is dont, go to the line with the RGB-Code
		std::getline(file, line);


		//Convert "RRR,GGG,BBB" to 3 Integer
		for (int i = 0; i < 3; i++)
		{
			
			strColor[i] = line.substr(3 * i + i, 3 * (i + 1) + i);
			std::stringstream sstrColor(strColor[i]);
			sstrColor >> intColor[i];
		}
		color = sf::Color(intColor[0], intColor[1], intColor[2]);

		//create a new Country
		countriesOfContinent.push_back(new Country(fileOfCountry, sf::Color(intColor[0], intColor[1], intColor[2])));

		//skip the empty line between the relevant lines
		std::getline(file, line);

	}
	
	board.placeBoard(boardPosition, sf::Color(intColor[0], intColor[1], intColor[2]), name, count, reward);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Continent::draw
///
/// Summary:	Draws the Continent into the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Continent::draw(sf::RenderWindow& window)
{
	for (auto i : countriesOfContinent)
	{
		i->draw(window);
	}
	
	board.draw(window);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Continent::convertInteraction
///
/// Summary:	Convert the interaction and gives the interacting country a darker color.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// country -  	int for country. 
/// mode - 	   	int for mode. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Continent::convertInteraction(int country, int mode)
{
	if (mode == 1)
	{
		countriesOfContinent[country]->setColor(mode);
	}
	else if (mode == -1)
	{
		for (Country* i : countriesOfContinent)
		{
			i->setColor(mode);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Continent::getCountry
///
/// Summary:	Gets the country to the given index (country).
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// country - 	The index of the country in the continent. 
///
/// Returns:	Null if it fails, else the country.
////////////////////////////////////////////////////////////////////////////////////////////////////

Country* Continent::getCountry(int country)
{

	return countriesOfContinent[country];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Continent::getAmountOfCountries
///
/// Summary:	Gets the amount of countries in this continent.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	The amount of countries in the continent.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Continent::getAmountOfCountries()
{
	int size = static_cast<int>(countriesOfContinent.size());

	return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Continent::getReward
///
/// Summary:	Gets the reward of the continent.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	The reward of the continent.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Continent::getReward()
{
	return this->reward;
}