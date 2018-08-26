#include "BoxCollider.h"

BoxCollider::BoxCollider(GameObject* game_object) : Collider(game_object)
{

}


BoxCollider::~BoxCollider()
{
}

bool BoxCollider::isColliding(Collider * collider)
{

	if (BoxCollider* box_collider = dynamic_cast<BoxCollider*>(collider)) {

		update();
		collider->update();

		if (
			rect.x + rect.w >= box_collider->rect.x &&
			box_collider->rect.x + box_collider->rect.w >= rect.x &&
			rect.y + rect.h >= box_collider->rect.y &&
			box_collider->rect.y + box_collider->rect.h >= rect.y)
		{
			return true;
		}
		
		return false;
	}
	else if (true) {

	}

	return false;
}

void BoxCollider::update() {
	rect.x = game_object->position.x + (offset.x * game_object->scale.x) - ((size.x / 2) * abs(game_object->scale.x));
	rect.y = game_object->position.y + (offset.y * game_object->scale.y) - ((size.y / 2) * abs(game_object->scale.y));

	rect.h = size.y * abs(game_object->scale.y);
	rect.w = size.x * abs(game_object->scale.x);
}

void BoxCollider::render(float camera_pos_x, float camera_pos_y) {
	SDL_Rect rect_temp;
	rect_temp.x = rect.x - camera_pos_x;
	rect_temp.y = rect.y - camera_pos_y;

	rect_temp.h = rect.h;
	rect_temp.w = rect.w;


	TextureManager::DrawRect(rect_temp);
}