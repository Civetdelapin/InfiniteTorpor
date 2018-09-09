#include "GoblinPrefab.h"

GoblinPrefab::GoblinPrefab(std::string img_path, OwnMathFuncs::Vector2* sprite_size) : Enemy(img_path, sprite_size)
{

	getComponent<VelocityBody>()->drag = { 10, 10 };
	getComponent<EnemyBasicBehavior>()->max_hp = 70;
	getComponent<EnemyBasicBehavior>()->speed = 2000;
	getComponent<DisplayEnemyHp>()->y_offset = 8;


	//Creation of child
	GameObject* game_object_child = new GameObject();

	BoxCollider* boxColliderHitBox = new BoxCollider(game_object_child);
	boxColliderHitBox->offset = { 0, 8 };
	boxColliderHitBox->size = { 12, 15 };
	boxColliderHitBox->collision_layer = 5;

	

	game_object_child->tag = "Enemy";

	addGameObject(game_object_child);


	GameObject* game_object_child2 = new GameObject();
	BoxCollider* boxColliderAttack = new BoxCollider(game_object_child2);
	boxColliderAttack->offset = { 12, 8 };
	boxColliderAttack->size = { 12, 15 };
	boxColliderAttack->collision_layer = 10;

	boxColliderAttack->is_active = false;

	EnemyAttackCollider* enemy_attack_collider = new EnemyAttackCollider(game_object_child2, boxColliderAttack);

	addGameObject(game_object_child2);

	Animator* animator = new Animator(this);

	// Creation of Animations
	Animation animIdle;
	animIdle.nb_sprites = 10;
	animIdle.speed = 0.1f;
	animIdle.y_index = 0;

	animator->animations.insert(std::pair <std::string, Animation>("Idle", animIdle));

	Animation animWalking;
	animWalking.nb_sprites = 10;
	animWalking.speed = 0.1f;
	animWalking.y_index = 2;

	animator->animations.insert(std::pair <std::string, Animation>("Walking", animWalking));


	Animation animBeforeAttack;
	animBeforeAttack.nb_sprites = 5;
	animBeforeAttack.speed = 0.075f;
	animBeforeAttack.y_index = 3;
	animBeforeAttack.is_looping = false;

	animator->animations.insert(std::pair <std::string, Animation>("BeforeAttack", animBeforeAttack));

	Animation animAttack;
	animAttack.nb_sprites = 5;
	animAttack.speed = 0.05f;
	animAttack.y_index = 3;
	animAttack.x_index = 5;
	animAttack.is_looping = false;

	animator->animations.insert(std::pair <std::string, Animation>("Attack", animAttack));


	animator->play("Idle");

	//Set the current State
	getComponent<StateMachine>()->setSet(new StateRushPlayer(this));
}


GoblinPrefab::~GoblinPrefab()
{
}
