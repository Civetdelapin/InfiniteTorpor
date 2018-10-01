#include "SnakePrefab.h"

SnakePrefab::SnakePrefab(OwnMathFuncs::Vector2 init_local_pos) : Enemy("img/snake.png", {32, 32}, init_local_pos)
{
	//---- MODIFICATION OF EXISTING COMPONENTS -----
	getComponent<VelocityBody>()->setDrag({ 13, 13 });

	getComponent<EnemyBasicBehavior>()->setMaxHP(60);
	getComponent<EnemyBasicBehavior>()->setSpeed(1500);

	getComponent<DisplayEnemyHp>()->setYOffset(8);
	getComponent<SpriteRenderer>()->setIsLookingRight(false);

	local_scale = { 3, 3 };

	BoxCollider* ground_collider = getComponent<BoxCollider>();
	//ground_collider->offset = { -2, 22 };
	//ground_collider->size = { 18, 6 };
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
	animWalking.y_index = 2;
	animator->addAnimation(std::pair <std::string, Animation>("Walking", animWalking));

	Animation animAttack;
	animAttack.nb_sprites = 5;
	animAttack.speed = 0.05f;
	animAttack.y_index = 3;
	animAttack.x_index = 5;
	animAttack.is_looping = false;
	animator->addAnimation(std::pair <std::string, Animation>("Attack", animAttack));

	animator->play("Idle");
	//--------------------------------------------


	//----------- STATE MACHINE ------------------
	StateMachine * stateMachine = getComponent<StateMachine>();
	stateMachine->setDefaultState("RushPlayer");

	stateMachine->addState(std::pair <std::string, State*>("RushPlayer", new StateRushPlayer(this, 100, "RushPlayer")));
	//stateMachine->addState(std::pair <std::string, State*>("MeleeAttack", new StateMeleeAttack(this, "RushPlayer", 0.80f, 3000)));

	stateMachine->play("RushPlayer");
	//-------------------------------------------
}

SnakePrefab::~SnakePrefab()
{
}
