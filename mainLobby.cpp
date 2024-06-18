#include "mainLobby.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MainLobby::MainLobby
///
/// Summary:
/// 	Default constructor of the MainLobby. Creates the PlayerBoxes, the UsernameBoxes, the
/// 	Startbutton and the WorldBox.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////
MainLobby::MainLobby()
{
	for (int i = 0; i < 6; i++)
	{
		socketIndex[i] = -1;
	}

	newConnection.loadFromFile("Sound/Connected.wav");
	lobbySound.setBuffer(newConnection);

}


void MainLobby::startLobby(int gameMode)
{
	if (gameMode == 1)
	{
		multiplayer = true;
	}


	listener.setBlocking(false);
	listener.listen(54000);


	nameOfMapBox.setSize(sf::Vector2f(300, 40));
	nameOfMapBox.setPosition(sf::Vector2f(100, 100 - nameOfMapBox.getGlobalBounds().height / 2));
	nameOfMapBox.setFillColor(sf::Color(150, 150, 150));

	font.loadFromFile("Lato-Regular.ttf");
	nameOfMap.setFont(font);
	nameOfMap.setCharacterSize(35);
	nameOfMap.setString("World");
	nameOfMap.setFillColor(sf::Color::Black);
	nameOfMap.setPosition(sf::Vector2f(nameOfMapBox.getPosition().x + 3, nameOfMapBox.getPosition().y));



	ipAdressBox.setSize(sf::Vector2f(300, 40));
	ipAdressBox.setPosition(1820 - ipAdressBox.getGlobalBounds().width, nameOfMapBox.getPosition().y);
	ipAdressBox.setFillColor(sf::Color::White);

	sf::IpAddress ip = sf::IpAddress::getLocalAddress();

	ipString.setFont(font);
	ipString.setCharacterSize(35);
	ipString.setString(ip.toString());
	ipString.setFillColor(sf::Color::Black);
	ipString.setPosition(sf::Vector2f(ipAdressBox.getPosition().x + 3, ipAdressBox.getPosition().y));






	texture.loadFromFile("pictures/Lobby.jpg");
	shape.setTexture(texture);
	
	textureOfIncrease.loadFromFile("pictures/increase.png");
	textureOfDecrease.loadFromFile("pictures/decrease.png");
	textureOfStartButton.loadFromFile("pictures/startButton.png");





	amountOfPlayer.setFont(font);
	startText.setFont(font);

	startText.setString("start");
	startText.setCharacterSize(30);
	startText.setPosition(sf::Vector2f((float) (shape.getGlobalBounds().width * 0.99 - startText.getGlobalBounds().width), (float) (shape.getGlobalBounds().height * 0.97 - startText.getGlobalBounds().height)));
	amountOfPlayer.setCharacterSize(80);


	amountOfPlayerValue = 3;
	amountOfPlayer.setString("3");


	amountOfPlayer.setFillColor(sf::Color::White);


	amountOfPlayer.setPosition(sf::Vector2f(shape.getGlobalBounds().width / 2 - amountOfPlayer.getGlobalBounds().width / 2, 100 - amountOfPlayer.getGlobalBounds().height / 2));

	increase.setTexture(textureOfIncrease);
	decrease.setTexture(textureOfDecrease);
	startButton.setTexture(textureOfStartButton);

	increase.setPosition(sf::Vector2f(amountOfPlayer.getPosition().x + amountOfPlayer.getGlobalBounds().width + increase.getGlobalBounds().width * 2, amountOfPlayer.getPosition().y + amountOfPlayer.getGlobalBounds().height / 2 + increase.getGlobalBounds().height / 2));
	decrease.setPosition(sf::Vector2f(amountOfPlayer.getPosition().x - decrease.getGlobalBounds().width * 3, amountOfPlayer.getPosition().y + amountOfPlayer.getGlobalBounds().height / 2 + decrease.getGlobalBounds().height / 2));
	startButton.setPosition(sf::Vector2f(startText.getPosition().x - startText.getGlobalBounds().width, startText.getPosition().y));

	for (int i = 0; i < 6; i++)
	{
		playerBoxes[i].setSize(sf::Vector2f(200, 200));
		playerBoxes[i].setFillColor(sf::Color::White);
		playerBoxes[i].setPosition(sf::Vector2f((float) (235 + i * 250), (float)500));

		usernameBoxes[i].setSize(sf::Vector2f(200, 25));
		usernameBoxes[i].setFillColor(sf::Color(150, 150, 150));
		usernameBoxes[i].setPosition(sf::Vector2f(playerBoxes[i].getPosition().x, playerBoxes[i].getPosition().y + playerBoxes[i].getGlobalBounds().height + 25));

		username[i].setFont(font);
		username[i].setCharacterSize(20);
		username[i].setString("");
		username[i].setFillColor(sf::Color::Black);
		username[i].setPosition(sf::Vector2f(usernameBoxes[i].getPosition().x + 2, usernameBoxes[i].getPosition().y + 2));



		if (multiplayer == true)
		{
			connectionBoxes[i].setSize(sf::Vector2f(200, 25));
			connectionBoxes[i].setFillColor(sf::Color(150, 150, 150));
			connectionBoxes[i].setPosition(sf::Vector2f(usernameBoxes[i].getPosition().x, usernameBoxes[i].getPosition().y + usernameBoxes[i].getGlobalBounds().height + 25));

			connection[i].setFont(font);
			connection[i].setCharacterSize(20);
			connection[i].setString("Client - closed");
			connection[i].setFillColor(sf::Color::Black);
			connection[i].setPosition(sf::Vector2f(connectionBoxes[i].getPosition().x + 2, connectionBoxes[i].getPosition().y + 2));
		}

	}

	connection[0].setString("Host");





}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MainLobby::getInteraction
///
/// Summary:	Gets the interaction of the MainLobby.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Returns:	The interaction.
////////////////////////////////////////////////////////////////////////////////////////////////////

int MainLobby::getInteraction()
{
	sf::Vector2f position = sf::Vector2f((float) sf::Mouse::getPosition().x, (float) sf::Mouse::getPosition().y);

	if (increase.getGlobalBounds().contains(position))
	{
		increase.setColor(sf::Color::White);
		return 1;
	}
	else if (decrease.getGlobalBounds().contains(position))
	{
		decrease.setColor(sf::Color::White);
		return 2;
	}
	else if (startButton.getGlobalBounds().contains(position) || startText.getGlobalBounds().contains(position))
	{
		startButton.setColor(sf::Color::Red);
		startText.setFillColor(sf::Color::Red);
		return 3;
	}
	/*else if (nameOfMapBox.getGlobalBounds().contains(position))
	{
		return 4;
	}*/
	else
	{
		for (int i = 0; i < amountOfPlayerValue; i++)
		{
			if (usernameBoxes[i].getGlobalBounds().contains(position))
			{
				return i + 5;
			}
		}
		for (int i = 0; i < amountOfPlayerValue; i++)
		{
			if (playerBoxes[i].getGlobalBounds().contains(position))
			{
				return i + 5 + (int)std::size(usernameBoxes);
			}
		}
		if (multiplayer == true)
		{
			for (int i = 0; i < amountOfPlayerValue; i++)
			{
				if (connectionBoxes[i].getGlobalBounds().contains(position))
				{
					connectionBoxes[i].setFillColor(sf::Color::White);
					return i + 5 + (int)std::size(usernameBoxes) + (int)std::size(playerBoxes);
				}
			}
		}
	}


	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MainLobby::resetInteraction
///
/// Summary:	Resets the interaction. So the Object get their default color.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
////////////////////////////////////////////////////////////////////////////////////////////////////

void MainLobby::resetInteraction()
{
	increase.setColor(sf::Color::Green);
	decrease.setColor(sf::Color::Red);
	startButton.setColor(sf::Color::White);
	startText.setFillColor(sf::Color::White);

	if (multiplayer == true)
	{
		for (int i = 0; i < amountOfPlayerValue; i++)
		{
			connectionBoxes[i].setFillColor(sf::Color(155, 155, 155));
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MainLobby::run
///
/// Summary:	Runs the MainLobby and acting with the return value depending on the current Mode.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window -   	[in,out] The window. 
/// event -    	[in,out] the event qeue of the current Frame. 
/// game - 	   	[in,out] the game which will be started. 
/// isMainLobby -  	[in,out] the Status of the MainLobby to leave the MainLobby. 
/// inGame -   	[in,out] the Status of the Game to start the Game. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MainLobby::run(sf::RenderWindow& window, sf::Event* event, Game** game, bool& isMainLobby, bool& inGame)
{

	if (multiplayer == true)
	{
		sf::TcpSocket* client = new sf::TcpSocket;

		if (listener.accept(*client) == sf::Socket::Done)
		{
			sockets.push_back(client);
			selector.add(*client);

			sockets[(int)sockets.size() - 1]->setBlocking(false);
			
			sf::Packet packet;
			packet << amountOfPlayerValue;
			sockets[(int)sockets.size() - 1]->send(packet);
			packet.clear();
			for (int i = 0; i < amountOfPlayerValue; i++)
			{
				std::string u = username[i].getString();
				std::string c = connection[i].getString();
				int r = (int)playerBoxes[i].getFillColor().r;
				int g = (int)playerBoxes[i].getFillColor().g;
				int b = (int)playerBoxes[i].getFillColor().b;

				packet << i << u << c << r << g << b;

				sf::Socket::Status status = sockets[(int)sockets.size() - 1]->send(packet);


				while (status == sf::Socket::Partial)
				{
					sf::Socket::Status status = sockets[(int)sockets.size() - 1]->send(packet);
				}
				packet.clear();

			}

			lobbySound.play();

		}
		else
		{
			delete client;
		}

		sf::Packet received;
		for (int i = 0; i < (int)sockets.size(); i++)
		{
			if (sockets[i]->receive(received) != sf::Socket::NotReady)
			{
				std::string action;
				received >> action;

				if (action == "takeSpot")
				{
					this->clientTakesSpot(received, i);
				}
				else if (action == "changeColor")
				{
					this->clientChangeColor(received, i);
				}
				else if (action == "changeUsername")
				{
					this->clientChangeUsername(received, i);
				}
			}
		}


	}





	int seed = rand();
	this->resetInteraction();
	int interaction = this->getInteraction();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}





	while (window.pollEvent(*event))
	{
		if (event->type == sf::Event::Closed)
		{
			window.close();
		}



		else if (event->type == sf::Event::TextEntered)
		{
			if (typeInField != -1)
			{
				if (connection[typeInField].getString().substring(0, 1) != "C")
				{
					if (event->text.unicode != 13)
					{
						if (event->text.unicode != 8)
						{
							username[typeInField].setString(username[typeInField].getString() + event->text.unicode);

						}
						else
						{
							std::string reducedUsername = username[typeInField].getString();
							username[typeInField].setString(reducedUsername.substr(0, (int)reducedUsername.size() - 1));
						}

						if (multiplayer == true)
						{
							sf::Packet changeUsername;
							std::string action = "changeUsername";
							int field = typeInField;
							std::string newUsername = username[typeInField].getString();
							changeUsername << action << typeInField << newUsername;
							this->sendToAll(changeUsername);

						}
					}
				}
			}
		}



		else if (event->type == sf::Event::KeyPressed && multiplayer == true)
		{
			if (event->key.code == sf::Keyboard::Enter)
			{
				if (interaction < 5 + (int)std::size(usernameBoxes) + (int)std::size(playerBoxes) + (int)std::size(connectionBoxes) &&
					interaction >= 5 + (int)std::size(usernameBoxes) + (int)std::size(playerBoxes))
				{
					bool hostExist = false;
					for (int i = 0; i < amountOfPlayerValue; i++)
					{
						if (connection[i].getString() == "Host")
						{
							hostExist = true;
						}
					}
					if (connection[interaction - (int)std::size(usernameBoxes) - (int)std::size(playerBoxes) - 5].getString() == "Client - closed" && hostExist == true)
					{
						connection[interaction - (int)std::size(usernameBoxes) - (int)std::size(playerBoxes) - 5].setString("Client - open");
					}
					else if (connection[interaction - (int)std::size(usernameBoxes) - (int)std::size(playerBoxes) - 5].getString() == "Client - open")
					{
						connection[interaction - (int)std::size(usernameBoxes) - (int)std::size(playerBoxes) - 5].setString("Client - closed");
					}
				}

				sf::Packet changeConnection;
				std::string action = "changeConnection";
				int field = interaction - (int)std::size(usernameBoxes) - (int)std::size(playerBoxes) - 5;
				std::string newConnection = connection[field].getString();

				changeConnection << action << field << newConnection;

				this->sendToAll(changeConnection);

				changeConnection.clear();


			}
		}



	}




	if (isWarning)
	{
		button = false;
		if (warning.run(window) == 1)
		{
			isWarning = false;
		}
	}



	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !button)
	{
		button = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && button && typeInField == -1)
	{
		button = false;
		if (interaction != -1)
		{
			if (interaction == 1)
			{
				if (amountOfPlayerValue < 6)
				{
					amountOfPlayerValue++;
					amountOfPlayer.setString(std::to_string(amountOfPlayerValue));

					username[amountOfPlayerValue - 1].setString("");
					playerBoxes[amountOfPlayerValue - 1].setFillColor(sf::Color::White);



					if (multiplayer == true)
					{
						connection[amountOfPlayerValue - 1].setString("Client - closed");

						sf::Packet increase;
						std::string action = "increase";
						int newAmount = amountOfPlayerValue;
						increase << action << newAmount;
						this->sendToAll(increase);
					}
				}
			}
			else if (interaction == 2)
			{
				if (amountOfPlayerValue > 2)
				{
					if (connection[amountOfPlayerValue - 1].getString() == "Host")
					{
						connection[amountOfPlayerValue - 1].setString("Client - closed");
					}
					amountOfPlayerValue--;
					amountOfPlayer.setString(std::to_string(amountOfPlayerValue));

					username[amountOfPlayerValue].setString("");
					playerBoxes[amountOfPlayerValue].setFillColor(sf::Color::White);



					if (multiplayer == true)
					{
						connection[amountOfPlayerValue].setString("Client - closed");

						sf::Packet decrease;
						std::string action = "decrease";
						int newAmount = amountOfPlayerValue;
						decrease << action << newAmount;
						this->sendToAll(decrease);
					}
				}
			}
			else if (interaction == 3)
			{
				
				this->start(game, isMainLobby, inGame, window);
				
			}
			/*else if (interaction == 4)
			{
				typeInField = 0;
				nameOfMapBox.setFillColor(sf::Color::White);
			}*/
			else if (interaction < 5 + (int)std::size(usernameBoxes))
			{
				typeInField = interaction - 5;
				usernameBoxes[interaction - 5].setFillColor(sf::Color::White);
			}
			else if (interaction < 5 + (int)std::size(usernameBoxes) + (int)std::size(playerBoxes))
			{
				if (connection[interaction - (int)std::size(usernameBoxes) - 5].getString().substring(0, 1) != "C")
				{
					this->changeColor(interaction - (int)std::size(usernameBoxes) - 5);
				}
			}
			else if (interaction < 5 + (int)std::size(usernameBoxes) + (int)std::size(playerBoxes) + (int)std::size(connectionBoxes))
			{
				this->changeConnection(interaction - (int)std::size(usernameBoxes) - (int)std::size(playerBoxes) - 5);
			}
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && button && typeInField != -1)
	{
		button = false;
		if (interaction != typeInField + 5)
		{
			usernameBoxes[typeInField].setFillColor(sf::Color(150, 150, 150));
			typeInField = -1;
			if (interaction >= 5 && interaction < 5 + (int)std::size(usernameBoxes))
			{
				typeInField = interaction - 5;
				usernameBoxes[interaction - 5].setFillColor(sf::Color::White);
			}
		}
	}

	this->draw(window);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MainLobby::changeColor
///
/// Summary:	Changes the color of the interacting PlayerBox.
///
/// Author:	Bennet.
///
/// Date:	31.12.2019.
///
/// Parameters:
/// interaction - 	The number of the PlayerBox. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MainLobby::changeColor(int interaction)
{
	sf::Color color = playerBoxes[interaction].getFillColor();
	if (color == sf::Color::White)
	{
		playerBoxes[interaction].setFillColor(sf::Color::Green);
	}
	else if (color == sf::Color::Green)
	{
		playerBoxes[interaction].setFillColor(sf::Color::Red);
	}
	else if (color == sf::Color::Red)
	{
		playerBoxes[interaction].setFillColor(sf::Color::Blue);
	}
	else if (color == sf::Color::Blue)
	{
		playerBoxes[interaction].setFillColor(sf::Color::Yellow);
	}
	else if (color == sf::Color::Yellow)
	{
		playerBoxes[interaction].setFillColor(sf::Color::Magenta);
	}
	else if (color == sf::Color::Magenta)
	{
		playerBoxes[interaction].setFillColor(sf::Color::Cyan);
	}
	else if (color == sf::Color::Cyan)
	{
		playerBoxes[interaction].setFillColor(sf::Color::White);
	}

	if (multiplayer == true)
	{
		sf::Packet changeColor;
		std::string action = "changeColor";
		int field = interaction;
		int r = playerBoxes[interaction].getFillColor().r;
		int g = playerBoxes[interaction].getFillColor().g;
		int b = playerBoxes[interaction].getFillColor().b;

		changeColor << action << field << r << g << b;

		this->sendToAll(changeColor);

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MainLobby::changeConnection
///
/// Summary:	Change the connectionType of the connection[interaction].
///
/// Author:	Bennet
///
/// Date:	02.01.2020
///
/// Parameters:
/// interaction - 	The interaction. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MainLobby::changeConnection(int interaction)
{
	if (connection[interaction].getString() == "local")
	{
		username[interaction].setString("");
		playerBoxes[interaction].setFillColor(sf::Color::White);

		sf::Packet reset;
		std::string action = "reset";
		int field = interaction;
		reset << action << field;
		this->sendToAll(reset);


		connection[interaction].setString("Client - closed");
	}
	else if (connection[interaction].getString() == "Client - closed")
	{
		bool hostExist = false;
		for (int i = 0; i < amountOfPlayerValue; i++)
		{
			if (connection[i].getString() == "Host")
			{
				hostExist = true;
			}
		}

		if (hostExist == true)
		{
			connection[interaction].setString("local");
		}
		else
		{
			connection[interaction].setString("Host");
		}

	}
	else if (connection[interaction].getString() == "Host")
	{
		connection[interaction].setString("local");
	}


	sf::Packet changeConnection;
	std::string action = "changeConnection";
	int field = interaction;
	std::string newConnection = connection[interaction].getString();

	changeConnection << action << field << newConnection;

	this->sendToAll(changeConnection);



}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MainLobby::start
///
/// Summary:	Starts the game with the given values of the PlayerBoxes and Usernames.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// game - 	   	[in,out] the game which will be started. 
/// isMainLobby -  	[in,out] The Status of the MainLobby to leave the MainLobby. 
/// inGame -   	[in,out] The Status of the Game to enter into the Game. 
/// window -   	[in,out] The window where the Warning could be drawn. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MainLobby::start(Game** game, bool& isMainLobby, bool& inGame, sf::RenderWindow& window)
{
	std::vector<std::string> usernameStr;
	std::vector<sf::Color> playerColor;

	bool differentUsernames = true;
	bool differentColors = true;

	for (int i = 0; i < amountOfPlayerValue; i++)
	{
		usernameStr.push_back(this->username[i].getString());
		playerColor.push_back(this->playerBoxes[i].getFillColor());
	}
	for (int i = 0; i < amountOfPlayerValue; i++)
	{
		for (int j = 0; j < amountOfPlayerValue; j++)
		{
			if (i != j)
			{
				if (usernameStr[i] == usernameStr[j])
				{
					differentUsernames = false;
				}
				if (playerColor[i] == playerColor[j])
				{
					differentColors = false;
				}
			}
		}
	}

	if (differentUsernames && differentColors)
	{
		if (!multiplayer)
		{

			*game = new LocalGame();
			(*game)->startGame(amountOfPlayerValue, &usernameStr, &playerColor);
			isMainLobby = false;
			inGame = true;
		}
		else if (multiplayer)
		{
			std::vector<sf::TcpSocket*> clients;

			for (int i = 0; i < 6; i++)
			{
				if (socketIndex[i] != -1)
				{
					clients.push_back(sockets[socketIndex[i]]);
				}
				else
				{
					clients.push_back(NULL);
				}

			}
			

			

			sf::Packet changeConnection;
			std::string action = "start";
			
			changeConnection << action;

			this->sendToAll(changeConnection);

			int activePlayer = 0;
			for (int i = 0; i < amountOfPlayerValue; i++)
			{
				if (connection[i].getString() == "Host")
				{
					activePlayer = i;
					break;
				}
			}


			*game = new HostGame();
			(*game)->startGame(amountOfPlayerValue, &usernameStr, &playerColor, clients, activePlayer);
			isMainLobby = false;
			inGame = true;


		}
	}
	else if (!differentUsernames || !differentColors)
	{
		isWarning = true;
		warning.placeWarning("Players cant have", "the same username", "or color!", window);
	}



}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	MainLobby::draw
///
/// Summary:	Draws the MainLobby into the given window.
///
/// Author:	Bennet
///
/// Date:	31.12.2019
///
/// Parameters:
/// window - 	[in,out] The window. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void MainLobby::draw(sf::RenderWindow& window)
{
	window.draw(shape); // Textur hinzufügen
	window.draw(nameOfMapBox);
	window.draw(nameOfMap); // eingabe hinzufügen
	//window.draw(amountOfPlayersBox); //evtl hinzufügen
	window.draw(amountOfPlayer);
	window.draw(increase);
	window.draw(decrease);
	window.draw(startButton);
	window.draw(startText);
	for (int i = 0; i < amountOfPlayerValue; i++)
	{
		window.draw(playerBoxes[i]);
		window.draw(usernameBoxes[i]);
		window.draw(username[i]);

		if (multiplayer == true)
		{
			window.draw(connectionBoxes[i]);
			window.draw(connection[i]);
		}
	}
	if (multiplayer == true)
	{
		window.draw(ipAdressBox);
		window.draw(ipString);
	}


	if (isWarning)
	{
		warning.draw(window);
	}
}


void MainLobby::sendToAll(sf::Packet& packet)
{
	for (auto i : sockets)
	{
		sf::Socket::Status status = i->send(packet);
		while (status == sf::Socket::Partial)
		{
			status = i->send(packet);
		}
	}
	packet.clear();
}

void MainLobby::sendToAll(sf::Packet& packet, int exclusion)
{
	for (int i = 0; i < (int)sockets.size(); i++)
	{
		if (i != exclusion)
		{
			sf::Socket::Status status = sockets[i]->send(packet);
			while (status == sf::Socket::Partial)
			{
				status = sockets[i]->send(packet);
			}
		}
	}
}


void MainLobby::clientTakesSpot(sf::Packet& packet, int socketNumber)
{
	int spot;
	packet >> spot;

	if (connection[spot].getString() == "Client - open")
	{
		connection[spot].setString("Client - taken");

		sf::Packet changeConnection;
		std::string action = "changeConnection";
		std::string newConnection = connection[spot].getString();

		changeConnection << action << spot << newConnection;

		this->sendToAll(changeConnection);
		changeConnection.clear();


		action = "getSpot";

		sf::Packet getSpot;
		getSpot << action << spot;
		sf::Socket::Status status = sockets[socketNumber]->send(getSpot);
		while (status == sf::Socket::Partial)
		{
			status = sockets[socketNumber]->send(getSpot);
		}

		socketIndex[spot] = socketNumber;
	}

}

void MainLobby::clientChangeColor(sf::Packet& packet, int socketNumber)
{
	int r, g, b;
	packet >> r >> g >> b;
	for (int i = 0; i < 6; i++)
	{
		if (socketIndex[i] == socketNumber)
		{
			playerBoxes[i].setFillColor(sf::Color(r, g, b));

			sf::Packet changeColor;
			std::string action = "changeColor";
			int field = i;
			r = playerBoxes[i].getFillColor().r;
			g = playerBoxes[i].getFillColor().g;
			b = playerBoxes[i].getFillColor().b;

			changeColor << action << field << r << g << b;

			this->sendToAll(changeColor, socketNumber);
		}
	}
}



void MainLobby::clientChangeUsername(sf::Packet& packet, int socketNumber)
{
	std::string newUsername;
	packet >> newUsername;

	for (int i = 0; i < 6; i++)
	{
		if (socketIndex[i] == socketNumber)
		{
			username[i].setString(newUsername);


			sf::Packet changeColor;
			std::string action = "changeUsername";
			int field = i;


			changeColor << action << i << newUsername;

			this->sendToAll(changeColor, socketNumber);
		}
	}
}
