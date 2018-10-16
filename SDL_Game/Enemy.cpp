#include "Enemy.h"

Enemy::Enemy(std::string img_path, OwnMathFuncs::Vector2 sprite_size, OwnMathFuncs::Vector2 init_local_pos) : GameObject(init_local_pos)
{
	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, sprite_size);
	spriteRenderer->setLayer(5);

	BoxCollider* boxCollider = new BoxCollider(this);
	boxCollider->offset = { 0, 14 };
	boxCollider->size = { 10, 6 };
	boxCollider->setIsTrigger(true);

	tag = "Enemy";
	localScale = { 4, 4};

	VelocityBody* velocityBody = new VelocityBody(this);
	
	EnemyBasicBehavior* enemyState = new EnemyBasicBehavior(this);

	DisplayEnemyHp* displayEnemyHp = new DisplayEnemyHp(this, enemyState);
	displayEnemyHp->setLayer(10);

	Animator* animation = new Animator(this);

	StateMachine* stateMachine = new StateMachine(this);
	stateMachine->addState(std::pair <std::string, State*>("Stun", new StateStun(this)));
	stateMachine->addState(std::pair <std::string, State*>("Dying", new StateDying(this)));
}


Enemy::~Enemy()
{
}
