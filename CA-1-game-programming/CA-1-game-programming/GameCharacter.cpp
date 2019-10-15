#include "GameCharacter.h"


void GameCharacter::spawn(string characterType, int health, int speed, int x, int y)
{
	m_typeID = characterType;

	m_health = health;

	m_speed = speed;

	m_x = x;

	m_y = y;

}


void GameCharacter::render()
{
	cout << "Character ID: " << m_typeID << endl;
	cout << "X: " << m_x << "\tY: " << m_y << endl;


}


void GameCharacter::update()
{
	cout << "This method is used as a template for updating x-y coordinates of character" << endl;
}


void GameCharacter::stats()
{
	cout << "\nCharacter STATS\n";
	cout << "Character ID: " << m_typeID << endl;
	cout << "X: " << m_x << "\tY: " << m_y << endl;
	cout << "Health: " << m_health << endl;
	cout << "Speed: " << m_speed << endl;
	cout << "Alive: " << isAlive() << "\n\n";

}

bool GameCharacter::isAlive()
{
	bool isAlive = false;
	if (m_health > 0)
	{
		isAlive = true;
		return isAlive;
	}

	return isAlive;

}

int GameCharacter::posX()
{
	return m_x;
}

int GameCharacter::posY()
{
	return m_y;
}

string GameCharacter::checkType()
{
	return m_typeID;
}

int GameCharacter::checkHealth()
{
	return m_health;
}

void GameCharacter::dead()
{
	m_health = 0;

}

void GameCharacter::hurt()
{
	m_health = m_health / 2;

}