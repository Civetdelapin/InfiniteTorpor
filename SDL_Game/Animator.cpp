#include "Animator.h"



Animator::Animator(GameObject* game_object, SpriteRenderer* spriteRenderer): Component(game_object), spriteRenderer(spriteRenderer)
{
	//spriteRenderer = &game_object->getComponent<SpriteRenderer>();

	std::cout << "SPRITERENDERER ANIMATOR ADRESSE : " << spriteRenderer << std::endl;
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
			spriteRenderer->srcrect.y = animations[cur_animation].y_index * spriteRenderer->sprite_sizeY;
		}

		time_passed += Time::deltaTime;
	}
	
}

void Animator::play(std::string name)
{
	if (cur_animation != name) {
		cur_animation = name;
		time_passed = 0;
		cur_sprite = 0;
	}
}

