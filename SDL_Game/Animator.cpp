#include "Animator.h"
#include "Game.h"

Animator::Animator(GameObject* game_object): Component(game_object)
{
	
}


Animator::~Animator()
{
}

void Animator::addAnimation(std::pair<std::string, Animation> animation)
{
	animations.insert(animation);
}

void Animator::start()
{
	spriteRenderer = game_object->getComponent<SpriteRenderer>();

}

void Animator::update()
{
	
	
	if (spriteRenderer != nullptr && cur_animation != "") {

		if (time_passed > animations[cur_animation].speed) {

			time_passed = 0;

			cur_sprite++;

			if (!animations[cur_animation].is_looping && cur_sprite >= animations[cur_animation].nb_sprites) {
				
				for (Transition transi : animations[cur_animation].transitions) {

					if (transi.ready_when_animation_is_over) {
						cur_animation = transi.next_animation;
					}
				}
			}
			else {
				cur_sprite = (cur_sprite % animations[cur_animation].nb_sprites);

				SDL_Rect tempRect;
				tempRect.x = (cur_sprite + animations[cur_animation].x_index) * spriteRenderer->getSpriteSize().x;
				tempRect.y = animations[cur_animation].y_index * spriteRenderer->getSpriteSize().y;

				spriteRenderer->setSourceRect(tempRect);
			}
		}

		time_passed += Time::deltaTime;
	}
	
	
}

void Animator::play(std::string name)
{
	if (cur_animation != name) {

		if (animations.count(name) > 0) {
			cur_animation = name;
		}
		else {
			cur_animation = "";
		}
		
		time_passed = 0;
		cur_sprite = 0;
	}
}

void Animator::clean()
{
	animations.clear();
	spriteRenderer = NULL;

	Component::clean();
}

