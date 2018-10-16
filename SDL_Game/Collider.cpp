#include "Collider.h"
#include "Game.h"


Collider::Collider(GameObject* gameObject, bool is_in_simulation) : Renderer(this), Component(gameObject)
{
	if (is_in_simulation) {
		Game::instance()->getColliderManager()->addCollider(this);
	}
}


Collider::~Collider()
{
}

bool Collider::AABB(SDL_Rect rectA, SDL_Rect rectB)
{
	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y)
	{
		return true;
	}

	return false;
}

bool Collider::isTrigger()
{
	return trigger;
}

void Collider::setIsTrigger(bool value)
{
	trigger = value;
}

void Collider::clean()
{
	Game::instance()->getColliderManager()->removeCollider(this);

	Renderer::clean();
	Component::clean();
}

int Collider::getCollisionLayer()
{
	return collisionLayer;
}

void Collider::setCollisionLayer(int value)
{
	collisionLayer = value;
}
