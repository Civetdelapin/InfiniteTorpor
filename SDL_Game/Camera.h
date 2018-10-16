#pragma once
#include "GameObject.h"


class Game;

struct Shake {

	bool shaking = false;

	std::vector<float> samples;

	Shake(float frequency, float duration);

	Shake();

	float amplitude();
	float decay(float time);
	float noise(int index);
	float t = 0;
	float frequency = 20;

	float duration = 0;

	void update();
};

class Camera
{
public:
	Camera(Game* game);
	~Camera();

	void update();

	OwnMathFuncs::Vector2 getCameraPos();
	void setCameraPos(OwnMathFuncs::Vector2 pos);
	void setObjectToFollow(GameObject* gameObject);


	void startShake(float ampli, float frequency, float duration);

private:
	Game * game;

	OwnMathFuncs::Vector2 cameraPosition = { 0, 0 };
	GameObject* objectToFollow;

	float followSpeed = 5;

	float amplitude = 2000;
	Shake shakeX;
	Shake shakeY;

	GameObject* nextObjectToFollow = nullptr;
};

