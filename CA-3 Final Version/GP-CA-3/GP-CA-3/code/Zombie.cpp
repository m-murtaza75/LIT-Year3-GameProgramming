#include "zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;


void Zombie::spawn(float startX, float startY, int type, int seed, IntRect arena)
{

	switch (type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/bloater.png"));

		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		break;

	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/chaser.png"));

		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		break;

	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/crawler.png"));

		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;

	case 3:
		// Dodger
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/dodger.png"));

		m_Speed = DODGER_SPEED;
		m_Health = DODGER_HEALTH;
		m_dodgeAbility = true;
		break;

	case 4:
		// Spitter
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/spitter.png"));

		m_Speed = SPITTER_SPEED;
		m_Health = SPITTER_HEALTH;
		m_FireAbility = true;
		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0) * seed);
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;

	m_Position.x = startX;
	m_Position.y = startY;


	maxX = arena.width - 20;
	minX = arena.left + 20;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

bool Zombie::hit()
{
	m_Health--;

	if (m_Health < 0)
	{
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}

	// injured but not dead yet
	return false;
}

bool Zombie::isAlive()
{
	return m_Alive;
}

bool Zombie::isFiring()
{
	return m_FireAbility;
}

// Reset fireTimer
void Zombie::resetFireTimer()
{
	fireTimer.restart();
}


FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

// Returns fireTimer in milliseconds
long Zombie::getFireTimer()
{
	long time = fireTimer.getElapsedTime().asMilliseconds();

	return time;
}

//Adding for the shooting purpose
Vector2f Zombie::getCenter()
{
	return m_Position;
}

Sprite Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::update(float elapsedTime,
	Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the zombie position variables
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x +
			m_Speed * elapsedTime;
	}

	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y +
			m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x -
			m_Speed * elapsedTime;
	}

	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y -
			m_Speed * elapsedTime;
	}

	if (m_dodgeAbility)
	{
		if (movementTimer.getElapsedTime().asMilliseconds() > 2000 && (xCounter > 0 && xCounter < 800))
		{
			m_Position.x = m_Position.x + 0.25;
			xCounter++;

			if (m_Position.x > maxX)
			{
				m_Position.x = maxX;
			}
		}

		if (xCounter == 800)
		{
			movementTimer.restart();
			//long time = movementTimer.getElapsedTime().asMilliseconds();
			xCounter++;
		}

		if (movementTimer.getElapsedTime().asMilliseconds() > 1200 && xCounter > 800)
		{
			m_Position.x = m_Position.x - 0.25;
			xCounter++;

			if (m_Position.x < minX)
			{
				m_Position.x = minX;
			}
		}

		if (xCounter > 1600)
		{
			xCounter = 1;
			movementTimer.restart();
		}
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);

}