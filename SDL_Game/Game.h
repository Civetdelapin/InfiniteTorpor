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
#include "Map.h"
#include "Camera.h"
#include "ColliderManager.h"
#include "RendererManager.h"


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
		delete s_instance;
		s_instance = new_instance;
	}


	void handleEvents();
	void update();
	void render();
	void clean();

	
	void instantiateGameObject(GameObject* gameObject, GameObject* new_parent = nullptr);
	void destroyGameObject(GameObject* game_object);

	GameObject* findGameObject(std::string tag);

	bool getIsRunning();
	bool getIsDebugMode();

	RendererManager* getRendererManager();

	SDL_Window* getWindow();
	
	SDL_Event event;
	
	void printInConsole(std::string str);

	int getScreenWidth();
	int getScreenHeight();

	Camera* getCamera();
	
	SDL_Renderer *renderer;
	ColliderManager *collider_manager;

private:

	GameObject * findGameObjectRecursive(std::string tag, GameObject* game_object);

	void addGameObject(GameObject* gameObject);

	std::vector<GameObject*> game_objects;
	std::vector<GameObject*> game_objects_to_be_destroyed;

	std::map <GameObject*, GameObject*> game_objects_to_be_added;

	bool isDebugMode;
	bool isRunning;
	SDL_Window *window;

	int screen_width;
	int screen_height;

	Camera* camera;

	RendererManager* renderer_manager = new RendererManager();

	Uint64 timeNow = SDL_GetPerformanceCounter();
	Uint64 timeLast = 0;
};

#endif