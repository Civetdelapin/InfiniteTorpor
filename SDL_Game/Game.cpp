#include "Game.h"

SDL_Event Game::event;

Game::Game(const char * title, int xpos, int ypos, int width, int height, bool fullscreen, bool isDebugMode) : isDebugMode(isDebugMode)
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
	Time::deltaTime = (float)((timeNow - timeLast) * 1000 / (float)SDL_GetPerformanceFrequency());

	//printInConsole("delta time : " + std::to_string(deltaTime));

	for (GameObject* game_object : game_objects) {
		game_object->update();
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
	SDL_RenderClear(renderer);

	for (GameObject* game_object : game_objects) {
		game_object->render();

		SDL_RenderPresent(renderer);
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

void Game::addGameObject(GameObject * game_object, std::string img_path, OwnMathFuncs::Vector2* sprite_size)
{
	if (img_path != "") {
	
		game_object->setTexture(TextureManager::LoadTexture(img_path.c_str(), renderer,game_object->img_sizeX, game_object->img_sizeY));

		if (sprite_size == nullptr) {
			game_object->sprite_sizeX = game_object->img_sizeX;
			game_object->sprite_sizeY = game_object->img_sizeY;
		}
		else {
			game_object->sprite_sizeX = sprite_size->x;
			game_object->sprite_sizeY = sprite_size->y;
		}
	}

	game_objects.push_back(game_object);
	std::sort(game_objects.begin(), game_objects.end(), [](GameObject* a, GameObject* b) {
		return a->layer > b->layer;
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

SDL_Renderer * Game::getRenderer()
{
	return renderer;
}

void Game::printInConsole(std::string str)
{
	if (getIsDebugMode()) {
		std::cout << str << std::endl;
	}
}
