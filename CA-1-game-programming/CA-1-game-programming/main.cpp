#include "Game.h"

int main()
{

	Game game;

	game.init();
	
	for (int i = 0; i < 20; i++) {
		game.render();
		game.update();
		game.battle();
		game.stats();
		game.clean();
		cout << "\n";
		system("Pause");
		cout << "\n";
	}

	game.stats();


	return 0;
}