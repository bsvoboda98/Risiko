#include "clientLobby.h"

ClientLobby::ClientLobby(){}

bool ClientLobby::startLobby(std::string ipAddress)
{
	sf::Packet packet;
	std::string s;

	sf::Socket::Status status = this->host->connect(sf::IpAddress(ipAddress), 54000, sf::seconds(5));
	if (status != sf::Socket::Done)
	{
		host->disconnect();
		return false;
	}
	else
	{
		host->receive(packet);
		int i;
		packet >> i;
		amountOfPlayerValue = i;
		packet.clear();
	}
	
	bool isRefreshed = false;
	while (isRefreshed == false)
	{
		host->receive(packet);
		int i;
		std::string u;
		std::string c;
		int r, g, b;


		packet >> i >> u >> c >> r >> g >> b;
		packet.clear();

		username[i].setString(u);
		connection[i].setString(c);
		playerBoxes[i].setFillColor(sf::Color(r, g, b));

		//daten verarbeiten
		
		isRefreshed = true;
		for (int i = 0; i < amountOfPlayerValue; i++)
		{
			if (connection[i].getString() == "")
			{
				isRefreshed = false;
			}
		}
	}
	host->setBlocking(false);


	nameOfMapBox.setSize(sf::Vector2f(300, 40));
	nameOfMapBox.setPosition(sf::Vector2f(100, 100 - nameOfMapBox.getGlobalBounds().height / 2));
	nameOfMapBox.setFillColor(sf::Color(150, 150, 150));

	texture.loadFromFile("pictures/Lobby.jpg");
	shape.setTexture(texture);

	textureOfIncrease.loadFromFile("pictures/increase.png");
	textureOfDecrease.loadFromFile("pictures/decrease.png");
	textureOfStartButton.loadFromFile("pictures/startButton.png");


	font.loadFromFile("Lato-Regular.ttf");
	nameOfMap.setFont(font);
	nameOfMap.setCharacterSize(35);
	nameOfMap.setString("World");
	nameOfMap.setFillColor(sf::Color::Black);
	nameOfMap.setPosition(sf::Vector2f(nameOfMapBox.getPosition().x + 3, nameOfMapBox.getPosition().y + 3));


	amountOfPlayer.setFont(font);
	startText.setFont(font);

	startText.setString("start");
	startText.setCharacterSize(30);
	startText.setPosition(sf::Vector2f(shape.getGlobalBounds().width * (float) 0.99 - startText.getGlobalBounds().width, shape.getGlobalBounds().height * (float) 0.97 - startText.getGlobalBounds().height));

	amountOfPlayer.setCharacterSize(80);
	amountOfPlayer.setString(std::to_string(amountOfPlayerValue));
	amountOfPlayer.setFillColor(sf::Color::White);
	amountOfPlayer.setPosition(sf::Vector2f(shape.getGlobalBounds().width / (float) 2 - amountOfPlayer.getGlobalBounds().width / (float) 2, (float) 100 - amountOfPlayer.getGlobalBounds().height / (float) 2));

	increase.setTexture(textureOfIncrease);
	decrease.setTexture(textureOfDecrease);
	startButton.setTexture(textureOfStartButton);
	increase.setPosition(sf::Vector2f(amountOfPlayer.getPosition().x + amountOfPlayer.getGlobalBounds().width + increase.getGlobalBounds().width * 2, amountOfPlayer.getPosition().y + amountOfPlayer.getGlobalBounds().height / 2 + increase.getGlobalBounds().height / 2));
	decrease.setPosition(sf::Vector2f(amountOfPlayer.getPosition().x - decrease.getGlobalBounds().width * 3, amountOfPlayer.getPosition().y + amountOfPlayer.getGlobalBounds().height / 2 + decrease.getGlobalBounds().height / 2));
	startButton.setPosition(sf::Vector2f(startText.getPosition().x - startText.getGlobalBounds().width, startText.getPosition().y));


	textureOfIndicator.loadFromFile("pictures/playerBoxIndicator.png");

	for (int i = 0; i < 6; i++)
	{
		playerBoxes[i].setSize(sf::Vector2f(200, 200));
		playerBoxes[i].setPosition(sf::Vector2f((float) (235 +  i * 250), (float) 500));

		playerBoxIndicator[i].setTexture(textureOfIndicator);
		playerBoxIndicator[i].setPosition(sf::Vector2f(playerBoxes[i].getPosition().x, playerBoxes[i].getPosition().y - playerBoxIndicator[i].getGlobalBounds().height));


		usernameBoxes[i].setSize(sf::Vector2f(200, 25));
		usernameBoxes[i].setFillColor(sf::Color(150, 150, 150));
		usernameBoxes[i].setPosition(sf::Vector2f(playerBoxes[i].getPosition().x, playerBoxes[i].getPosition().y + playerBoxes[i].getGlobalBounds().height + 25));

		username[i].setFont(font);
		username[i].setCharacterSize(20);
		username[i].setFillColor(sf::Color::Black);
		username[i].setPosition(sf::Vector2f(usernameBoxes[i].getPosition().x + 2, usernameBoxes[i].getPosition().y + 2));
		
		connectionBoxes[i].setSize(sf::Vector2f(200, 25));
		connectionBoxes[i].setFillColor(sf::Color(150, 150, 150));
		connectionBoxes[i].setPosition(sf::Vector2f(usernameBoxes[i].getPosition().x, usernameBoxes[i].getPosition().y + usernameBoxes[i].getGlobalBounds().height + 25));

		connection[i].setFont(font);
		connection[i].setCharacterSize(20);
		connection[i].setFillColor(sf::Color::Black);
		connection[i].setPosition(sf::Vector2f(connectionBoxes[i].getPosition().x + 2, connectionBoxes[i].getPosition().y + 2));
		

	}

	return true;
}

int ClientLobby::getInteraction()
{
	sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	if (spot == -1)
	{
		for (int i = 0; i < amountOfPlayerValue; i++)
		{
			if (connection[i].getString() == "Client - open")
			{
				if (playerBoxIndicator[i].getGlobalBounds().contains(position))
				{
					playerBoxIndicator[i].setColor(sf::Color::Red);
					return i;
				}
			}
		}
	}
	else
	{
		if (playerBoxes[spot].getGlobalBounds().contains(position))
		{
			return 6;
		}
		else if (usernameBoxes[spot].getGlobalBounds().contains(position))
		{
			return 7;
		}
	}


	return -1;
}

void ClientLobby::resetInteraction()
{
	if (spot == -1)
	{
		for (auto& i : playerBoxIndicator)
		{
			i.setColor(sf::Color::White);
		}
	}
}

void ClientLobby::run(sf::RenderWindow& window, sf::Event* event, Game** game, bool& isLobby, bool& inGame)
{
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
		if (event->type == sf::Event::MouseButtonPressed)
		{
			if (event->mouseButton.button == sf::Mouse::Left)
			{

				if (interaction != -1)
				{
					if(spot == -1)
					{
						sf::Packet takeSpot;
						std::string action = "takeSpot";
						int choosenSpot = interaction;

						takeSpot << action << choosenSpot;
						
						sf::Socket::Status status = host->send(takeSpot);
						while (status == sf::Socket::Partial)
						{
							status = host->send(takeSpot);
						}
					}
					else if (interaction == 6)
					{
						this->changeColor();
						//test
					}
					else if (interaction == 7)
					{
						if (isTyping == false)
						{
							isTyping = true;
							usernameBoxes[spot].setFillColor(sf::Color::White);
						}
						else
						{
							isTyping = false;
							usernameBoxes[spot].setFillColor(sf::Color(150, 150, 150));

						}
					}
				}
			}
		}
		else if (event->type == sf::Event::TextEntered)
		{
			if (isTyping == true && spot != -1)
			{
				if (event->text.unicode != 13)
				{
					if (event->text.unicode != 8)
					{
						username[spot].setString(username[spot].getString() + event->text.unicode);

					}
					else
					{
						std::string reducedUsername = username[spot].getString();
						username[spot].setString(reducedUsername.substr(0, (int)reducedUsername.size() - 1));
					}

					sf::Packet changeUsername;
					std::string action = "changeUsername";
					std::string newUsername = username[spot].getString();

					changeUsername << action << newUsername;

					sf::Socket::Status status = host->send(changeUsername);
					while (status == sf::Socket::Partial)
					{
						status = host->send(changeUsername);
					}

				}
			}
		}
	}

	sf::Packet received;
	
	if (host->receive(received) != sf::Socket::NotReady)
	{
		std::string action;
		received >> action;

		if (action == "changeUsername")
		{
			this->changeUsernameByNetwork(received);
		}
		else if (action == "changeColor")
		{
			this->changeColorByNetwork(received);
		}
		else if (action == "changeConnection")
		{
			this->changeConnectionByNetwork(received);
		}
		else if (action == "reset")
		{
			this->resetByNetwork(received);
		}
		else if (action == "increase")
		{
			this->increaseByNetwork(received);
		}
		else if (action == "decrease")
		{
			this->decreaseByNetwork(received);
		}
		else if (action == "getSpot")
		{
			this->getSpotByNetwork(received);
		}
		else if (action == "start")
		{
			std::cout << "i should start now" << std::endl;
			this->start(game, isLobby, inGame, window);
			//this->startByNetwork(received);
		}
		else if (action == "changeMap")
		{
			//this->changeMapByNetwork(received);
		}



		received.clear();
	}



	this->draw(window);
}

void ClientLobby::changeColor()
{
	sf::Color color = playerBoxes[spot].getFillColor();
	if (color == sf::Color::White)
	{
		playerBoxes[spot].setFillColor(sf::Color::Green);
	}
	else if (color == sf::Color::Green)
	{
		playerBoxes[spot].setFillColor(sf::Color::Red);
	}
	else if (color == sf::Color::Red)
	{
		playerBoxes[spot].setFillColor(sf::Color::Blue);
	}
	else if (color == sf::Color::Blue)
	{
		playerBoxes[spot].setFillColor(sf::Color::Yellow);
	}
	else if (color == sf::Color::Yellow)
	{
		playerBoxes[spot].setFillColor(sf::Color::Magenta);
	}
	else if (color == sf::Color::Magenta)
	{
		playerBoxes[spot].setFillColor(sf::Color::Cyan);
	}
	else if (color == sf::Color::Cyan)
	{
		playerBoxes[spot].setFillColor(sf::Color::White);
	}


	sf::Packet changeColor;
	std::string action = "changeColor";
	int r = playerBoxes[spot].getFillColor().r;
	int g = playerBoxes[spot].getFillColor().g;
	int b = playerBoxes[spot].getFillColor().b;

	changeColor << action << r << g << b;

	sf::Socket::Status status = host->send(changeColor);
	while (status == sf::Socket::Partial)
	{
		status = host->send(changeColor);
	}
}

void ClientLobby::changeUsernameByNetwork(sf::Packet& packet)
{
	int field;
	std::string newUsername;

	packet >> field >> newUsername;

	username[field].setString(newUsername);
	
}


void ClientLobby::changeColorByNetwork(sf::Packet& packet)
{
	int field;
	int r, g, b;

	packet >> field >> r >> g >> b;

	playerBoxes[field].setFillColor(sf::Color(r, g, b));

}

void ClientLobby::changeConnectionByNetwork(sf::Packet& packet)
{
	int field;
	std::string newConnection;

	packet >> field >> newConnection;

	connection[field].setString(newConnection);

}

void ClientLobby::resetByNetwork(sf::Packet& packet)
{
	int field;
	packet >> field;

	playerBoxes[field].setFillColor(sf::Color::White);
	username[field].setString("");
	connection[field].setString("Client - closed");

}

void ClientLobby::increaseByNetwork(sf::Packet& packet)
{
	int newAmount;
	packet >> newAmount;

	amountOfPlayerValue = newAmount;
	amountOfPlayer.setString(std::to_string(amountOfPlayerValue));


	username[amountOfPlayerValue - 1].setString("");
	playerBoxes[amountOfPlayerValue - 1].setFillColor(sf::Color::White);
	connection[amountOfPlayerValue - 1].setString("Client - closed");
}





void ClientLobby::decreaseByNetwork(sf::Packet& packet)
{
	int newAmount;
	packet >> newAmount;

	amountOfPlayerValue = newAmount;
	amountOfPlayer.setString(std::to_string(amountOfPlayerValue));


	username[amountOfPlayerValue].setString("");
	playerBoxes[amountOfPlayerValue].setFillColor(sf::Color::White);
	connection[amountOfPlayerValue].setString("Client - closed");
}



void ClientLobby::getSpotByNetwork(sf::Packet& packet)
{
	int newSpot;
	packet >> newSpot;

	spot = newSpot;
	playerBoxIndicator[spot].setColor(sf::Color::Green);
	
}



void ClientLobby::draw(sf::RenderWindow& window)
{

	window.draw(shape); // Textur hinzufügen
	window.draw(nameOfMapBox);
	window.draw(nameOfMap); // eingabe hinzufügen
	window.draw(amountOfPlayer);
	window.draw(increase);
	window.draw(decrease);
	window.draw(startButton);
	window.draw(startText);
	for (int i = 0; i < amountOfPlayerValue; i++)
	{
		window.draw(playerBoxes[i]);

		if (connection[i].getString() == "Client - open" && spot == -1)
		{
			window.draw(playerBoxIndicator[i]);
		}
		window.draw(usernameBoxes[i]);
		window.draw(username[i]);

		
		window.draw(connectionBoxes[i]);
		window.draw(connection[i]);
		
	}
	if (spot != -1)
	{
		window.draw(playerBoxIndicator[spot]);
	}


	if (isWarning)
	{
		warning.draw(window);
	}
}



void ClientLobby::start(Game** game, bool& isLobby, bool& inGame, sf::RenderWindow& window)
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
	
	*game = new ClientGame();
	(*game)->startGame(amountOfPlayerValue, &usernameStr, &playerColor, host, spot);
	isLobby = false;
	inGame = true;
	
}