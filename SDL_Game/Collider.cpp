#include "Collider.h"
#include "Game.h"


Collider::Collider(GameObject* game_object) : Component(game_object)
{
	Game::collider_manager->addCollider(this);
}


Collider::~Collider()
{
}
