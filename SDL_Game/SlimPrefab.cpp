#include "SlimPrefab.h"



SlimPrefab::SlimPrefab(OwnMathFuncs::Vector2 init_local_pos) : Enemy("img/slimes.png", { 32, 32 }, init_local_pos)
{

	getComponent<VelocityBody>()->setDrag({ 13, 13 });

	EnemyBasicBehavior* enemy_basic_behavior = getComponent<EnemyBasicBehavior>();
	enemy_basic_behavior->setMaxHP(40);
	enemy_basic_behavior->setSpeed(500);
	enemy_basic_behavior->setScoreValue(70);

	getComponent<SpriteRenderer>()->setIsLookingRight(false);

	//Creation of child
	GameObject* game_object_child = new GameObject();

	BoxCollider* boxColliderHitBox = new BoxCollider(game_object_child);
	boxColliderHitBox->offset = { 0, 10 };
	boxColliderHitBox->size = { 12, 10 };
	boxColliderHitBox->setCollisionLayer(5);

	game_object_child->tag = "Enemy";
	addGameObjectAsChild(game_object_child);

	
	Animator* animator = getComponent<Animator>();
	
	// Creation of Animations
	Animation animIdle;
	animIdle.nb_sprites = 10;
	animIdle.speed = 0.1f;
	animIdle.y_index = 0;

	animator->addAnimation(std::pair <std::string, Animation>("Idle", animIdle));

	Animation animDying;
	animDying.nb_sprites = 10;
	animDying.speed = 0.1f;
	animDying.y_index = 4;
	animDying.is_looping = false;

	animator->addAnimation(std::pair <std::string, Animation>("Dying", animDying));

	Animation animWalking;
	animWalking.nb_sprites = 10;
	animWalking.speed = 0.1f;
	animWalking.y_index = 1;

	animator->addAnimation(std::pair <std::string, Animation>("Walking", animWalking));

	Animation animJump;
	animJump.nb_sprites = 10;
	animJump.speed = 0.1f;
	animJump.y_index = 2;
	animJump.is_looping = false;

	animator->addAnimation(std::pair <std::string, Animation>("Jump", animJump));

	animator->play("Idle");

	//State Machine
	StateMachine * stateMachine = getComponent<StateMachine>();
	stateMachine->setDefaultState("OnlyWait");

	stateMachine->addState(std::pair <std::string, State*>("WalkRandomPos", new StateWalkRandomPos(this, 30, "OnlyWait")));
	stateMachine->addState(std::pair <std::string, State*>("OnlyWait", new StateOnlyWait(this, 1.25, "SlimAttack")));
	stateMachine->addState(std::pair <std::string, State*>("SlimAttack", new StateSlimAttack(this, 52, "WalkRandomPos")));

	stateMachine->play("OnlyWait");
}


SlimPrefab::~SlimPrefab()
{
}
