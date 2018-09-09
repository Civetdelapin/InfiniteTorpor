#pragma once
#include "Component.h"
#include "Collider.h"
#include "PlayerStat.h"

class EnemyAttackCollider : public Component
{

public:
	EnemyAttackCollider(GameObject* game_object, Collider* collider);
	~EnemyAttackCollider();

	const float dmg = 1;

	void update();

	Collider* collider_to_check = nullptr;

};

