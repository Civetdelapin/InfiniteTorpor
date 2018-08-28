#pragma once
#include "GameObject.h"


#ifndef CAMERA_H
#define CAMERA_H_H

class Game;

class Camera
{
public:
	Camera(Game* game);
	~Camera();

	static float camera_pos_x;
	static float camera_pos_y;

	GameObject* objectToFollow;

	void update();

	const static float scale;

private:
	Game * game;
};

#endif

