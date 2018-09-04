#include "Enemy.h"

Enemy::Enemy(std::string img_path, OwnMathFuncs::Vector2* sprite_size) : GameObject()
{
	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, sprite_size);

	BoxCollider* boxCollider = new BoxCollider(this);
	boxCollider->offset = { 0, 14 };
	boxCollider->size = { 10, 6 };
	boxCollider->is_trigger = true;

	tag = "Enemy";
	local_scale = { 3, 3 };

	VelocityBody* velocityBody = new VelocityBody(this);
	
	EnemyStat* enemyState = new EnemyStat(this);


	DisplayEnemyHp* displayEnemyHp = new DisplayEnemyHp(this, enemyState);

	StateMachine* stateMachine = new StateMachine(this);
}


Enemy::~Enemy()
{
}
