#include "SlimPrefab.h"



SlimPrefab::SlimPrefab(OwnMathFuncs::Vector2 init_local_pos) : Enemy("img/slimes.png", { 32, 32 }, init_local_pos)
{
	//---- MODIFICATION OF EXISTING COMPONENTS -----
	getComponent<VelocityBody>()->setDrag({ 13, 13 });

	EnemyBasicBehavior* enemyBasicBehavior = getComponent<EnemyBasicBehavior>();
	enemyBasicBehavior->setMaxHP(40);
	enemyBasicBehavior->setSpeed(500);
	enemyBasicBehavior->setScoreValue(70);
	enemyBasicBehavior->setTimeBeforeEnemy(6.0f);

	getComponent<SpriteRenderer>()->setIsLookingRight(false);
	//----------------------------------------------

	//Creation of children
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
	animIdle.nbSprites = 10;
	animIdle.speed = 0.1f;
	animIdle.indexY = 0;

	animator->addAnimation(std::pair <std::string, Animation>("Idle", animIdle));

	Animation animDying;
	animDying.nbSprites = 10;
	animDying.speed = 0.1f;
	animDying.indexY = 4;
	animDying.looping = false;

	animator->addAnimation(std::pair <std::string, Animation>("Dying", animDying));

	Animation animWalking;
	animWalking.nbSprites = 10;
	animWalking.speed = 0.1f;
	animWalking.indexY = 1;

	animator->addAnimation(std::pair <std::string, Animation>("Walking", animWalking));

	Animation animJump;
	animJump.nbSprites = 10;
	animJump.speed = 0.1f;
	animJump.indexY = 2;
	animJump.looping = false;

	animator->addAnimation(std::pair <std::string, Animation>("Jump", animJump));

	animator->play("Idle");

	//State Machine
	StateMachine * stateMachine = getComponent<StateMachine>();
	stateMachine->setDefaultState("OnlyWait");

	stateMachine->addState(std::pair <std::string, State*>("WalkRandomPos", new StateWalkRandomPos(this, 30, "OnlyWait")));
	stateMachine->addState(std::pair <std::string, State*>("OnlyWait", new StateOnlyWait(this, 1.25, "SlimAttack")));
	stateMachine->addState(std::pair <std::string, State*>("SlimAttack", new StateSlimAttack(this, 32, "WalkRandomPos")));

	stateMachine->play("OnlyWait");
}


SlimPrefab::~SlimPrefab()
{

}
