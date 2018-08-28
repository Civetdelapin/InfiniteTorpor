#include "Game.h"

SDL_Event Game::event;
SDL_Renderer* Game::renderer;
ColliderManager* Game::collider_manager = new ColliderManager();

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

		

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	camera = new Camera(this);
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
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	
	//drawLevels();

	for (GameObject* game_object : game_objects) {

		if (game_object->is_active) {
			game_object->render();
		}
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	for (GameObject* game_object : game_objects) {
		game_object->clean();
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	IMG_Quit();
	SDL_Quit();

	printInConsole("Game closed!");
}

void Game::addGameObject(GameObject * game_object)
{
	game_objects.push_back(game_object);
	std::sort(game_objects.begin(), game_objects.end(), [](GameObject* a, GameObject* b) {
		return a->layer < b->layer;
	});
}

bool Game::getIsRunning()
{
	return isRunning;
}

bool Game::getIsDebugMode()
{
	return isDebugMode;
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

