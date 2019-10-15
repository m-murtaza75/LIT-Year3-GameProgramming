/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#pragma once
#ifndef GOBLIN_H
#define GOBLIN_H

#include "GameCharacter.h"

class Goblin : public GameCharacter
{
public:
	virtual void update(Level &level);

private:
	/* Variable to get the opposite element in the direction this character is moving */
	char nextTile;
	/* Decision variable for determining direction to move */
	bool movingRight;
};

#endif // !GOBLIN_H
