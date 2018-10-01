#include "MinotaurPrefab.h"



MinotaurPrefab::MinotaurPrefab(std::string img_path, OwnMathFuncs::Vector2 sprite_size, OwnMathFuncs::Vector2 init_local_pos) : Enemy(img_path, sprite_size, init_local_pos)
{
	//---- MODIFICATION OF EXISTING COMPONENTS -----
	getComponent<VelocityBody>()->setDrag({ 10, 10 });

	getComponent<EnemyBasicBehavior>()->setMaxHP(120);
	getComponent<EnemyBasicBehavior>()->setSpeed(1300);
	getComponent<EnemyBasicBehavior>()->setKnockBackResistance(0);

	getComponent<DisplayEnemyHp>()->setYOffset(12);
	getComponent<SpriteRenderer>()->setIsLookingRight(false);

	local_scale = { 4, 4 };

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
	boxColliderAttack->setIsActive(false);

	EnemyAttackCollider* enemy_attack_collider = new EnemyAttackCollider(game_object_child2, boxColliderAttack);
	addGameObjectAsChild(game_object_child2);
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
	//--------------------------------------------


	//----------- STATE MACHINE ------------------
	StateMachine * stateMachine = getComponent<StateMachine>();
	stateMachine->setDefaultState("RushPlayer");

	stateMachine->addState(std::pair <std::string, State*>("RushPlayer", new StateRushPlayer(this, 100, "MeleeAttack")));
	stateMachine->addState(std::pair <std::string, State*>("MeleeAttack", new StateMeleeAttack(this,"RushPlayer", 0.80f, 3000)));

	stateMachine->play("RushPlayer");
	//-------------------------------------------
}


MinotaurPrefab::~MinotaurPrefab()
{

}
