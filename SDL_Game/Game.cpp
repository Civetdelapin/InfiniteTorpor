#include "Game.h"

Game *Game::s_instance = 0;

Game::Game(const char * title, int xpos, int ypos, int width, int height, bool fullscreen, bool isDebugMode) : isDebugMode(isDebugMode), screen_width(width), screen_height(height)
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
	//handle the deltatime
	timeLast = timeNow;
	timeNow = SDL_GetPerformanceCounter();
	Time::deltaTime = (float)((timeNow - timeLast) * 1000 / (float)SDL_GetPerformanceFrequency()) * 0.001;
	

	//printInConsole("delta time : " + std::to_string(deltaTime));

	collider_manager->update();
	camera->update();

	for (GameObject* game_object : game_objects) {
		if (game_object->is_active) {
			game_object->update();
		}
	}

	//We add the objects that need to be add
	for (auto const& game_object : game_objects_to_be_added) {

		if (game_object.second == nullptr) {

			//We add the new game object in the Game itselft
			addGameObject(game_object.first);
		}
		else {
			//We add the new game object as child of its new parent
			game_object.second->addGameObjectAsChild(game_object.first);
		}
	}
	game_objects_to_be_added.clear();

	//We delete the objects that need to be deleted
	for (GameObject* game_object : game_objects_to_be_destroyed) {

		if (game_object->parent_game_object == nullptr) {
			game_objects.erase(std::remove(game_objects.begin(), game_objects.end(), game_object), game_objects.end());
		}
		else {
			game_object->parent_game_object->getChildren().erase(std::remove(game_object->parent_game_object->getChildren().begin(), game_object->parent_game_object->getChildren().end(), game_object), game_object->parent_game_object->getChildren().end());
		}
		

		//collider_manager->removeGameObjectColliders(game_object);

		game_object->clean();

		delete game_object;
		game_object = NULL;
	}
	game_objects_to_be_destroyed.clear();
}

void Game::render()
{
	renderer_manager->render();
}

void Game::clean()
{
	for (GameObject* game_object : game_objects) {
		game_object->clean();
	}

	delete renderer_manager;
	delete collider_manager;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	IMG_Quit();
	SDL_Quit();

	printInConsole("Game closed!");
}

void Game::addGameObject(GameObject* gameObject)
{
	game_objects.push_back(gameObject);
}

void Game::instantiateGameObject(GameObject * game_object, GameObject * new_parent)
{
	game_objects_to_be_added.insert(std::pair <GameObject*, GameObject*>(game_object, new_parent));
}

void Game::destroyGameObject(GameObject * game_object)
{
	game_object->is_active = false;
	game_object->setActiveChildren(false);

	game_objects_to_be_destroyed.push_back(game_object);
}

GameObject* Game::findGameObject(std::string tag)
{

	for (GameObject* game_object : game_objects) {
		GameObject* object_found = Game::findGameObjectRecursive(tag, game_object);
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

RendererManager * Game::getRendererManager()
{
	return renderer_manager;
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

int Game::getScreenWidth()
{
	return screen_width;
}

int Game::getScreenHeight()
{
	return screen_height;
}

Camera* Game::getCamera()
{
	return camera;
}

GameObject * Game::findGameObjectRecursive(std::string tag, GameObject* game_object)
{
	

	if (game_object->tag == tag) {
		
		return game_object;
	}

	for (GameObject* game_object_child : game_object->getChildren()) {
		GameObject* object_found = Game::findGameObjectRecursive(tag, game_object_child);
		if (object_found != nullptr) {

			
			return object_found;
		}

		object_found = NULL;
	}


	return nullptr;
}


