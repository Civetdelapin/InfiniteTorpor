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
	shake_x.update();
	shake_y.update();

	if (objectToFollow != nullptr) {
		if (shake_x.is_shaking || shake_y.is_shaking) {
			camera_pos = { objectToFollow->getWorldPosition().x - game->getScreenWidth() / 2 , objectToFollow->getWorldPosition().y - game->getScreenHeight() / 2 };
		}
		else {
			camera_pos = OwnMathFuncs::OwnMathFuncs::Lerp(camera_pos,
				{ objectToFollow->getWorldPosition().x - game->getScreenWidth() / 2 , objectToFollow->getWorldPosition().y - game->getScreenHeight() / 2 },
				Time::deltaTime * follow_speed);
		}
	}

	if (shake_x.is_shaking || shake_y.is_shaking) {

		float s_x = shake_x.amplitude() * _amplitude;
		float s_y = shake_y.amplitude() * _amplitude;

		camera_pos.x += s_x;
		camera_pos.y += s_y;
	}
}

OwnMathFuncs::Vector2 Camera::getCameraPos()
{
	return camera_pos;
}

void Camera::setObjectToFollow(GameObject* game_object)
{
	objectToFollow = game_object;
}

void Camera::startShake(float ampli, float frequency, float duration)
{
	shake_x = Shake(frequency, duration);
	shake_y = Shake(frequency, duration);

	_amplitude = ampli;
}



float Shake::amplitude()
{
	float s = t * _frequency;
	int s0 = floor(s);
	int s1 = s0 + 1;

	float k = decay(t);

	return (noise(s0) + (s - s0) * (noise(s1) - noise(s0))) * k;
}

void Shake::update()
{
	if (is_shaking) {

		t += Time::deltaTime;
		if (t > _duration) {
			is_shaking = false;
		}
	}
}

float Shake::decay(float time)
{

	if (time >= _duration) {
		return 0;
	}

	return (_duration - time) / _duration;
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
	_duration = duration;
	_frequency = frequency;

	t = 0;

	is_shaking = true;

	int sampleCount = (duration * frequency);

	for (int i = 0; i < sampleCount; i++) {
		samples.push_back(2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f);
	}
}

Shake::Shake()
{
}
