#include "Game.h"
#include "Player.h"
#include "OwnMathFuncs.h"
#include "SDL.h"
#include "Enemy.h"
#include "SlimPrefab.h"
#include "DisplayPlayerHealth.h"
#include "GoblinPrefab.h"
#include "MinotaurPrefab.h"
#include "SnakePrefab.h"

int main(int argc, char* args[]) {

	Game::setInstance(new Game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, false));

	//Add the background
	
	Map* map = new Map("img/dungeon_tileset.png", { 16,16 }, "levels/TileMap_5_0.csv", "levels/TileMap_5_Collider.csv");
	Game::instance()->instantiateGameObject(map);
	
	Map* map2 = new Map("img/dungeon_tileset.png", { 16, 16 }, "levels/TileMap_5_1.csv");
	Game::instance()->instantiateGameObject(map2);


	//Add the player in the game
	Player *player = new Player("img/player.png", { 32, 32 }, { 1366, 768 });
	Game::instance()->instantiateGameObject(player);


	Game::instance()->getCamera()->setObjectToFollow(player);

	//----------- ADD ENEMY ----------------
	/*
	SlimPrefab * slim = new SlimPrefab({ 1000, 900 });
	Game::instance()->instantiateGameObject(slim);
	*/

	/*
	GoblinPrefab *goblin = new GoblinPrefab({ 900, 768 });
	Game::instance()->instantiateGameObject(goblin);
	*/

	/*
	MinotaurPrefab *minotaur = new MinotaurPrefab({ 900, 800 });
	Game::instance()->instantiateGameObject(minotaur);
	*/

	SnakePrefab* snake = new SnakePrefab({ 900, 800 });
	Game::instance()->instantiateGameObject(snake);

	//--------------------------------------

	//----------- Add UI Manager ----------------
	GameObject* ui_manager = new GameObject();
	DisplayPlayerHealth* display = new DisplayPlayerHealth(ui_manager, player->getComponent<PlayerStat>());
	display->setLayer(10);

	Game::instance()->instantiateGameObject(ui_manager);
	//--------------------------------------


	float timePassed = 0;
	int i = 0;

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

			Game::instance()->addGameObjectInGame(enemy);

			timePassed = 0.0000000000005;
			i++;
			*/
		}
	}

	Game::instance()->clean();
	return 0;
}