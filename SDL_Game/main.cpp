#include "Game.h"
#include "Player.h"
#include "OwnMathFuncs.h"
#include "SDL.h"
#include "Enemy.h"
#include "GameManager.h"

#include "DisplayPlayerHealth.h"
#include "DisplayPlayerScore.h"
#include "DisplayScreenFadeInOut.h"
#include "DisplayBetweenFloor.h"
#include "DisplayGameOver.h"

#include "TransitionManager.h"

#include "SlimPrefab.h"
#include "GoblinPrefab.h"
#include "MinotaurPrefab.h"
#include "SnakePrefab.h"
#include "GenerateLevel.h"

int main(int argc, char* args[]) {

	Game::setInstance(new Game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false));


	//Add the player in the game
	Player *player = new Player({ 1366, 768 });
	Game::instance()->instantiateGameObject(player);


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

	/*
	SnakePrefab* snake = new SnakePrefab({ 900, 800 });
	Game::instance()->instantiateGameObject(snake);
	*/

	//--------------------------------------

	//----------- Add UI Manager ----------------
	GameObject* uiManager = new GameObject();
	uiManager->tag = "UI_Manager";
	uiManager->localScale = { 4, 4 };

	//Display the player's health
	DisplayPlayerHealth* display = new DisplayPlayerHealth(uiManager);
	
	//Display the player's score
	DisplayPlayerScore* display_score = new DisplayPlayerScore(uiManager);

	//Display the black screen
	DisplayScreenFadeInOut* display_screen = new DisplayScreenFadeInOut(uiManager);
	
		//----- TRANSITION MANAGER -----
		TransitionManager* transitionManager = new TransitionManager(uiManager);

		GameObject* betweenFloorGameObject = new GameObject();
		betweenFloorGameObject->active = false;
		DisplayBetweenFloor* displayBetweenFloor = new DisplayBetweenFloor(betweenFloorGameObject);
		transitionManager->transitionBetweenFloor = displayBetweenFloor;
		
		GameObject* gameOverGameObject = new GameObject();
		gameOverGameObject->active = false;
		DisplayGameOver* displayGameOver = new DisplayGameOver(gameOverGameObject);
		transitionManager->_transitionGameOver = displayGameOver;

		GameObject* gamePauseGameObject = new GameObject();
		gamePauseGameObject->active = false;
		DisplayGamePause* displayGamePause = new DisplayGamePause(gamePauseGameObject);

		uiManager->addGameObjectAsChild(gamePauseGameObject);
		uiManager->addGameObjectAsChild(betweenFloorGameObject);
		uiManager->addGameObjectAsChild(gameOverGameObject);
		//------------------------------

	Game::instance()->instantiateGameObject(uiManager);
	//--------------------------------------

	//------- Add Game Managers ------------
	GameObject* gameManager = new GameObject();
	gameManager->tag = "Manager";

	GenerateLevel* generate_level = new GenerateLevel(gameManager);
	GameManager* game_manager_component = new GameManager(gameManager);

	Game::instance()->instantiateGameObject(gameManager);
	//--------------------------------------


	//GameObject* enemy = new SlimPrefab({ 32,32 });
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

			enemy = new SlimPrefab({ 32,32 });

			enemy->localPosition.x = 1000 + i * 10;
			enemy->localPosition.y = 768;

			Game::instance()->instantiateGameObject(enemy);
			*/

			timePassed = 0.0000000000005;
			i++;
		}
	}

	Game::instance()->clean();
	return 0;
}