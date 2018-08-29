#include "Game.h"
#include "Player.h"
#include "OwnMathFuncs.h"
#include "SDL.h"
#include "Enemy.h"
#include "SlimPrefab.h"

int main(int argc, char* args[]) {

	Game::setInstance(new Game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, false));

	//Add the background
	
	Map* map = new Map("img/dungeon_tileset.png", new OwnMathFuncs::Vector2(16,16), "levels/TileMap_5_0.csv", "levels/TileMap_5_Collider.csv");
	map->layer = -1;

	Game::instance()->addGameObject(map);
	
	Map* map2 = new Map("img/dungeon_tileset.png", new OwnMathFuncs::Vector2(16, 16), "levels/TileMap_5_1.csv");
	map2->layer = 10;

	Game::instance()->addGameObject(map2);


	//Add the player in the game
	Player *player = new Player("img/player.png", new OwnMathFuncs::Vector2(32, 32));
	player->layer = 5;

	Game::instance()->addGameObject(player);

	player->local_position.x = 1366;
	player->local_position.y = 768;


	Game::instance()->getCamera()->objectToFollow = player;


	//Add enemy
	SlimPrefab *enemy = new SlimPrefab("img/slimes.png", new OwnMathFuncs::Vector2(32, 32));
	enemy->layer = 4;

	enemy->local_position.x = 1000;
	enemy->local_position.y = 768;

	Game::instance()->addGameObject(enemy);




	//Main loop of the game
	while (Game::instance()->getIsRunning()) {

		Game::instance()->handleEvents();
		Game::instance()->update();
		Game::instance()->render();

	}

	Game::instance()->clean();
	return 0;
}