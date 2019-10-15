/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#include "GameCharacter.h"


//std::string typeID, int health, int x, int y, int experience, int luck
void GameCharacter::spawn(string characterType, int health, int x, int y, int xp, int luck)
{
	m_typeID = characterType;

	m_health = health;

	m_x = x;

	m_y = y;

	m_experience = xp;

	m_luck = luck;

}


/*
* update method is used as a template for updating x-y coordinates of character on the level
*/
void GameCharacter::update(Level &level)
{
	
}

int GameCharacter::totalStrength()
{
	int strength;

	strength = m_health + m_experience + m_luck;

	return strength;
}


void GameCharacter::stats()
{
	cout << "\nCharacter STATS\n";
	cout << "Character ID: " << m_typeID << "\tHealth: " << m_health << "\tLuck: " << m_luck << "\tExperience: " << m_experience << endl;
	cout << "X: " << m_x << "\tY: " << m_y << endl;
	cout << "Alive: " << isAlive() << "\n";

}

bool GameCharacter::isAlive()
{
	bool isAlive = false;
	if (this->m_health > 0)
	{
		isAlive = true;
		return isAlive;
	}

	return isAlive;

}


void GameCharacter::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
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

/**
*	Method Template that can be overload by the derived classes 
*/
void GameCharacter::gainExperience()
{
	
}

/**
*	Method Template that can be overload by the derived classes
*/
void GameCharacter::gainLuck()
{

}