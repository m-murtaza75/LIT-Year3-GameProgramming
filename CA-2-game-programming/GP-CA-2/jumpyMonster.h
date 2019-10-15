/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#pragma once
#ifndef JUMPYMONSTER_H
#define JUMPYMONSTER_H

#include "GameCharacter.h"

class JumpyMonster : public GameCharacter
{
public:
	virtual void update(Level &level);

private:
	/* Decision Variable to control character movement */
	bool hasJumped;
};

#endif // !JUMPYMONSTER_H
