#pragma once
#include "GameObject.h"




class Game;

struct Shake {

	bool is_shaking = false;

	std::vector<float> samples;

	Shake(float frequency, float duration);

	Shake();

	float amplitude();
	float decay(float time);
	float noise(int index);
	float t = 0;
	float _frequency = 20;

	float _duration = 0;

	void update();
};

class Camera
{
public:
	Camera(Game* game);
	~Camera();

	void update();

	OwnMathFuncs::Vector2 getCameraPos();
	void setObjectToFollow(GameObject* game_object);
	void startShake(float ampli, float frequency, float duration);

private:
	Game * game;

	OwnMathFuncs::Vector2 camera_pos = { 0, 0 };
	GameObject* objectToFollow;


	float _amplitude = 2000;
	Shake shake_x;
	Shake shake_y;
};

