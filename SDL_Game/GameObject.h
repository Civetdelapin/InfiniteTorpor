#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include "OwnMathFuncs.h"
#include <string>
#include <iostream>
#include "Time.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


// Base class for all the objects of the game
class GameObject
{

public:
	
	OwnMathFuncs::Vector2 position = {0, 0};
	OwnMathFuncs::Vector2 velocity = {0, 0};

	int img_sizeX = 30;
	int img_sizeY = 30;

	int sprite_sizeX = 30;
	int sprite_sizeY = 30;

	int layer = 0;

	explicit GameObject(SDL_Renderer* renderer);
	~GameObject();

	virtual void handleEvents();
	virtual void update();
	virtual void render();
	void clean();

	void setTexture(SDL_Texture* texture);

private:

	SDL_Texture* texture;
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	SDL_Renderer* renderer;

	
};

#endif
