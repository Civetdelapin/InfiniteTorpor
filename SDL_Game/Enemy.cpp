#include "Enemy.h"

Enemy::Enemy(std::string img_path, OwnMathFuncs::Vector2 spriteSize, OwnMathFuncs::Vector2 init_local_pos) : GameObject(init_local_pos)
{
	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, spriteSize);
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
	displayEnemyHp->setLayer(RendererManager::MAX_LAYER);

	Animator* animation = new Animator(this);

	StateMachine* stateMachine = new StateMachine(this);
	stateMachine->addState(std::pair <std::string, State*>("Stun", new StateStun(this)));
	stateMachine->addState(std::pair <std::string, State*>("Dying", new StateDying(this)));


	GameObject* game_object_child_3 = new GameObject({ 0, spriteRenderer->getSpriteSize().y / 2 });
	SpriteRenderer* sprite_renderer_2 = new SpriteRenderer(game_object_child_3, "img/shadow_small.png", { 21, 21 });
	sprite_renderer_2->setLayer(RendererManager::TOP_DOWN_LAYER - 1);

	addGameObjectAsChild(game_object_child_3);
}


Enemy::~Enemy()
{
}
