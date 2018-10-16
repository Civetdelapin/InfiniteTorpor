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

		if (timeLeft >= animations[cur_animation].speed) {

			timeLeft = 0;

			cur_sprite++;

			if (!animations[cur_animation].is_looping && cur_sprite >= animations[cur_animation].nb_sprites) {
				
				for (Transition transi : animations[cur_animation].transitions) {

					if (transi.ready_when_animation_is_over) {
						cur_animation = transi.next_animation;
					}
				}
			}
			else {

				setRectRenderer();
			}
		}

		timeLeft += Time::deltaTime;
	}

}

void Animator::play(std::string name)
{
	if (cur_animation != name) {

		timeLeft = 0;
		cur_sprite = 0;

		if (animations.count(name) > 0) {
			cur_animation = name;

			timeLeft = animations[cur_animation].speed;
		}
		else {
			cur_animation = "";
			
		}
	}
}

void Animator::clean()
{
	animations.clear();
	spriteRenderer = NULL;

	Component::clean();
}

void Animator::setRectRenderer()
{
	cur_sprite = (cur_sprite % animations[cur_animation].nb_sprites);
	SDL_Rect tempRect;

	if (animations[cur_animation].is_reverse) {
		tempRect.x = (animations[cur_animation].nb_sprites - cur_sprite + animations[cur_animation].x_index) * spriteRenderer->getSpriteSize().x;
	}
	else {
		tempRect.x = (cur_sprite + animations[cur_animation].x_index) * spriteRenderer->getSpriteSize().x;
	}

	tempRect.y = animations[cur_animation].y_index * spriteRenderer->getSpriteSize().y;
	spriteRenderer->setSourceRect(tempRect);
}

