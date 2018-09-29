#pragma once
#include "Component.h"
#include "Collider.h"
#include "PlayerStat.h"

class EnemyAttackCollider : public Component
{

public:
	EnemyAttackCollider(GameObject* game_object, Collider* collider, bool isDestroyed = false);
	~EnemyAttackCollider();

	const float dmg = 1;

	void update();
	void clean();

	Collider* getDamageCollider();

private:
	Collider * collider_to_check = nullptr;

	bool isDestroyed = false;
};

