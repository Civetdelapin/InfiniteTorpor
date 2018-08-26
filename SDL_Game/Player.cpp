#include "Player.h"


Player::Player(std::string img_path, OwnMathFuncs::Vector2* sprite_size) :  GameObject()
{
	VelocityBody* velocityBody = new VelocityBody(this);
	
	//std::cout << velocityBody->drag.x << std::endl;

	addComponent(velocityBody);

	PlayerController* playerController = new PlayerController(this);
	addComponent(playerController);

	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, sprite_size);
	addComponent(spriteRenderer);
	/*
	Animator* animator = new Animator(this);

	// Creation of Animations
	Animation animIdle;
	animIdle.nb_sprites = 10;
	animIdle.speed = 0.5f;
	animIdle.y_index = 0;

	animator->animations.insert(std::pair <std::string, Animation> ("Idle", animIdle));
	addComponent(animator);


	animator->play("Idle");
	*/


	scale.x = 3;
	scale.y = 3;
}


Player::~Player()
{
}
