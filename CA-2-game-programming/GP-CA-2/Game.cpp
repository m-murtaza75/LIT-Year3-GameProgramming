/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#include "Game.h"
#include <list>


void Game::welcomeMsg()
{
	cout << "WELCOME TO MONS-BUSTER!\n";
	cout << "\nPlayer you are on a mission to save your people from Monsters.\nThey have locked the door to escape from their world. Only you can save the people now.\n\n";
}

void Game::instructions()
{
	cout << "!!!INSTRUCTIONS!!!\n";
	cout << "1. Collect pickups ($ and T) to increase your winning chances against Monsters.\n";
	cout << "2. Beat the weakest Monster first to gain experience to compete against stronger ones.\n";
	cout << "3. Monsters list starting from weakest: Static Enemy: @, Jumpy: M, Goblin: G, Ogre: O\n\n";

	cout << "Great! you are good to start the game. Press any key to start the game.\n";

	system("PAUSE");
}

void Game::init()
{
	/* Loading game level*/
	level.load("monsBuster.txt");

	/*
	*	Spawning Characters.
	*	object.spawn(name, health, x-coord, y-coord, experience, luck)
	*/
	player->spawn("Player1", 130, 1, 1, 0, 40);
	e1->spawn("Static-Enemy", 80, 3, 3, 5, 20);
	e2->spawn("Static-Enemy 2", 85, 23, 9, 5, 20);
	jumpy->spawn("Jumpy", 150, 14, 11, 20, 45);
	goblin->spawn("Goblin", 160, 21, 4, 25, 60);
	goblin2->spawn("Goblin 2", 165, 59, 8, 25, 60);
	goblin3->spawn("Goblin 3", 165, 53, 13, 35, 60);
	ogre->spawn("Ogre", 180, 62, 13, 100, 96);
	ogre2->spawn("Ogre 2", 180, 64, 12, 100, 96);

	/* Spawning Pickups */
	treasure->spawn("T1", 1, 5, 7, 0, 0);
	treasure2->spawn("T2", 1, 5, 10, 0, 0);
	treasure3->spawn("T3", 1, 21, 2, 0, 0);
	treasure4->spawn("T4", 1, 55, 7, 0, 0);
	treasure5->spawn("T5", 1, 63, 13, 0, 0);
	coin->spawn("C1", 1, 15, 12, 0, 0);
	coin2->spawn("C2", 1, 18, 2, 0, 0);
	coin3->spawn("C3", 1, 20, 8, 0, 0);
	coin4->spawn("C4", 1, 53, 7, 0, 0);
	coin5->spawn("C5", 1, 49, 14, 0, 0);
	coin6->spawn("C6", 1, 52, 15, 0, 0);


	/* Spawning Acid object*/
	acid->spawn("Acid", 0, 57, 7, 0, 0);

	/* Spawning Door object (level end goal) */
	door->spawn("Door", 0, 55, 15, 0, 0);

	/* Setting Characters positions on the level */
	level.setTile(1,  1, 'P');
	level.setTile(3,  3, '@'); //Static-Enemy 
	level.setTile(23, 9, '@'); //Static-Enemy 2
	level.setTile(14, 11,'M');
	level.setTile(21, 4, 'G'); //Goblin
	level.setTile(59, 8, 'G'); //Goblin 2
	level.setTile(53, 13, 'G'); //Goblin 3
	level.setTile(62, 13, 'O'); //Ogre
	level.setTile(64, 12, 'O'); //Ogre 2
	level.setTile(57, 7, 'A'); //Acid
	level.setTile(55, 15, 'D'); //Door

	/* Setting Pickup Position on the level */
	level.setTile(5, 7, 'T'); //Treasure 1
	level.setTile(5, 10,'T'); //Treasure 2
	level.setTile(21, 2, 'T'); //Treasure 3
	level.setTile(55, 7, 'T'); //Treasure 4
	level.setTile(63, 13, 'T'); //Treasure 5
	level.setTile(15, 12, '$'); //Coin
	level.setTile(18, 2, '$'); //Coin 2
	level.setTile(20, 8, '$'); //Coin 3
	level.setTile(53, 7, '$'); //Coin 4
	level.setTile(49, 14, '$'); //Coin 5
	level.setTile(52, 15, '$'); //Coin 6

	
	/* Adding Enemies into their list */
	m_gameEnemiesList.push_back(e1);
	m_gameEnemiesList.push_back(e2);
	m_gameEnemiesList.push_back(jumpy);
	m_gameEnemiesList.push_back(goblin);
	m_gameEnemiesList.push_back(goblin2);
	m_gameEnemiesList.push_back(goblin3);
	m_gameEnemiesList.push_back(ogre);
	m_gameEnemiesList.push_back(ogre2);

	/* Adding pickups into their list */
	m_gamePickupList.push_back(coin);
	m_gamePickupList.push_back(coin2);
	m_gamePickupList.push_back(coin3);
	m_gamePickupList.push_back(coin4);
	m_gamePickupList.push_back(coin5);
	m_gamePickupList.push_back(coin6);
	m_gamePickupList.push_back(treasure);
	m_gamePickupList.push_back(treasure2);
	m_gamePickupList.push_back(treasure3);
	m_gamePickupList.push_back(treasure4);
	m_gamePickupList.push_back(treasure5);


}


void Game::render()
{
	/* Printing Level map on screen */
	level.print();
	
}


void Game::update()
{
	/* List iterator to iterate through enemies list*/
	list<GameCharacter*>::const_iterator it;

	//Calling update function of the gamecharacters
	for (it = m_gameEnemiesList.begin(); it != m_gameEnemiesList.end(); it++)
	{

		(*it)->update(level);

	}

	/* Calling player's update method*/
	player->update(level);	

}


void Game::battle()
{
	/* List for checking if battle occurs */
	list<GameCharacter*>::const_iterator it;


	//cout << "\nCalling GAME->BATTLE\n";

	for (it = m_gameEnemiesList.begin(); it != m_gameEnemiesList.end(); it++)
	{
		if ((player->posX() == (*it)->posX()) && (player->posY() == (*it)->posY()))
		{
			cout << "BATTLE begins!...\n";

			if (player->totalStrength() > (*it)->totalStrength())
			{
				(*it)->dead();
				level.setTile((*it)->posX(), (*it)->posY(), 'P');
				player->gainExperience();
				cout << "Wow! Player you win, experience increased.\n";
			}
			else if (player->totalStrength() < (*it)->totalStrength())
			{
				string enemyName = (*it)->checkType();
				player->dead();
				cout << "\nOh no! Player you are dead. " << enemyName << " wins.\n";
			}
			else
			{
				player->hurt();
				(*it)->hurt();
			}
		}
	}

	


}


void Game::stats()
{
	/* Printing player's stats if he is alive*/
	if (player->checkHealth() > 0)
	{
		player->stats();
		mapDetail();
	}
}

void Game::clean()
{
	list<GameCharacter*>::const_iterator it;

	if (!player->isAlive())
	{
		delete player;
		player = 0;

		cout << "\nGame over! Thank you for playing.\n";
		system("PAUSE");
		exit(0);
	}

	/* Iterating through list if its size is greater than 0
	*  Otherwise it reaches end of list and give exception 
	*/
	if (m_gameEnemiesList.size() != 0)
	{
		for (it = m_gameEnemiesList.begin(); it != m_gameEnemiesList.end(); it++)
		{
			if (!(*it)->isAlive())
			{
				delete *it;
				it = m_gameEnemiesList.erase(it);
			}

			if (m_gameEnemiesList.size() == 0)
			{
				/* Break through the loop to prevent end of list error */
				break;
			}
		}
	}

	/* For pickups list */
	if (m_gamePickupList.size() != 0)
	{
		for (it = m_gamePickupList.begin(); it != m_gamePickupList.end(); it++)
		{
			if (!(*it)->isAlive())
			{
				delete *it;
				it = m_gamePickupList.erase(it);
			}

			if (m_gamePickupList.size() == 0)
			{
				/* Break through the loop to prevent end of list error */
				break;
			}
		}
	}

}

/* Keeps the player aware of how many enemies are left in the map */
void Game::mapDetail()
{
	cout << "Enemy left: " << m_gameEnemiesList.size() << endl;
}


/* Below function opens the obstacle if all enemies are dead */
void Game::checkToOpenDoor()
{
	if (m_gameEnemiesList.size() == 0)
	{
		level.setTile(55, 13, '.');

		render();

		cout << "\nLevel-end Door is open now.\n";
	}
}

/* Below method to check if player fall in the acid place 'Player dies if he's in acid' */
void Game::hasTouchedAcid()
{
	if ((player->posX() == acid->posX()) && (player->posY() == acid->posY()))
	{
		level.setTile(player->posX(), player->posY(), 'A');
		player->dead();
		render();
		
		cout << "\nOh no! Player you are falling in acid";
		/* Deleting player object by calling game's clean method*/
		clean();

	}

}

void Game::reachedEnd()
{
	if ((player->posX() == door->posX()) && (player->posY() == door->posY()))
	{
		gameCompleted();
	}

}

void Game::gameCompleted()
{
	cout << string(32, '\n');

	cout << "GAME OVER!\n";
	cout << "Congratulations Player! This place is now safe from Monsters. YAAAY..\n";

	system("PAUSE");
	exit(0);
}


void Game::warning()
{
	if ((player->posX() == 54) && (player->posY() == 9))
	{
		cout << "\nWARNING! BEWARE from Acid.\n";
	}
}

void Game::pickupCollected()
{
	list<GameCharacter*>::const_iterator it;

	for (it = m_gamePickupList.begin(); it != m_gamePickupList.end(); it++)
	{
		if ((player->posX() == (*it)->posX()) && (player->posY() == (*it)->posY()))
		{
			(*it)->dead();

			level.setTile((*it)->posX(), (*it)->posY(), 'P');
			player->gainLuck();
			cout << "Wow! Player your luck increased.\n";

		}
	}
}