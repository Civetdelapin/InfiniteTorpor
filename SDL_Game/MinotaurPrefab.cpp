#include "MinotaurPrefab.h"



MinotaurPrefab::MinotaurPrefab(OwnMathFuncs::Vector2 init_local_pos) : Enemy("img/minotaur.png", { 48, 48 }, init_local_pos)
{
	//---- MODIFICATION OF EXISTING COMPONENTS -----
	getComponent<VelocityBody>()->setDrag({ 10, 10 });

	EnemyBasicBehavior* enemyBasicBehavior = getComponent<EnemyBasicBehavior>();
	enemyBasicBehavior->setMaxHP(120);
	enemyBasicBehavior->setSpeed(1300);
	enemyBasicBehavior->setKnockBackResistance(0);
	enemyBasicBehavior->setScoreValue(85);
	enemyBasicBehavior->setTimeBeforeEnemy(12.0f);

	getComponent<DisplayEnemyHp>()->setYOffset(12);
	getComponent<SpriteRenderer>()->setIsLookingRight(false);

	localScale = { 4, 4 };

	BoxCollider* ground_collider = getComponent<BoxCollider>();
	ground_collider->offset = { -2, 22 };
	ground_collider->size = { 18, 6 };
	//----------------------------------------------


	//---------- CREATION OF CHILDREN --------------
	GameObject* game_object_child = new GameObject();
	game_object_child->tag = "Enemy";

	BoxCollider* boxColliderHitBox = new BoxCollider(game_object_child);
	boxColliderHitBox->offset = { -3, 8 };
	boxColliderHitBox->size = { 26, 30 };
	boxColliderHitBox->setCollisionLayer(5);
	addGameObjectAsChild(game_object_child);

	GameObject* game_object_child2 = new GameObject();
	game_object_child2->tag = "Enemy";

	BoxCollider* boxColliderAttack = new BoxCollider(game_object_child2);
	boxColliderAttack->offset = { 12, 8 };
	boxColliderAttack->size = { 24, 40 };
	boxColliderAttack->setCollisionLayer(10);
	boxColliderAttack->setActive(false);

	EnemyAttackCollider* enemy_attack_collider = new EnemyAttackCollider(game_object_child2, boxColliderAttack);
	addGameObjectAsChild(game_object_child2);
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
	animBeforeAttack.nbSprites = 5;
	animBeforeAttack.speed = 0.075f;
	animBeforeAttack.YIndex = 3;
	animBeforeAttack.looping = false;
	animator->addAnimation(std::pair <std::string, Animation>("BeforeAttack", animBeforeAttack));

	Animation animAttack;
	animAttack.nbSprites = 5;
	animAttack.speed = 0.05f;
	animAttack.YIndex = 3;
	animAttack.XIndex = 5;
	animAttack.looping = false;
	animator->addAnimation(std::pair <std::string, Animation>("Attack", animAttack));

	animator->play("Idle");
	//--------------------------------------------


	//----------- STATE MACHINE ------------------
	StateMachine * stateMachine = getComponent<StateMachine>();
	stateMachine->setDefaultState("RushPlayer");

	stateMachine->addState(std::pair <std::string, State*>("RushPlayer", new StateRushPlayer(this, 100, "MeleeAttack")));
	stateMachine->addState(std::pair <std::string, State*>("MeleeAttack", new StateMeleeAttack(this,"RushPlayer", 0.80f, 150)));

	stateMachine->play("RushPlayer");
	//-------------------------------------------
}


MinotaurPrefab::~MinotaurPrefab()
{

}
