#include "Game.h"
#include "Player.h"
#include "OwnMathFuncs.h"
#include "SDL.h"

int main(int argc, char* args[]) {

	Game *main_game = new Game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, false);

	//Add the background
	
	Map* map = new Map("img/dungeon_tileset.png", new OwnMathFuncs::Vector2(16,16), "levels/TileMap_1.csv");
	map->layer = -1;
	main_game->addGameObject(map);
	

	//map->position.x = (main_game->getScreenWidth() / 2);
	//map->position.y = (main_game->getScreenHeight() / 2);

	
	GameObject* box_collider_test = new GameObject();
	BoxCollider* box_collider = new BoxCollider(box_collider_test);
	box_collider_test->addComponent(box_collider);
	
	main_game->addGameObject(box_collider_test);
	

	//Add the player in the game
	Player *player = new Player("img/player.png", new OwnMathFuncs::Vector2(32, 32));
	player->layer = 5;

	main_game->addGameObject(player);

	main_game->getCamera()->objectToFollow = player;


	//Main loop of the game
	while (main_game->getIsRunning()) {

		main_game->handleEvents();
		main_game->update();
		main_game->render();

	}

	main_game->clean();
	return 0;
}