#include "GoblinPrefab.h"

GoblinPrefab::GoblinPrefab(OwnMathFuncs::Vector2 init_local_pos) : Enemy("img/goblin.png", { 32, 32 }, init_local_pos)
{
	//---- MODIFICATION OF EXISTING COMPONENTS -----
	getComponent<VelocityBody>()->setDrag({ 10, 10 });

	EnemyBasicBehavior* enemyBasicBehavior = getComponent<EnemyBasicBehavior>();
	enemyBasicBehavior-> setMaxHP(70);
	enemyBasicBehavior->setSpeed(3100);
	enemyBasicBehavior->setScoreValue(70);
	enemyBasicBehavior->setTimeBeforeEnemy(8.5f);

	getComponent<DisplayEnemyHp>()->setYOffset(8);
	//----------------------------------------------


	//Creation of children
	GameObject* game_object_child = new GameObject();
	game_object_child->tag = "Enemy";

	BoxCollider* boxColliderHitBox = new BoxCollider(game_object_child);
	boxColliderHitBox->offset = { 0, 8 };
	boxColliderHitBox->size = { 12, 15 };
	boxColliderHitBox->setCollisionLayer(5);

	addGameObjectAsChild(game_object_child);


	GameObject* game_object_child2 = new GameObject();
	game_object_child2->tag = "Enemy";

	BoxCollider* boxColliderAttack = new BoxCollider(game_object_child2);
	boxColliderAttack->offset = { 12, 8 };
	boxColliderAttack->size = { 12, 22 };
	boxColliderAttack->setCollisionLayer(10);
	boxColliderAttack->setActive(false);

	EnemyAttackCollider* enemy_attack_collider = new EnemyAttackCollider(game_object_child2, boxColliderAttack);

	addGameObjectAsChild(game_object_child2);

	Animator* animator = getComponent<Animator>();

	// Creation of Animations
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

	//-----------STATES MACHINE ----------
	StateMachine * stateMachine = getComponent<StateMachine>();
	stateMachine->setDefaultState("RushPlayer");

	stateMachine->addState(std::pair <std::string, State*>("RushPlayer", new StateRushPlayer(this, 100, "MeleeAttack")));
	stateMachine->addState(std::pair <std::string, State*>("MeleeAttack", new StateMeleeAttack(this, "RushPlayer")));

	stateMachine->play("RushPlayer");
	//------------------------------------
}


GoblinPrefab::~GoblinPrefab()
{
}
