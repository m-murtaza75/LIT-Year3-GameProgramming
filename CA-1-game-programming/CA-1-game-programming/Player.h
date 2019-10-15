#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameCharacter.h"

class Player : public GameCharacter
{
public:
	virtual void update();
};

#endif // !PLAYER_H
