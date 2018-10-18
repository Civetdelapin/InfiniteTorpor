#include "Game.h"

Game *Game::s_instance = 0;

Game::Game(const char * title, int xpos, int ypos, int width, int height, bool fullscreen, bool isDebugMode) : isDebugMode(isDebugMode), screenSize({(float) width, (float) height})
{

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		printInConsole("Subsytems Initilialised !");

		int flags = 0;
		if (fullscreen) {
			flags = SDL_WINDOW_FULLSCREEN;
		}
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != nullptr) {
			printInConsole("Window created!");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer != nullptr) {
			printInConsole("renderer created!");
		}

		collider_manager = new ColliderManager();
		camera = new Camera(this);

		TTF_Init();

		isRunning = true;
	}
	else {
		isRunning = false;
	}

}

Game::~Game()
{

}

void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
	
	collider_manager->update();
	
	//We delete the objects that need to be deleted
	for (GameObject* gameObject : gameObjectsToDestroy) {

		if (gameObject->parentGameObject == nullptr) {
			gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject), gameObjects.end());
		}
		else {
			gameObject->parentGameObject->getChildren().erase(std::remove(gameObject->parentGameObject->getChildren().begin(), gameObject->parentGameObject->getChildren().end(), gameObject), gameObject->parentGameObject->getChildren().end());
		}


		//collider_manager->removeGameObjectColliders(gameObject);

		gameObject->clean();

		delete gameObject;
		gameObject = NULL;
	}
	gameObjectsToDestroy.clear();

	//We add the objects that need to be add
	for (auto const& gameObject : gameObjectsToAdd) {

		if (gameObject.second == nullptr) {

			//We add the new game object in the Game itselft
			addGameObject(gameObject.first);
		}
		else {
			//We add the new game object as child of its new parent
			gameObject.second->addGameObjectAsChild(gameObject.first);
		}
	}
	gameObjectsToAdd.clear();


	for (GameObject* gameObject : gameObjects) {
		
		gameObject->update();
		
	}

	camera->update();

	
	//handle the deltatime
	timeLast = timeNow;
	timeNow = SDL_GetPerformanceCounter();
	Time::deltaTime = ((timeNow - timeLast) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001 * Time::timeScale;

	if (Time::deltaTime > 0.033f) {
		Time::deltaTime = 0.033f;
	}

	//printInConsole("delta time : " + std::to_string(Time::deltaTime));

}

void Game::render()
{
	renderer_manager->render();
}

void Game::clean()
{
	for (GameObject* gameObject : gameObjects) {
		gameObject->clean();
	}

	delete renderer_manager;
	delete collider_manager;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	TTF_Quit();

	SDL_Quit();

	printInConsole("Game closed!");
}

void Game::addGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}


void Game::instantiateGameObject(GameObject * gameObject, GameObject * new_parent)
{
	gameObjectsToAdd.insert(std::pair <GameObject*, GameObject*>(gameObject, new_parent));
}

void Game::destroyGameObject(GameObject * gameObject)
{
	gameObject->active = false;
	gameObject->setActiveChildren(false);

	gameObjectsToDestroy.push_back(gameObject);
}

GameObject* Game::findGameObject(std::string tag)
{

	for (GameObject* gameObject : gameObjects) {
		GameObject* object_found = Game::findGameObjectRecursive(tag, gameObject);
		if (object_found != nullptr) {
			
			return object_found;
		}

		object_found = NULL;
	}

	return nullptr;
}

bool Game::getIsRunning()
{
	return isRunning;
}

bool Game::getIsDebugMode()
{
	return isDebugMode;
}

SDL_Renderer * Game::getRenderer()
{
	return renderer;
}

RendererManager * Game::getRendererManager()
{
	return renderer_manager;
}

ColliderManager * Game::getColliderManager()
{
	return collider_manager;
}

SDL_Window* Game::getWindow()
{
	return window;
}

void Game::printInConsole(std::string str)
{
	if (getIsDebugMode()) {
		std::cout << str << std::endl;
	}
}

Camera* Game::getCamera()
{
	return camera;
}

OwnMathFuncs::Vector2 Game::getScreenSize()
{
	return screenSize;
}

GameObject * Game::findGameObjectRecursive(std::string tag, GameObject* gameObject)
{
	
	if (gameObject->tag == tag) {
		
		return gameObject;
	}

	for (GameObject* game_object_child : gameObject->getChildren()) {
		GameObject* object_found = Game::findGameObjectRecursive(tag, game_object_child);
		if (object_found != nullptr) {

			
			return object_found;
		}

		object_found = NULL;
	}

	return nullptr;
}


