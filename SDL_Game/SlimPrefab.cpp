#include "SlimPrefab.h"



SlimPrefab::SlimPrefab(std::string img_path, OwnMathFuncs::Vector2* sprite_size) : Enemy(img_path, sprite_size)
{

	getComponent<VelocityBody>()->drag = { 13, 13 };


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
	animator->play("Idle");

}


SlimPrefab::~SlimPrefab()
{
}
