#include "Camera.h"

#include "Game.h"


Camera::Camera(Game* game) : game(game)
{
}


Camera::~Camera()
{
}

void Camera::update()
{
	shakeX.update();
	shakeY.update();

	if (objectToFollow != nullptr) {
		if (shakeX.shaking || shakeY.shaking) {
			cameraPosition = { objectToFollow->getWorldPosition().x - game->getScreenSize().x / 2 , objectToFollow->getWorldPosition().y - game->getScreenSize().y / 2 };
		}
		else {
			cameraPosition = OwnMathFuncs::OwnMathFuncs::Lerp(cameraPosition,
				{ objectToFollow->getWorldPosition().x - game->getScreenSize().x / 2 , objectToFollow->getWorldPosition().y - game->getScreenSize().y / 2 },
				Time::deltaTime * followSpeed);
		}
	}

	if (shakeX.shaking || shakeY.shaking) {

		float s_x = shakeX.amplitude() * amplitude;
		float s_y = shakeY.amplitude() * amplitude;

		cameraPosition.x += s_x;
		cameraPosition.y += s_y;
	}
	else {
		if (nextObjectToFollow != nullptr) {
			objectToFollow = nextObjectToFollow;
			nextObjectToFollow = nullptr;
		}
	}
}

OwnMathFuncs::Vector2 Camera::getCameraPos()
{
	return cameraPosition;
}

void Camera::setCameraPos(OwnMathFuncs::Vector2 pos)
{
	cameraPosition = { pos.x - game->getScreenSize().x / 2 , pos.y - game->getScreenSize().y / 2 };
}

void Camera::setObjectToFollow(GameObject* gameObject)
{
	if (shakeX.shaking || shakeY.shaking) {
	
		nextObjectToFollow = gameObject;
		
	}
	else {
		objectToFollow = gameObject;
	}

}

void Camera::startShake(float ampli, float frequency, float duration)
{
	shakeX = Shake(frequency, duration);
	shakeY = Shake(frequency, duration);

	amplitude = ampli;
}



float Shake::amplitude()
{
	float s = t * frequency;
	int s0 = floor(s);
	int s1 = s0 + 1;

	float k = decay(t);

	return (noise(s0) + (s - s0) * (noise(s1) - noise(s0))) * k;
}

void Shake::update()
{
	if (shaking) {

		t += Time::deltaTime;
		if (t > duration) {
			shaking = false;
		}
	}
}

float Shake::decay(float time)
{

	if (time >= duration) {
		return 0;
	}

	return (duration - time) / duration;
}

float Shake::noise(int index)
{
	if (index >= 0 && index < samples.size()) {
		return samples.at(index);
	}
	else {
		return 0;
	}	
}

Shake::Shake(float frequency, float duration)
{
	duration = duration;
	frequency = frequency;

	t = 0;

	shaking = true;

	int sampleCount = (duration * frequency);

	for (int i = 0; i < sampleCount; i++) {
		samples.push_back(2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f);
	}
}

Shake::Shake()
{
}
