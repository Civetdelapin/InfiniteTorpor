#include "Collider.h"
#include "Game.h"


Collider::Collider(GameObject* game_object) : Renderer(this), Component(game_object)
{
	Game::instance()->collider_manager->addCollider(this);
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
	return is_trigger;
}

void Collider::setIsTrigger(bool value)
{
	is_trigger = value;
}

void Collider::clean()
{
	Game::instance()->collider_manager->removeCollider(this);

	Renderer::clean();
	Component::clean();
}

int Collider::getCollisionLayer()
{
	return collision_layer;
}

void Collider::setCollisionLayer(int value)
{
	collision_layer = value;
}
