#pragma once
#include "Component.h"
#include "Collider.h"
#include "PlayerBehavior.h"

class EnemyAttackCollider : public Component
{

public:
	EnemyAttackCollider(GameObject* gameObject, Collider* collider, bool isDestroyed = false);
	~EnemyAttackCollider();

	const float dmg = 1;

	void update();
	void clean();

	Collider* getDamageCollider();

private:
	Collider * colliderToCheck = nullptr;

	bool isDestroyed = false;
};

