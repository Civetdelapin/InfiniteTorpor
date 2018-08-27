#include "Player.h"


Player::Player(std::string img_path, OwnMathFuncs::Vector2* sprite_size) :  GameObject()
{


	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, sprite_size);
	addComponent(spriteRenderer);
	
	Animator* animator = new Animator(this);


	// Creation of Animations
	Animation animIdle;
	animIdle.nb_sprites = 5;
	animIdle.speed = 0.5f;
	animIdle.y_index = 0;

	animator->animations.insert(std::pair <std::string, Animation> ("Idle", animIdle));
	addComponent(animator);

	Animation animWalking;
	animWalking.nb_sprites = 5;
	animWalking.speed = 0.2f;
	animWalking.y_index = 2;

	animator->animations.insert(std::pair <std::string, Animation>("Walking", animWalking));
	addComponent(animator);

	animator->play("Idle");
	
	VelocityBody* velocityBody = new VelocityBody(this);
	addComponent(velocityBody);

	
	BoxCollider* boxCollider = new BoxCollider(this);
	boxCollider->offset = { 1, 14};
	boxCollider->size = { 10, 5.5 };

	addComponent(boxCollider);
	

	PlayerController* playerController = new PlayerController(this);
	addComponent(playerController);


	scale.x = 3;
	scale.y = 3;

}


Player::~Player()
{
}
