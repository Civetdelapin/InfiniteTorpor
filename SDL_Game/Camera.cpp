#include "Camera.h"

Camera::Camera()
{


}

Camera::~Camera()
{
}

void Camera::update()
{

	if (objectToFollow != nullptr) {
		camera_pos_x = objectToFollow->position.x - (1366/2);
		camera_pos_y = objectToFollow->position.y - (768/2);
	}

}
