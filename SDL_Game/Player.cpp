#include "Player.h"


Player::Player(std::string img_path, OwnMathFuncs::Vector2 sprite_size, OwnMathFuncs::Vector2 init_local_pos) :  GameObject(init_local_pos)
{
	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, sprite_size);
	spriteRenderer->setLayer(5);

	Animator* animator = new Animator(this);

	// Creation of Animations
	Animation animIdle;
	animIdle.nb_sprites = 5;
	animIdle.speed = 0.3f;
	animIdle.y_index = 0;

	animator->addAnimation(std::pair <std::string, Animation> ("Idle", animIdle));
	

	Animation animWalking;
	animWalking.nb_sprites = 5;
	animWalking.speed = 0.1f;
	animWalking.y_index = 2;

	animator->addAnimation(std::pair <std::string, Animation>("Walking", animWalking));
	animator->play("Idle");
	

	BoxCollider* boxCollider = new BoxCollider(this);
	boxCollider->offset = { 1, 14};
	boxCollider->size = { 10, 5.5 };

	VelocityBody* velocityBody = new VelocityBody(this);
	velocityBody->setDrag({ 20, 20 });

	PlayerController* playerController = new PlayerController(this);
	PlayerStat* playerStat = new PlayerStat(this);

	local_scale = { 3, 3 };
	tag = "Player";

	//Creation of child
	GameObject* game_object_child = new GameObject();

	BoxCollider* boxColliderHitBox = new BoxCollider(game_object_child);
	boxColliderHitBox->offset = { 0, 4 };
	boxColliderHitBox->size = { 10, 22 };
	boxColliderHitBox->setCollisionLayer(10);

	game_object_child->tag = "Player";
	addGameObjectAsChild(game_object_child);

	GameObject* game_object_child_2 = new GameObject();

	BoxCollider* boxColliderHitBoxAttack = new BoxCollider(game_object_child_2);
	boxColliderHitBoxAttack->offset = {12, 0 };
	boxColliderHitBoxAttack->size = { 26, 40};
	boxColliderHitBoxAttack->setCollisionLayer(5);

	BoxCollider* boxColliderHitBoxAttackUpDown = new BoxCollider(game_object_child_2);
	boxColliderHitBoxAttackUpDown->offset = { 0, -16 };
	boxColliderHitBoxAttackUpDown->size = { 40, 26 };
	boxColliderHitBoxAttackUpDown->setCollisionLayer(5);


	BoxCollider* boxColliderHitBoxAttackCorner1 = new BoxCollider(game_object_child_2);
	boxColliderHitBoxAttackCorner1->offset = { 12, -13 };
	boxColliderHitBoxAttackCorner1->size = { 28, 28 };
	boxColliderHitBoxAttackCorner1->setCollisionLayer(5);


	PlayerAttack* player_attack = new PlayerAttack(game_object_child_2, boxColliderHitBoxAttack, boxColliderHitBoxAttackUpDown, boxColliderHitBoxAttackCorner1 ,playerController, velocityBody);

	game_object_child_2->tag = "Player";
	addGameObjectAsChild(game_object_child_2);
}


Player::~Player()
{
}
