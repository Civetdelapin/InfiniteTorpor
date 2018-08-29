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
	Camera();
	~Camera();

	static float camera_pos_x;
	static float camera_pos_y;

	GameObject* objectToFollow;

	void update();

	const static float scale;

	void startShake(float ampli, float frequency, float duration);

private:
	Game * game;
	
	float _amplitude = 2000;

	Shake shake_x;
	Shake shake_y;
};

