/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameCharacter.h"

class Player : public GameCharacter
{
public:
	virtual void update(Level &level);
	/* Virtual function for increasing experience of player */
	virtual void gainExperience();
	/* Virtual function for increasing luck of player */
	virtual void gainLuck();

	//void responseToMove(Level &level, int targetX, int targetY);
	
};

#endif // !PLAYER_H
