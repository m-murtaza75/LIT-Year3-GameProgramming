/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/


#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Level.h"
#include "GameCharacter.h"
#include "JumpyMonster.h"
#include "Goblin.h"
#include "Ogre.h"
#include <list>


class Game
{
public:
	/* Welcome Message */
	void welcomeMsg();
	/* Game Important Instructions*/
	void instructions();
	/* Initializing */
	void init();
	void render();
	void update();
	void battle();
	void stats();
	void clean();
	void mapDetail();
	void checkToOpenDoor();
	void hasTouchedAcid();
	void reachedEnd();
	void gameCompleted();
	void warning();
	void pickupCollected();

private:

	/* Player Declaration*/
	GameCharacter* player = new Player();
	
	/* Enemies Declaration */
	GameCharacter* e1 = new GameCharacter();
	GameCharacter* e2 = new GameCharacter();
	//Enemy that jumps only
	GameCharacter* jumpy = new JumpyMonster();
	//Goblin Enemy moves left and right
	GameCharacter* goblin = new Goblin();
	GameCharacter* goblin2 = new Goblin();
	GameCharacter* goblin3 = new Goblin();
	//Ogre Enemy moves in a fixed square path
	GameCharacter* ogre = new Ogre();
	GameCharacter* ogre2 = new Ogre();
	


	/* Pickups declaration */
	GameCharacter* treasure = new GameCharacter();
	GameCharacter* treasure2 = new GameCharacter();
	GameCharacter* treasure3 = new GameCharacter();
	GameCharacter* treasure4 = new GameCharacter();
	GameCharacter* treasure5 = new GameCharacter();
	GameCharacter* coin =  new GameCharacter();
	GameCharacter* coin2 = new GameCharacter();
	GameCharacter* coin3 = new GameCharacter();
	GameCharacter* coin4 = new GameCharacter();
	GameCharacter* coin5 = new GameCharacter();
	GameCharacter* coin6 = new GameCharacter();

	/* Acid Object to trick the player */
	GameCharacter* acid = new GameCharacter();

	/* Door object is level ender*/
	GameCharacter* door = new GameCharacter();


	/* Level declaration*/
	Level level;

	
	/*  List for storing enemy objects*/
	list<GameCharacter*> m_gameEnemiesList;

	/* List for storing game pickup objects */
	list<GameCharacter*> m_gamePickupList;

};

#endif // !GAME_H
