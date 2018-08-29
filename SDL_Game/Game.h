#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include <vector>
#include "GameObject.h"
#include "TextureManager.h"
#include "OwnMathFuncs.h"
#include <algorithm>
#include "Time.h"
#include "Map.h"
#include "Camera.h"
#include "ColliderManager.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
	Game(const char* title, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, int width = 600, int height = 400, bool fullscreen = false, bool isDebugMode = true);
	~Game();

	std::vector<GameObject*> game_objects;

	void handleEvents();
	void update();
	void render();
	void clean();

	void addGameObject(GameObject* gameObject);

	bool getIsRunning();
	bool getIsDebugMode();

	SDL_Window* getWindow();
	
	static SDL_Event event;
	
	void printInConsole(std::string str);

	int getScreenWidth();
	int getScreenHeight();
	Camera* getCamera();
	
	static Camera* camera;

	static SDL_Renderer *renderer;
	static ColliderManager * collider_manager;

private:
	bool isDebugMode;
	bool isRunning;
	SDL_Window *window;

	int screen_width;
	int screen_height;

	Uint64 timeNow = SDL_GetPerformanceCounter();
	Uint64 timeLast = 0;
};

#endif