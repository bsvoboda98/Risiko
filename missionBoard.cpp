#include "missionBoard.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MissionBoard::MissionBoard
///
/// Summary:	Constructor. Sets the Missionboard and creates the Missions (chosen random from all missions).
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// position - 	The position where the Missionboard will be placed on the map. 
////////////////////////////////////////////////////////////////////////////////////////////////////
MissionBoard::MissionBoard()
{

}


void MissionBoard::start(sf::Vector2f position)
{

	texture.loadFromFile("pictures/MissionboardShape.png");
	font.loadFromFile("Lato-Regular.ttf");

	basicMission.setFont(font);
	basicMission.setCharacterSize(10);
	basicMission.setString("basic missions");


	specialMission.setFont(font);
	specialMission.setCharacterSize(10);
	specialMission.setString("special missions");




	shape.setTexture(texture);
	shape.setPosition(position);

	for (int i = 0; i < 2; i++)
	{

		missionHeader.push_back(sf::VertexArray(sf::Triangles, 3));
		missionHeader[0 + 3 * i][0].position = sf::Vector2f(position.x + 8 + i * 127, position.y + 11);
		missionHeader[0 + 3 * i][1].position = sf::Vector2f(missionHeader[0 + 3 * i][0].position.x + 106, missionHeader[0 + 3 * i][0].position.y);
		missionHeader[0 + 3 * i][2].position = sf::Vector2f(missionHeader[0 + 3 * i][0].position.x + 53, missionHeader[0 + 3 * i][0].position.y + 30);

		missionHeader.push_back(sf::VertexArray(sf::Triangles, 3));
		missionHeader[1 + 3 * i][0].position = missionHeader[0 + 3 * i][2].position;
		missionHeader[1 + 3 * i][1].position = sf::Vector2f(missionHeader[1 + 3 * i][0].position.x, missionHeader[1 + 3 * i][0].position.y + 10);
		missionHeader[1 + 3 * i][2].position = missionHeader[0 + 3 * i][1].position;

		missionHeader.push_back(sf::VertexArray(sf::Triangles, 3));
		missionHeader[2 + 3 * i][0].position = missionHeader[1 + 3 * i][0].position;
		missionHeader[2 + 3 * i][1].position = missionHeader[1 + 3 * i][1].position;
		missionHeader[2 + 3 * i][2].position = missionHeader[0 + 3 * i][0].position;

		for (int j = 0; j < 3; j++)
		{
			missionHeader[0 + 3 * i][j].color = sf::Color(55, 26, 22);
			missionHeader[1 + 3 * i][j].color = sf::Color::Black;
			missionHeader[2 + 3 * i][j].color = sf::Color::Black;

		}
	}

	std::vector<int> mixedMissions1;
	std::vector<int> mixedMissions2;

	for (int i = 0; i < 6; i++)
	{
		mixedMissions1.push_back(i);
		mixedMissions2.push_back(i + 6);
	}

	for (int i = 0; i < 6; i++)
	{
		int k1 = rand() % 6;
		int k2 = rand() % 6;

		int temp1 = mixedMissions1[i];
		mixedMissions1[i] = mixedMissions1[k1];
		mixedMissions1[k1] = temp1;

		int temp2 = mixedMissions2[i];
		mixedMissions2[i] = mixedMissions2[k2];
		mixedMissions2[k2] = temp2;
	}


	for (int i = 0; i < 8; i++)
	{
		missionBox.push_back(sf::VertexArray(sf::TriangleStrip, 6));

		if (i < 4)
		{
			missionBox[i][0].position = sf::Vector2f(missionHeader[0][0].position.x + 5, missionHeader[0][2].position.y + 5 + i * 75);
		}
		else
		{
			missionBox[i][0].position = sf::Vector2f(missionHeader[3][0].position.x + 5, missionHeader[3][2].position.y + 5 + (i - 4) * 75);
		}
		missionBox[i][1].position = sf::Vector2f(missionBox[i][0].position.x, missionBox[i][0].position.y + 60);
		missionBox[i][2].position = sf::Vector2f(missionBox[i][0].position.x + 48, missionBox[i][0].position.y + 10);
		missionBox[i][3].position = sf::Vector2f(missionBox[i][2].position.x, missionBox[i][1].position.y + 20);
		missionBox[i][4].position = sf::Vector2f(missionBox[i][0].position.x + 96, missionBox[i][0].position.y);
		missionBox[i][5].position = sf::Vector2f(missionBox[i][4].position.x, missionBox[i][1].position.y);

		for (int j = 0; j < 6; j++)
		{
			missionBox[i][j].color = sf::Color::Black;
		}

		if (i < 4)
		{
			missions.push_back(new Mission(mixedMissions1[i], missionBox[i][0].position));
		}
		else
		{
			missions.push_back(new Mission(mixedMissions2[i - 4], missionBox[i][0].position));
		}

	}

	basicMission.setPosition(sf::Vector2f(missionHeader[0][0].position.x + 53 - basicMission.getGlobalBounds().width / 2, missionHeader[0][0].position.y));
	specialMission.setPosition(sf::Vector2f(missionHeader[3][0].position.x + 53 - specialMission.getGlobalBounds().width / 2, missionHeader[3][0].position.y));
}



void MissionBoard::startWithMissions(sf::Vector2f position, int missionsIndex[8])
{

	texture.loadFromFile("pictures/MissionboardShape.png");
	font.loadFromFile("Lato-Regular.ttf");

	basicMission.setFont(font);
	basicMission.setCharacterSize(10);
	basicMission.setString("basic missions");


	specialMission.setFont(font);
	specialMission.setCharacterSize(10);
	specialMission.setString("special missions");




	shape.setTexture(texture);
	shape.setPosition(position);

	for (int i = 0; i < 2; i++)
	{

		missionHeader.push_back(sf::VertexArray(sf::Triangles, 3));
		missionHeader[0 + 3 * i][0].position = sf::Vector2f(position.x + 8 + i * 127, position.y + 11);
		missionHeader[0 + 3 * i][1].position = sf::Vector2f(missionHeader[0 + 3 * i][0].position.x + 106, missionHeader[0 + 3 * i][0].position.y);
		missionHeader[0 + 3 * i][2].position = sf::Vector2f(missionHeader[0 + 3 * i][0].position.x + 53, missionHeader[0 + 3 * i][0].position.y + 30);

		missionHeader.push_back(sf::VertexArray(sf::Triangles, 3));
		missionHeader[1 + 3 * i][0].position = missionHeader[0 + 3 * i][2].position;
		missionHeader[1 + 3 * i][1].position = sf::Vector2f(missionHeader[1 + 3 * i][0].position.x, missionHeader[1 + 3 * i][0].position.y + 10);
		missionHeader[1 + 3 * i][2].position = missionHeader[0 + 3 * i][1].position;

		missionHeader.push_back(sf::VertexArray(sf::Triangles, 3));
		missionHeader[2 + 3 * i][0].position = missionHeader[1 + 3 * i][0].position;
		missionHeader[2 + 3 * i][1].position = missionHeader[1 + 3 * i][1].position;
		missionHeader[2 + 3 * i][2].position = missionHeader[0 + 3 * i][0].position;

		for (int j = 0; j < 3; j++)
		{
			missionHeader[0 + 3 * i][j].color = sf::Color(55, 26, 22);
			missionHeader[1 + 3 * i][j].color = sf::Color::Black;
			missionHeader[2 + 3 * i][j].color = sf::Color::Black;

		}
	}


	for (int i = 0; i < 8; i++)
	{
		missionBox.push_back(sf::VertexArray(sf::TriangleStrip, 6));

		if (i < 4)
		{
			missionBox[i][0].position = sf::Vector2f(missionHeader[0][0].position.x + 5, missionHeader[0][2].position.y + 5 + i * 75);
		}
		else
		{
			missionBox[i][0].position = sf::Vector2f(missionHeader[3][0].position.x + 5, missionHeader[3][2].position.y + 5 + (i - 4) * 75);
		}
		missionBox[i][1].position = sf::Vector2f(missionBox[i][0].position.x, missionBox[i][0].position.y + 60);
		missionBox[i][2].position = sf::Vector2f(missionBox[i][0].position.x + 48, missionBox[i][0].position.y + 10);
		missionBox[i][3].position = sf::Vector2f(missionBox[i][2].position.x, missionBox[i][1].position.y + 20);
		missionBox[i][4].position = sf::Vector2f(missionBox[i][0].position.x + 96, missionBox[i][0].position.y);
		missionBox[i][5].position = sf::Vector2f(missionBox[i][4].position.x, missionBox[i][1].position.y);

		for (int j = 0; j < 6; j++)
		{
			missionBox[i][j].color = sf::Color::Black;
		}

		if (i < 4)
		{
			missions.push_back(new Mission(missionsIndex[i], missionBox[i][0].position));
		}
		else
		{
			missions.push_back(new Mission(missionsIndex[i], missionBox[i][0].position));
		}

	}

	basicMission.setPosition(sf::Vector2f(missionHeader[0][0].position.x + 53 - basicMission.getGlobalBounds().width / 2, missionHeader[0][0].position.y));
	specialMission.setPosition(sf::Vector2f(missionHeader[3][0].position.x + 53 - specialMission.getGlobalBounds().width / 2, missionHeader[3][0].position.y));
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MissionBoard::hasWon
///
/// Summary:	Query if 'player' has won.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// player - 	[in,out] If non-null, the player. 
///
/// Returns:	True if won, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool MissionBoard::hasWon(Player* player)
{
	if (player->hasOwnCapital())
	{
		int counter = 0;
		for (auto i : missions)
		{
			if (i->hasAccomplished(player))
			{
				counter++;
			}
		}

		if (counter >= 3)
		{
			return true;
		}
	}
	return false;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MissionBoard::draw
///
/// Summary:	Draws the Missionboard into the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MissionBoard::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	for (int i = 0; i < 6; i++)
	{
		window.draw(missionHeader[i]);
	}

	for (auto& i : missionBox)
	{
		window.draw(i);
	}

	window.draw(basicMission);
	window.draw(specialMission);

	for (auto& i : missions)
	{
		i->draw(window);
	}
}




int MissionBoard::getIndexOfMission(int number)
{
	return missions[number]->getIndex();
}