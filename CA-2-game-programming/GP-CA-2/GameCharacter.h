/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#pragma once
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "Level.h"
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <vector>
//To fix error C2679 
#include <string>

using namespace std;

class GameCharacter
{
public:
	void spawn(string typeID, int health,int x, int y, int experience, int luck);
	
	void setPosition(int x, int y);
	/* Virtual function to update character */
	virtual void update(Level &level);
	/* print all stats relating to the object */
	void stats();
	/* return 1 if its health is greater than 0 */
	bool isAlive();
	//Returns position X
	int posX(); 
	//Returns position Y
	int posY();

	/* Return Character-name */
	string checkType();
	/* Return Character's health */
	int checkHealth();
	/* Set Health to zero */
	void dead();

	/* Set the character's health to half */
	void hurt();
	/* This function returns the total of health, experience and luck */
	virtual int totalStrength();
	/* Virtual function for increasing experience of a character */ 
	virtual void gainExperience();
	/* Virtual function for increasing luck of a character */
	virtual void gainLuck();

protected:
	string m_typeID;
	int m_health;
	int m_x;
	int m_y;
	int m_experience;
	int m_luck;
	
};
#endif // !GAMECHARACTER_H
