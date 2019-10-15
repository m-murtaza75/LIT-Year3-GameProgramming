#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "GameCharacter.h"



class Enemy : public GameCharacter
{
public:
	virtual void update();

};


#endif // !ENEMY_H
