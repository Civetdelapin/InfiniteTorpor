#include "Game.h"
#include "Player.h"
#include "OwnMathFuncs.h"
#include "SDL.h"
#include "Enemy.h"
#include "SlimPrefab.h"
#include "DisplayPlayerHealth.h"
#include "GoblinPrefab.h"

int main(int argc, char* args[]) {

	Game::setInstance(new Game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, false));

	//Add the background
	
	Map* map = new Map("img/dungeon_tileset.png", { 16,16 }, "levels/TileMap_5_0.csv", "levels/TileMap_5_Collider.csv");
	map->layer = -1;

	Game::instance()->addGameObject(map);
	
	Map* map2 = new Map("img/dungeon_tileset.png", { 16, 16 }, "levels/TileMap_5_1.csv");
	map2->layer = 10;

	Game::instance()->addGameObject(map2);


	//Add the player in the game
	Player *player = new Player("img/player.png", { 32, 32 });
	player->layer = 5;

	Game::instance()->addGameObject(player);

	player->local_position.x = 1366;
	player->local_position.y = 768;


	Game::instance()->getCamera()->setObjectToFollow(player);


	//Add enemy
	
	SlimPrefab * slim = new SlimPrefab("img/slimes.png", { 32,32 });
	slim->layer = 4;

	slim->local_position.x = 1000;
	slim->local_position.y = 768;

	Game::instance()->addGameObject(slim);
	
	/*
	GoblinPrefab *goblin = new GoblinPrefab("img/goblin.png", new OwnMathFuncs::Vector2(32, 32));
	goblin->layer = 4;

	goblin->local_position.x = 900;
	goblin->local_position.y = 768;

	Game::instance()->addGameObject(goblin);
	*/



	//Add UI Manager
	GameObject* ui_manager = new GameObject();
	ui_manager->layer = 50;
	DisplayPlayerHealth* display = new DisplayPlayerHealth(ui_manager, player->getComponent<PlayerStat>());

	Game::instance()->addGameObject(ui_manager);


	float timePassed = 0;
	int i = 0;

	SlimPrefab *enemy = new SlimPrefab("img/slimes.png", { 32,32 });
	enemy = new SlimPrefab("img/slimes.png", { 32,32 });
	enemy->layer = 4;

	enemy->local_position.x = 1000 ;
	enemy->local_position.y = 768;

	Game::instance()->addGameObject(enemy);

	//Main loop of the game
	while (Game::instance()->getIsRunning()) {

		Game::instance()->handleEvents();
		Game::instance()->update();
		Game::instance()->render();

		timePassed -= Time::deltaTime;
		
		if (timePassed <= 0) {

			/*
			Game::instance()->destroyGameObject(enemy->getRootParent());

			enemy = new SlimPrefab("img/slimes.png", { 32,32 });
			enemy->layer = 4;

			enemy->local_position.x = 1000 + i * 10;
			enemy->local_position.y = 768;

			Game::instance()->addGameObject(enemy);

			timePassed = 0.0000000000005;
			i++;
			*/
		}
	}

	Game::instance()->clean();
	return 0;
}