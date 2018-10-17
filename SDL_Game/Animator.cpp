#include "Animator.h"
#include "Game.h"

Animator::Animator(GameObject* gameObject): Component(gameObject)
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
	spriteRenderer = gameObject->getComponent<SpriteRenderer>();

}

void Animator::update()
{

	if (spriteRenderer != nullptr && currentAnimation != "") {

		if (timeLeft >= animations[currentAnimation].speed) {

			timeLeft = 0;

			currentSprite++;

			if (!animations[currentAnimation].looping && currentSprite >= animations[currentAnimation].nbSprites) {
				
				for (Transition transi : animations[currentAnimation].transitions) {

					if (transi.ready_when_animation_is_over) {
						currentAnimation = transi.next_animation;
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
	if (currentAnimation != name) {

		timeLeft = 0;
		currentSprite = 0;

		if (animations.count(name) > 0) {
			currentAnimation = name;

			timeLeft = animations[currentAnimation].speed;
		}
		else {
			currentAnimation = "";
			
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
	currentSprite = (currentSprite % animations[currentAnimation].nbSprites);
	SDL_Rect tempRect;

	if (animations[currentAnimation].reverse) {
		tempRect.x = (animations[currentAnimation].nbSprites - currentSprite + animations[currentAnimation].indexX) * spriteRenderer->getSpriteSize().x;
	}
	else {
		tempRect.x = (currentSprite + animations[currentAnimation].indexX) * spriteRenderer->getSpriteSize().x;
	}

	tempRect.y = animations[currentAnimation].indexY * spriteRenderer->getSpriteSize().y;
	spriteRenderer->setSourceRect(tempRect);
}

