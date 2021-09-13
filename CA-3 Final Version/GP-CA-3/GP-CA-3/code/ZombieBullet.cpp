/*
	STUDENT NAME: MUHAMMAD MURTAZA
	STUDENT ID: K00223470
	CA: 3
	SUBJECT: GAME PROGRAMMING

*/

#include "ZombieBullet.h"


// The constructor
ZombieBullet::ZombieBullet()
{
	m_BulletShape.setSize(sf::Vector2f(8, 8));
	m_BulletShape.setFillColor(sf::Color::Black);
}

void ZombieBullet::shoot(float startX, float startY,
	float targetX, float targetY)
{
	// Keep track of the bullet
	m_InFlight = true;
	m_BulletPosition.x = startX;
	m_BulletPosition.y = startY;

	// Calculate the gradient of the flight path
	float gradient = (startX - targetX) / (startY - targetY);

	// Any gradient less than zero needs to be negative
	if (gradient < 0)
	{
		gradient *= -1;
	}

	// Calculate the ratio between x and t
	float ratioXY = m_BulletSpeed / (1 + gradient);

	// Set the "speed" horizontally and vertically
	m_BulletDistanceY = ratioXY;
	m_BulletDistanceX = ratioXY * gradient;

	// Point the bullet in the right direction
	if (targetX < startX)
	{
		m_BulletDistanceX *= -1;
	}

	if (targetY < startY)
	{
		m_BulletDistanceY *= -1;
	}

	// Finally, assign the results to the
	// member variables
	m_XTarget = targetX;
	m_YTarget = targetY;

	// Set a max range of 1000 pixels
	float range = 800;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;

	// Position the bullet ready to be drawn
	m_BulletShape.setPosition(m_BulletPosition);
}

void ZombieBullet::stop()
{
	m_InFlight = false;
}

bool ZombieBullet::isInFlight()
{
	return m_InFlight;
}

FloatRect ZombieBullet::getPosition()
{
	return m_BulletShape.getGlobalBounds();
}

RectangleShape ZombieBullet::getShape()
{
	return m_BulletShape;
}


void ZombieBullet::update(float elapsedTime)
{
	// Update the bullet position variables
	m_BulletPosition.x += m_BulletDistanceX * elapsedTime;
	m_BulletPosition.y += m_BulletDistanceY * elapsedTime;

	// Move the bullet
	m_BulletShape.setPosition(m_BulletPosition);

	// Has the bullet gone out of range?
	if (m_BulletPosition.x < m_MinX || m_BulletPosition.x > m_MaxX ||
		m_BulletPosition.y < m_MinY || m_BulletPosition.y > m_MaxY)
	{
		m_InFlight = false;
	}

}