#include "EnemyAttackCollider.h"
#include "Game.h"

EnemyAttackCollider::EnemyAttackCollider(GameObject* game_object, Collider* collider) : Component(game_object), collider_to_check(collider)
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
				
					if (collider->game_object->tag == "Player") {
						collider->game_object->getRootParent()->getComponent<PlayerStat>()->addDamage(dmg);
					}
			}
		}

	}
}

