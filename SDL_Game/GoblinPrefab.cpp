#include "GoblinPrefab.h"

GoblinPrefab::GoblinPrefab(OwnMathFuncs::Vector2 init_local_pos) : Enemy("img/goblin.png", { 32, 32 }, init_local_pos)
{

	getComponent<VelocityBody>()->setDrag({ 10, 10 });

	EnemyBasicBehavior* enemy_basic_behavior = getComponent<EnemyBasicBehavior>();
	enemy_basic_behavior-> setMaxHP(70);
	enemy_basic_behavior->setSpeed(2000);
	enemy_basic_behavior->setScoreValue(70);

	getComponent<DisplayEnemyHp>()->setYOffset(8);

	//Creation of child
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
	boxColliderAttack->setIsActive(false);

	EnemyAttackCollider* enemy_attack_collider = new EnemyAttackCollider(game_object_child2, boxColliderAttack);

	addGameObjectAsChild(game_object_child2);

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
	animWalking.y_index = 2;

	animator->addAnimation(std::pair <std::string, Animation>("Walking", animWalking));


	Animation animBeforeAttack;
	animBeforeAttack.nb_sprites = 5;
	animBeforeAttack.speed = 0.075f;
	animBeforeAttack.y_index = 3;
	animBeforeAttack.is_looping = false;

	animator->addAnimation(std::pair <std::string, Animation>("BeforeAttack", animBeforeAttack));

	Animation animAttack;
	animAttack.nb_sprites = 5;
	animAttack.speed = 0.05f;
	animAttack.y_index = 3;
	animAttack.x_index = 5;
	animAttack.is_looping = false;

	animator->addAnimation(std::pair <std::string, Animation>("Attack", animAttack));


	animator->play("Idle");

	//State Machine
	StateMachine * stateMachine = getComponent<StateMachine>();
	stateMachine->setDefaultState("RushPlayer");

	stateMachine->addState(std::pair <std::string, State*>("RushPlayer", new StateRushPlayer(this, 80, "MeleeAttack")));
	stateMachine->addState(std::pair <std::string, State*>("MeleeAttack", new StateMeleeAttack(this, "RushPlayer")));

	stateMachine->play("RushPlayer");
}


GoblinPrefab::~GoblinPrefab()
{
}
