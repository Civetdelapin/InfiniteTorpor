#include "Collider.h"
#include "Game.h"


Collider::Collider(GameObject* game_object) : Component(game_object)
{
	Game::collider_manager->addCollider(this);
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
