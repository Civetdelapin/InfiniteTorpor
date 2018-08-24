#pragma once
#include "GameObject.h"

#ifndef CAMERA_H
#define CAMERA_H_H

class Camera
{
public:
	Camera();
	~Camera();

	float camera_pos_x;
	float camera_pos_y;

	GameObject* objectToFollow;

	void update();
};

#endif

