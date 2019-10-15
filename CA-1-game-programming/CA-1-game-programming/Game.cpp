#include "Game.h"
#include <list>



void Game::init()
{
	
	

	
	int x = 2;
	int y = 2;

	GameCharacter* player = new Player();

	GameCharacter* e1 = new Enemy();

	GameCharacter* e2 = new Enemy();

	GameCharacter* e3 = new Enemy();
	
	GameCharacter* e4 = new Enemy();



	//Spawing player.
	player->spawn("Player1", 165, 3, 1, 5);

	//Spawing Enemy objects
	e1->spawn("Enemy1", 145, 3, x+2, y+3);
	e2->spawn("Enemy2", 115, 1, x+9, y+11);
	e3->spawn("Enemy3", 130, 3, x+6, y+1);
	e4->spawn("Enemy4", 165, 2, x+10, y+5);



	m_gameCharacterObjectsList.push_back(player);
	m_gameCharacterObjectsList.push_back(e1);
	m_gameCharacterObjectsList.push_back(e2);
	m_gameCharacterObjectsList.push_back(e3);
	m_gameCharacterObjectsList.push_back(e4);


}


void Game::render()
{
	list<GameCharacter*>::const_iterator it;

	//Calling render function of the gameCharacters
	for (it = m_gameCharacterObjectsList.begin(); it != m_gameCharacterObjectsList.end(); it++)
	{
		(*it)->render();
	}
}


void Game::update()
{
	list<GameCharacter*>::const_iterator it;


	//Calling update function of the gamecharacters
	for (it = m_gameCharacterObjectsList.begin(); it != m_gameCharacterObjectsList.end(); it++)
	{
		(*it)->update();
	}

}


void Game::battle()
{
	list<GameCharacter*>::const_iterator it;

	list<GameCharacter*>::const_iterator it2;


	cout << "\nCalling GAME->BATTLE\n";

	for (it = m_gameCharacterObjectsList.begin(); it != m_gameCharacterObjectsList.end(); it++)
	{
		for (it2 = m_gameCharacterObjectsList.begin(); it2 != m_gameCharacterObjectsList.end(); ++it2)
		{
			if (it == it2)
			{
				continue;
			}
			else if (((*it)->posX() == (*it2)->posX()) && ((*it)->posY() == (*it2)->posY()))
			{
				
				cout << "BATTLE begins!...\n";
				cout << "Character: " << (*it)->checkType() << " VS " << (*it2)->checkType() << endl;

				if ((*it)->checkHealth() > (*it2)->checkHealth())
				{
					//cout << "Character: " << (*iter)->checkType() << " WIN\n";
					(*it2)->dead();
				}
				else if ((*it)->checkHealth() < (*it2)->checkHealth())
				{
					//cout << "Character: " << (*iter2)->checkType() << " WIN\n";
					(*it)->dead();
				}
				else
				{
					//cout << "\nIt's a DRAW\n";
					(*it)->hurt();
					(*it2)->hurt();
				}

			}
			


		}
	}


}


void Game::stats()
{
	list<GameCharacter*>::const_iterator it;

	//Calling stats function of the gamecharacters
	for (it = m_gameCharacterObjectsList.begin(); it != m_gameCharacterObjectsList.end(); it++)
	{
		(*it)->stats();
	}

}

void Game::clean()
{
	list<GameCharacter*>::const_iterator it;

	for (it = m_gameCharacterObjectsList.begin(); it != m_gameCharacterObjectsList.end();it++)
	{
		if (!(*it)->isAlive()) 
		{
			delete *it;
			it = m_gameCharacterObjectsList.erase(it);
		}
	}
}