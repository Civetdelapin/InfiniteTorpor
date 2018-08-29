#include "Camera.h"

#include "Game.h"

const float Camera::scale = 3;
float Camera::camera_pos_x = 0;
float Camera::camera_pos_y = 0;

Camera::Camera(Game* game) : game(game)
{
}

Camera::Camera()
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
		camera_pos_x = objectToFollow->getWorldPosition().x - game->getScreenWidth() / 2;
		camera_pos_y = objectToFollow->getWorldPosition().y - game->getScreenHeight() / 2;
	}
	if (shake_x.is_shaking || shake_y.is_shaking) {

		float s_x = shake_x.amplitude() * _amplitude;
		float s_y = shake_y.amplitude() * _amplitude;

		camera_pos_x += s_x;
		camera_pos_y += s_y;
	}
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
