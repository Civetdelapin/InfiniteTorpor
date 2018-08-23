#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include <vector>
#include "GameObject.h"
#include "TextureManager.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
	Game(const char* title, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, int width = 600, int height = 400, bool fullscreen = false, bool isDebugMode = true);
	~Game();

	double deltaTime;

	std::vector<GameObject*> game_objects;

	void handleEvents();
	void update();
	void render();
	void clean();

	void addGameObject(GameObject* gameObject, std::string imgPath = "");

	bool getIsRunning();
	bool getIsDebugMode();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

	void printInConsole(std::string str);

private:

	bool isDebugMode;
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;


	Uint64 timeNow = SDL_GetPerformanceCounter();
	Uint64 timeLast = 0;
};

#endif