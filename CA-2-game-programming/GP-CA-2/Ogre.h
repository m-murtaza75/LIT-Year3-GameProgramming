/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#pragma once
#ifndef OGRE_H
#define OGRE_H

#include "GameCharacter.h"

class Ogre : public GameCharacter
{
public:
	virtual void update(Level &level);

private:
	/* Variable to get the opposite element in the direction this character is moving */
	char nextTile;
	/* Decision variable to move in particular direction */
	int directionToMove = 1;
};

#endif // !OGRE_H


