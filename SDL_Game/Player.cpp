#include "Player.h"


Player::Player(std::string img_path, OwnMathFuncs::Vector2* sprite_size) :  GameObject()
{
	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, sprite_size);
	
	Animator* animator = new Animator(this);

	// Creation of Animations
	Animation animIdle;
	animIdle.nb_sprites = 5;
	animIdle.speed = 0.3f;
	animIdle.y_index = 0;

	animator->animations.insert(std::pair <std::string, Animation> ("Idle", animIdle));
	

	Animation animWalking;
	animWalking.nb_sprites = 5;
	animWalking.speed = 0.1f;
	animWalking.y_index = 2;

	animator->animations.insert(std::pair <std::string, Animation>("Walking", animWalking));
	animator->play("Idle");
	
	VelocityBody* velocityBody = new VelocityBody(this);
	
	BoxCollider* boxCollider = new BoxCollider(this);
	boxCollider->offset = { 1, 14};
	boxCollider->size = { 10, 5.5 };

	PlayerController* playerController = new PlayerController(this);
	PlayerStat* playerStat = new PlayerStat(this);

	local_scale = { 3, 3 };



	//Creation of child

	GameObject* game_object_child = new GameObject();

	BoxCollider* boxColliderHitBox = new BoxCollider(game_object_child);
	boxColliderHitBox->offset = { 0, 0 };
	boxColliderHitBox->size = { 10, 30 };
	boxColliderHitBox->collision_layer = 5;

	addGameObject(game_object_child);



	GameObject* game_object_child_2 = new GameObject();

	BoxCollider* boxColliderHitBoxAttack = new BoxCollider(game_object_child_2);
	boxColliderHitBoxAttack->offset = {15, 0 };
	boxColliderHitBoxAttack->size = { 15, 40};
	boxColliderHitBoxAttack->collision_layer = 5;

	PlayerAttack* player_attack = new PlayerAttack(game_object_child_2, boxColliderHitBoxAttack, playerController, velocityBody);

	addGameObject(game_object_child_2);
}


Player::~Player()
{
}
