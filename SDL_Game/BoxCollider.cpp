#include "BoxCollider.h"

BoxCollider::BoxCollider(GameObject* gameObject, bool is_in_simulation) : Collider(gameObject, is_in_simulation)
{
	setLayer(20);
}


BoxCollider::~BoxCollider()
{
}

bool BoxCollider::isColliding(Collider * collider)
{

	if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider)) {

		update();
		collider->update();

		if (OwnMathFuncs::OwnMathFuncs::AABB(rect, boxCollider->rect)) {
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
	rect.x = gameObject->getWorldPosition().x + (offset.x * gameObject->getWorldScale().x) - ((size.x / 2) * abs(gameObject->getWorldScale().x));
	rect.y = gameObject->getWorldPosition().y + (offset.y * gameObject->getWorldScale().y) - ((size.y / 2) * abs(gameObject->getWorldScale().y));

	rect.h = size.y * abs(gameObject->getWorldScale().y);
	rect.w = size.x * abs(gameObject->getWorldScale().x);
}

void BoxCollider::render() {
	//TextureManager::DrawRect(rect);
}