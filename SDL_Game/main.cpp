#include "Game.h"
#include "Player.h"
#include "OwnMathFuncs.h"
#include "SDL.h"

int main(int argc, char* args[]) {

	Game *main_game = new Game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, false);

	//Add the player in the game
	Player *player = new Player(main_game->getRenderer());

	OwnMathFuncs::Vector2* sprite = new OwnMathFuncs::Vector2();
	sprite->x = 32;
	sprite->y = 32;
	main_game->addGameObject(player, "img/rat.png", sprite);

	while (main_game->getIsRunning()) {

		main_game->handleEvents();
		main_game->update();
		main_game->render();

	}

	main_game->clean();
	return 0;
}