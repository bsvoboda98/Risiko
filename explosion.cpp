#include "explosion.h"

Explosion::Explosion(sf::Vector2f position)
{
	explosionSprite.setPosition(position.x - 17, position.y - 17);
	explosionTexture.loadFromFile("pictures/explosion.png");
	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setTextureRect(sf::IntRect(status * 34,line * 34 , 34, 34));


}

bool Explosion::draw(sf::RenderWindow& window)
{
	if (line > 3)
	{
		return true;
	}
	else
	{
		window.draw(explosionSprite);

		status++;

		if (status > 4)
		{
			line++;
			status = 0;
		}

		explosionSprite.setTextureRect(sf::IntRect(status * 34, line * 34, 34, 34));

	}
	return false;
}