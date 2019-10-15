/**
*	@Creator		Muhammad Murtaza
*	@StudentID		[K00223470]
*	@CreationDate	20/11/2018
*
**/

#include "Game.h"

int main()
{
	Game game;

	game.welcomeMsg();
	game.instructions();
	game.init();

	while (true)
	{
		game.render();
		game.stats();
		game.update();
		game.battle();
		game.pickupCollected();
		game.hasTouchedAcid();
		game.warning();
		game.checkToOpenDoor();
		game.reachedEnd();
		game.clean();

	}

	return 0;
}