#include "SnakePrefab.h"

SnakePrefab::SnakePrefab(OwnMathFuncs::Vector2 init_local_pos) : Enemy("img/snake.png", {32, 32}, init_local_pos)
{
	//---- MODIFICATION OF EXISTING COMPONENTS -----
	getComponent<VelocityBody>()->setDrag({ 13, 13 });

	EnemyBasicBehavior* enemyBasicBehavior = getComponent<EnemyBasicBehavior>();
	enemyBasicBehavior->setMaxHP(60);
	enemyBasicBehavior->setSpeed(1500);
	enemyBasicBehavior->setTimeBeforeEnemy(7.0f);

	getComponent<DisplayEnemyHp>()->setYOffset(8);
	getComponent<SpriteRenderer>()->setIsLookingRight(false);

	localScale = { 4, 4};

	BoxCollider* ground_collider = getComponent<BoxCollider>();
	//----------------------------------------------


	//---------- CREATION OF CHILDREN --------------
	GameObject* game_object_child = new GameObject();
	game_object_child->tag = "Enemy";

	BoxCollider* boxColliderHitBox = new BoxCollider(game_object_child);
	boxColliderHitBox->offset = { 0, 10 };
	boxColliderHitBox->size = { 12, 10 };
	boxColliderHitBox->setCollisionLayer(5);
	addGameObjectAsChild(game_object_child);

	GameObject* game_object_child2 = new GameObject();
	game_object_child2->tag = "Enemy";
	// -------------------------------------------


	//---------- CREATION OF ANIMATION -----------
	Animator* animator = getComponent<Animator>();

	Animation animIdle;
	animIdle.nbSprites = 10;
	animIdle.speed = 0.1f;
	animIdle.YIndex = 0;
	animator->addAnimation(std::pair <std::string, Animation>("Idle", animIdle));

	Animation animDying;
	animDying.nbSprites = 10;
	animDying.speed = 0.1f;
	animDying.YIndex = 4;
	animDying.looping = false;
	animator->addAnimation(std::pair <std::string, Animation>("Dying", animDying));

	Animation animWalking;
	animWalking.nbSprites = 10;
	animWalking.speed = 0.1f;
	animWalking.YIndex = 2;
	animator->addAnimation(std::pair <std::string, Animation>("Walking", animWalking));


	Animation animBeforeAttack;
	animBeforeAttack.nbSprites = 4;
	animBeforeAttack.speed = 0.1f;
	animBeforeAttack.YIndex = 3;
	animBeforeAttack.looping = false;
	animator->addAnimation(std::pair <std::string, Animation>("BeforeAttack", animBeforeAttack));

	Animation animAttack;
	animAttack.nbSprites = 6;
	animAttack.speed = 0.1f;
	animAttack.YIndex = 3;
	animAttack.XIndex = 4;
	animAttack.looping = false;
	animator->addAnimation(std::pair <std::string, Animation>("Attack", animAttack));

	animator->play("Idle");
	//--------------------------------------------


	//----------- STATE MACHINE ------------------
	StateMachine * stateMachine = getComponent<StateMachine>();
	stateMachine->setDefaultState("RushPlayer");

	stateMachine->addState(std::pair <std::string, State*>("RushPlayer", new StateRushPlayer(this, 200, "LaunchProjectile")));
	stateMachine->addState(std::pair <std::string, State*>("LaunchProjectile", new StateLaunchProjectile(this, "RushPlayer")));

	stateMachine->play("RushPlayer");
	//-------------------------------------------
}

SnakePrefab::~SnakePrefab()
{
}
