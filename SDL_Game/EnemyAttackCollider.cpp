#include "EnemyAttackCollider.h"
#include "Game.h"

EnemyAttackCollider::EnemyAttackCollider(GameObject* game_object, Collider* collider, bool isDestroyed) : Component(game_object), collider_to_check(collider), isDestroyed(isDestroyed)
{

}


EnemyAttackCollider::~EnemyAttackCollider()
{
}

void EnemyAttackCollider::update()
{

	if (collider_to_check != nullptr) {

		std::vector<Collider*> vect = Game::instance()->collider_manager->isTrigger(collider_to_check);
		if (vect.size() > 0) {

			for (Collider* collider : vect) {
				
					if (collider->getGameObject()->tag == "Player") {

						if (collider->getGameObject()->getRootParent()->getComponent<PlayerBehavior>()->addDamage(dmg) && isDestroyed) {
							Game::instance()->destroyGameObject(getGameObject());
						}

					}
			}
		}

	}
}

void EnemyAttackCollider::clean()
{
	collider_to_check = NULL;
	Component::clean();
}

Collider * EnemyAttackCollider::getDamageCollider()
{
	return collider_to_check;
}

