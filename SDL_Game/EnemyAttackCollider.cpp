#include "EnemyAttackCollider.h"
#include "Game.h"

EnemyAttackCollider::EnemyAttackCollider(GameObject* gameObject, Collider* collider, bool isDestroyed) : Component(gameObject), colliderToCheck(collider), isDestroyed(isDestroyed)
{

}


EnemyAttackCollider::~EnemyAttackCollider()
{
}

void EnemyAttackCollider::update()
{

	if (colliderToCheck != nullptr) {

		std::vector<Collider*> vect = Game::instance()->getColliderManager()->isTrigger(colliderToCheck);
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
	colliderToCheck = NULL;
	Component::clean();
}

Collider * EnemyAttackCollider::getDamageCollider()
{
	return colliderToCheck;
}

