#include "country.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Country	::country sets the original color and reads the coordinates of the surface from a file			 //
//																											 //
//input		:: string filename		: string with the file which contains the coordinates of the surface	 //
//			:: sf::Color color		: the original color of the country										 //
//			:: surface[]			: contains the VertexArrays, that build the surface of the country		 //	
//			:: int figurePosition[]	: contains the positions where the										 //
//																											 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Country::Country(std::string filename, sf::Color color)
{
	
	std::ifstream file;
	std::string line;
	std::string check;

	int length;
	int i = 0;
	int iteration = 0;

	file.open(filename);
	//std::cout << filename << std::endl;
	originalColor[0] = color.r;
	originalColor[1] = color.g;
	originalColor[2] = color.b;

	while (std::getline(file, line))
	{
		

		//"/" as sign for 2 commentary lines
		check = line.substr(0, 1);
		if (check == "/")
		{
			std::getline(file, line);
			continue;
		}
		else if (check == "&")
		{
			font.loadFromFile("Lato-Regular.ttf");
			std::getline(file, line);
			
			name = line;
			countryname.setString(name);
			countryname.setCharacterSize(15);
			amount.setCharacterSize(20);
			countryname.setFont(font);
			amount.setFont(font);
			countryname.setFillColor(sf::Color::Black);
			amount.setFillColor(sf::Color::Black);

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

			countryname.setPosition(sf::Vector2f(firstpart - countryname.getGlobalBounds().width / 2, lastpart - countryname.getGlobalBounds().height / 2));
			amount.setPosition(sf::Vector2f(firstpart - amount.getGlobalBounds().width / 2 - 5, lastpart - amount.getGlobalBounds().height / 2 + 10));

			std::getline(file, line);
			continue;
		}
		else if (check == "-")
		{
			std::getline(file, line);
			check = line.substr(0, 1);

			while (check != "-")
			{
				
				
				std::stringstream sstr_first(line);
				int neighbor;
				sstr_first >> neighbor;

				neighbors.push_back(neighbor);

				std::getline(file, line);
				check = line.substr(0, 1);
			}
			continue;
		}
		//"*" as sign for the definition of the figurePositions (positions where the country can place figures)
		else if (check == "*")
		{
			std::getline(file, line);
			check = line.substr(0, 1);

			while (check != "*")
			{

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


				figurePositions.push_back(sf::Vector2i(firstpart, lastpart));
				figurePositionIsUsed.push_back(false);
		
				std:getline(file, line);
				check = line.substr(0, 1);
				
			}
			
			continue;
		}
		else if (check == "$")
		{
			std::getline(file, line);
			if (line == "1")
			{
				this->hasCity = true;
			}
			std::getline(file, line);
			continue;
		}
		

		//"" as sign for a new VertexArray
		if (line == "")
		{
			i++;
			iteration = 0;

			//read new line
			std::getline(file, line);

			std::stringstream sstr_line(line);
			sstr_line >> length;

			//new VertexArray at the end of the vector
			surface.push_back(sf::VertexArray(sf::TriangleFan, length));

			//read new line
			std::getline(file, line);
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
		surface[i-1][iteration].position = sf::Vector2f(firstpart, lastpart);
		surface[i-1][iteration].color = color;
		iteration++;
	}
	file.close();


	for (sf::Vector2i& i : figurePositions)
	{
		this->maxNumberOfUnits += 5;
	}



	if (this->hasCity == true)
	{
		this->placeFigure(0, sf::Color::White);
		this->maxNumberOfUnits -= 5;
	}


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Country	::draw is drawing the VertexArrays from surface[]												 //
//																											 //
//input		:: surface[]				: contains the VertexArrays, that build the surface of the country   //
//			:: sf::Renderwindow& window : reference to the window where the surface has to be drawn			 //
//																											 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Country::draw(sf::RenderWindow& window)
{
	//draw every VertexArray of the country
	for(sf::VertexArray& i : surface)
	{
		window.draw(i);
	}
	window.draw(countryname);

	if (this->numberOfFigures > this->maxNumberOfUnits || this->numberOfFigures == this->maxNumberOfUnits - 1 || this->numberOfFigures == this->maxNumberOfUnits - 3)
	{
		window.draw(amount);
	}
	
	


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Country::setColor will be started with a mode,																									  //
//if the mouse is on the country will get a darker color (-15)																						  //
//if mode = -1 the method checks, if the color is the original color. If not the method sets the color to the original color.						  //
//																																					  //
//input :: mode					: if 1 the mouse is on the country; if -1 the mouse is not on the country											  //
//		:: bool isOriginalColor	: checks if the color has to be resetted																			  //
//		:: int originalColor[3] : contains the 3 Integer for the RGB code (sf::Color not possible cause every int has to be reduced by 15 at mode = 1)//
//																																					  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Country::setColor(int mode)
{
	bool isOriginalColor = false;
	if (surface[0][0].color == sf::Color(originalColor[0], originalColor[1], originalColor[2]) && mode == -1)
	{
		isOriginalColor = true;
	}
	if(isOriginalColor == false)
	{
		for (sf::VertexArray& i : surface)
		{
			size_t size = i.getVertexCount();
			int length = static_cast<int>(size);

			for (int j = 0; j < length; j++)
			{
				//if -1 reset the color to originalColor (mouse is not on the country)
				if (mode == -1)
				{
					i[j].color = sf::Color(originalColor[0], originalColor[1], originalColor[2]);
				}
				//if 1 color gets darker by -15 (mouse is on the country)
				else if (mode == 1)
				{
						i[j].color = sf::Color(originalColor[0] - 15, originalColor[1] - 15, originalColor[2] - 15);	
				}
			}
		}		
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Country	::getRandomPositionForFigure chooses random a free postion for figures in the country			 //
//																											 //
//variable	:: figurePositionIsUsed		: contains the bool if the Position for figures is used				 //
//			:: figurePositions			: contains the positions (sf::Vector2i) for the figures				 //
//																											 //
//return	:: returns a Vector2i for a free position in the country										 //
//																											 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Vector2i Country::getRandomPositionForFigure()
{
	int counter = 0;
	int numberOfPosition = 0;
	size_t convertToInt = this->figurePositions.size();
	int length = static_cast<int>(convertToInt);
	for (int j = 0; j < length; j++)
	{
		if (this->figurePositionIsUsed[j] == false)
		{
			counter++;
		}
	}
	
	if (counter != 0)
	{
		numberOfPosition = rand() % counter + 1;
	}
	else
	{
		return sf::Vector2i(0, 0);
	}

	counter = 0;
	
	for (int j = 0; j < length; j++)
	{
		if (figurePositionIsUsed[j] == false)
		{
			counter++;

			if (counter == numberOfPosition)
			{
				figurePositionIsUsed[j] = true;
				return figurePositions[j];
			}
		}
	}

	return sf::Vector2i(0, 0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Country	::placeFigure is placing the figures in the vector												 //
//																											 //
//input		:: getRandomPositionForFigure()	 : returns random a empty place of the FigurePositions			 //
//			:: figureList					 : contains the Figures of the Country							 //
//																											 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Country::placeFigure(int value, sf::Color color)
{

	sf::Vector2i position = getRandomPositionForFigure();
	if (position != sf::Vector2i(0, 0))
	{
			figureList.push_back(new Figure(value, position, color));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Country	::drawFigure draws the Figures of the acting country in the window								 //
//																											 //
//input		:: sf::RenderWindow& window		 : reference to the window where the Figures will be drawn		 //
//			:: figureList					 : contains the Figures of the Country							 //
//																											 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Country::drawFigure(sf::RenderWindow& window)
{
	if (this->numberOfFigures <= this->maxNumberOfUnits && this->numberOfFigures != this->maxNumberOfUnits - 1 && this->numberOfFigures != this->maxNumberOfUnits - 3)
	{
		for (auto i : figureList)
		{
			i->draw(window);
		}
	}

	for (int i = 0; i < explosionList.size(); i++)
	{
		if (explosionList[i]->draw(window) == true)
		{
			explosionList.erase(explosionList.begin() + i);
			i--;
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::deleteFigure
///
/// Summary:	Deletes the figure described by value.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// value - 	The value of the figure which has to be deleted. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Country::deleteFigure(int value)
{
	bool isNotEmpty = false;
	int numberOfElement = 0;
	int deletedFigure = 0;
	int counter = 0;

	for (int i = 0; i < figurePositionIsUsed.size(); i++)
	{
		if (figurePositionIsUsed[i] == true)
		{
			isNotEmpty = true;
		}
	}
	if (isNotEmpty == true)
	{
		
		for (int i = 0; i < figureList.size(); i++)
		{
			if (figureList[i]->getValue() == value)
			{
				counter++;
			}
		}

		if (counter != 0)
		{
			int numberOfElement = rand() % counter + 1;
			counter = 0;

			for (int i = 0; i < figureList.size(); i++)
			{
				if (figureList[i]->getValue() == value)
				{
					counter++;

					if (numberOfElement == counter)
					{
						sf::Vector2i position = figureList[i]->getPosition();

						for (int j = 0; j < figurePositions.size(); j++)
						{
							if (figurePositions[j] == position)
							{
								delete figureList[i];
								figureList.erase(figureList.begin() + i);
								figurePositionIsUsed[j] = false;
							}
						}
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::getNumbOfValue
///
/// Summary:	counts the figures with the given value in the acting country.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// value - 	The value. 
///
/// Returns:	The number of the figures with the given value.
////////////////////////////////////////////////////////////////////////////////////////////////////

int Country::getNumbOfValue(int value)
{
	int counter = 0;

	for (auto& i : figureList)
	{
		if(i->getValue() == value)
		{
			counter++;
		}
	}

	return counter;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::getName
///
/// Summary:	Gets the name of the country.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	The name.
////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Country::getName()
{
	return this->name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::getCity
///
/// Summary:	Gets if the country has a city.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Returns:	True if the country has a city, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Country::getCity()
{
	return this->hasCity;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::isNeighbor
///
/// Summary:	Query if 'index' is a neighbor of the acting country.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// index - 	Zero-based index of the. 
///
/// Returns:	True if its a neighbor, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Country::isNeighbor(int index)
{
	for (auto i : neighbors)
	{
		if (i == index)
		{
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::refreshAmount
///
/// Summary:	Refresh the amount of the figures in the country.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
////////////////////////////////////////////////////////////////////////////////////////////////////

void Country::refreshAmount()
{
	amount.setString(std::to_string(numberOfFigures));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::giveCapital
///
/// Summary:	Gives a capital to the country.
///
/// Author:	Bennet
///
/// Date:	01.01.2020
///
/// Parameters:
/// color - 	The color of the owner of the capital. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void Country::giveCapital(sf::Color color)
{
	this->hasCapital = true;
	this->colorOfCapital = color;
	this->placeFigure(-1, color);
	this->maxNumberOfUnits -= 5;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::replaceCapital
///
/// Summary:	Replaces the capital.
///
/// Author:	Bennet
///
/// Date:	01.01.2020
////////////////////////////////////////////////////////////////////////////////////////////////////

void Country::replaceCapital()
{
	this->placeFigure(-1, colorOfCapital);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::getCapital
///
/// Summary:	Gets the capital.
///
/// Author:	Bennet
///
/// Date:	01.01.2020
///
/// Returns:	True if it has a capital, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Country::getCapital()
{
	return this->hasCapital;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Country::getColorOfCapital
///
/// Summary:	Gets color of capital.
///
/// Author:	Bennet
///
/// Date:	02.01.2020
///
/// Returns:	The color of capital.
////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Color Country::getColorOfCapital()
{
	return this->colorOfCapital;
}


void Country::explode()
{
	int counter = 0;
	int numberOfPosition = 0;
	size_t convertToInt = this->figurePositions.size();
	int length = static_cast<int>(convertToInt);
	for (int j = 0; j < length; j++)
	{
		if (this->figurePositionIsUsed[j] == true)
		{
			counter++;
		}
	}

	if (counter != 0)
	{
		numberOfPosition = rand() % counter + 1;
	}
	else
	{
		return;
	}

	counter = 0;

	for (int j = 0; j < length; j++)
	{
		if (figurePositionIsUsed[j] == true)
		{
			counter++;

			if (counter == numberOfPosition)
			{
				figurePositionIsUsed[j] = true;
				this->explosionList.push_back(new Explosion(sf::Vector2f(figurePositions[j].x, figurePositions[j].y)));
				return;
			}
		}
	}

	return;
}