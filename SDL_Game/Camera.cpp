#include "Camera.h"

#include "Game.h"

const float Camera::scale = 3;
float Camera::camera_pos_x = 0;
float Camera::camera_pos_y = 0;

Camera::Camera(Game* game) : game(game)
{
}

Camera::~Camera()
{
}

void Camera::update()
{

	if (objectToFollow != nullptr) {
		camera_pos_x = objectToFollow->getWorldPosition().x - game->getScreenWidth() / 2;
		camera_pos_y = objectToFollow->getWorldPosition().y - game->getScreenHeight() / 2;
	}

}
