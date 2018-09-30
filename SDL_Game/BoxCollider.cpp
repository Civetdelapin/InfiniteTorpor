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

		if (Collider::AABB(rect, box_collider->rect)) {
			return true;
		}
		else {
			return false;
		}
	}
	

	return false;
}

SDL_Rect BoxCollider::getRect()
{
	return rect;
}

void BoxCollider::start()
{

}

void BoxCollider::update() {
	rect.x = game_object->getWorldPosition().x + (offset.x * game_object->getWorldScale().x) - ((size.x / 2) * abs(game_object->getWorldScale().x));
	rect.y = game_object->getWorldPosition().y + (offset.y * game_object->getWorldScale().y) - ((size.y / 2) * abs(game_object->getWorldScale().y));

	rect.h = size.y * abs(game_object->getWorldScale().y);
	rect.w = size.x * abs(game_object->getWorldScale().x);
}

void BoxCollider::render() {
	TextureManager::DrawRect(rect);
}