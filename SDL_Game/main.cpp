#include "Game.h"
#include "Player.h"
#include "OwnMathFuncs.h"
#include "SDL.h"

int main(int argc, char* args[]) {

	Game *main_game = new Game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, false);

	//Add the background
	Map* map = new Map(main_game->getRenderer(),1);
	map->sprite_sizeX = 16;
	map->sprite_sizeY = 16;
	map->layer = -1;
	main_game->addGameObject(map);

	//map->position.x = (main_game->getScreenWidth() / 2);
	//map->position.y = (main_game->getScreenHeight() / 2);


	//Add the player in the game
	Player *player = new Player(main_game->getRenderer(), map);
	OwnMathFuncs::Vector2* sprite = new OwnMathFuncs::Vector2();
	sprite->x = 32;
	sprite->y = 32;
	player->layer = 5;
	main_game->addGameObject(player, "img/player.png", sprite);

	player->position.x = main_game->getScreenWidth() / 2;
	player->position.y = main_game->getScreenHeight() / 2;

	main_game->getCamera()->objectToFollow = player;

	while (main_game->getIsRunning()) {

		main_game->handleEvents();
		main_game->update();
		main_game->render();

	}

	main_game->clean();
	return 0;
}