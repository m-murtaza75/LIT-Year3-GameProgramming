#pragma once
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

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
	void spawn(std::string typeID, int health, int speed, int x, int y);
	void render(); // print to the screen the typeID and its x and y coords
	virtual void update(); //virtual function
	void stats(); // print all stats relating to the object
	bool isAlive(); //return 1 if its health is greater than 0
	int posX();
	int posY();
	string checkType();
	int checkHealth();
	void dead();
	void hurt();

protected:
	std::string m_typeID;
	int m_health;
	int m_speed;
	int m_x;
	int m_y;
};


#endif // !GAMECHARACTER_H
