#pragma once
#ifndef GAME_H
#define GAME_H

#include "Enemy.h"
#include "Player.h"
#include <list>

class Game
{
public:
	void init();
	void render();
	void update();
	void battle();
	void stats();
	void clean();

private:
	std::list<GameCharacter*> m_gameCharacterObjectsList;

};

#endif // !GAME_H
