#include "Animator.h"



Animator::Animator(GameObject* game_object): Component(game_object)
{
	spriteRenderer = game_object->getComponent<SpriteRenderer>();
}


Animator::~Animator()
{
}

void Animator::update()
{
	if (spriteRenderer != nullptr && cur_animation != "") {

		if (time_passed > animations[cur_animation].speed) {

			

			time_passed = 0;

			cur_sprite = (cur_sprite + 1) % animations[cur_animation].nb_sprites;

			

			spriteRenderer->srcrect.x = cur_sprite * spriteRenderer->sprite_sizeX;

			spriteRenderer->sprite_sizeX = 10;

			

			spriteRenderer->srcrect.y = animations[cur_animation].y_index;
		}

		time_passed += Time::deltaTime;
	}
}

void Animator::play(std::string name)
{
	cur_animation = name;
	time_passed = 0;
	cur_sprite = 0;
}

