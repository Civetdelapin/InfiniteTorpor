#include "SlimProjectilePrefab.h"



SlimProjectilePrefab::SlimProjectilePrefab(OwnMathFuncs::Vector2 init_local_pos) : GameObject(init_local_pos)
{
	local_scale = { 3, 3 };
	tag = "Enemy";
	layer = 4;

	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, "img/slim_projectile.png", { 32, 32 });

	BoxCollider* boxCollider = new BoxCollider(this);
	boxCollider->size = { 5, 5 };
	boxCollider->setIsTrigger(true);

	ProjectileBehavior* protectileBehavior = new ProjectileBehavior(this, 500, boxCollider);


	BoxCollider* boxColliderAttack = new BoxCollider(this);
	boxColliderAttack->size = { 5, 5 };
	boxColliderAttack->setIsTrigger(true);
	boxColliderAttack->setCollisionLayer(10);

	EnemyAttackCollider* enemyAttackCollider = new EnemyAttackCollider(this, boxColliderAttack);
}


SlimProjectilePrefab::~SlimProjectilePrefab()
{
}
