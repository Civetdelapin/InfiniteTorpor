#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "GameObject.h"
#include "TextureManager.h"
#include "OwnMathFuncs.h"
#include <algorithm>
#include "Time.h"
#include "Camera.h"
#include "ColliderManager.h"
#include "RendererManager.h"
#include "Room.h"
#include "ButtonManager.h"
#include "Color.h"
#include "DisplayGamePause.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
	Game(const char* title = "Untitled Game", int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, int width = 600, int height = 400, bool fullscreen = false, bool isDebugMode = true);
	~Game();


	static Game *s_instance;

	static Game *instance()
	{
		if (!s_instance)
			s_instance = new Game;
		return s_instance;
	}

	static void setInstance(Game* new_instance) {
		if (s_instance != nullptr) {
			s_instance->clean();
		}
		delete s_instance;
		s_instance = new_instance;
	}


	void handleEvents();
	void update();
	void render();
	void clean();

	
	void instantiateGameObject(GameObject* gameObject, GameObject* new_parent = nullptr);
	void destroyGameObject(GameObject* gameObject);

	GameObject* findGameObject(std::string tag);

	bool getIsRunning();
	bool getIsDebugMode();

	SDL_Renderer* getRenderer();

	RendererManager* getRendererManager();
	ColliderManager* getColliderManager();
	ButtonManager* getButtonManager();

	SDL_Window* getWindow();
	
	SDL_Event event;
	
	void printInConsole(std::string str);

	Camera* getCamera();
	
	OwnMathFuncs::Vector2 getScreenSize();

private:

	GameObject * findGameObjectRecursive(std::string tag, GameObject* gameObject);

	void addGameObject(GameObject* gameObject);

	std::vector<GameObject*> gameObjects;

	std::vector<GameObject*> gameObjectsToDestroy;

	std::map <GameObject*, GameObject*> gameObjectsToAdd;

	bool isDebugMode;
	bool isRunning;

	SDL_Window* window;
	SDL_Renderer* renderer;

	OwnMathFuncs::Vector2 screenSize;
	Camera* camera;

	RendererManager* rendererManager = new RendererManager();
	ColliderManager* colliderManager = new ColliderManager();
	ButtonManager* buttonManager = new ButtonManager();

	Uint64 timeNow = SDL_GetPerformanceCounter();
	Uint64 timeLast = 0;
};

#endif