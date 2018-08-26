#include "Player.h"


Player::Player(std::string img_path, OwnMathFuncs::Vector2* sprite_size) :  GameObject()
{


	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, sprite_size);
	addComponent(spriteRenderer);
	
	Animator* animator = new Animator(this, spriteRenderer);


	// Creation of Animations
	Animation animIdle;
	animIdle.nb_sprites = 10;
	animIdle.speed = 0.1f;
	animIdle.y_index = 0;

	animator->animations.insert(std::pair <std::string, Animation> ("Idle", animIdle));
	addComponent(animator);


	Animation animWalking;
	animWalking.nb_sprites = 10;
	animWalking.speed = 0.1f;
	animWalking.y_index = 2;

	animator->animations.insert(std::pair <std::string, Animation>("Walking", animWalking));
	addComponent(animator);

	animator->play("Idle");
	
	VelocityBody* velocityBody = new VelocityBody(this);
	addComponent(velocityBody);

	PlayerController* playerController = new PlayerController(this, velocityBody, animator);
	addComponent(playerController);


	scale.x = 3;
	scale.y = 3;

	std::cout << "SPRITE RENDEDER PLAYER : " << spriteRenderer << std::endl;
	std::cout << "velocityBody PLAYER : " << velocityBody << std::endl;
}


Player::~Player()
{
}
