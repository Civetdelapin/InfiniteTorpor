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
	if (spriteRenderers.size() == 0) {
		SpriteRenderer* spriteRenderer = gameObject->getComponent<SpriteRenderer>();
		if (spriteRenderer != nullptr) {
			spriteRenderers.push_back(spriteRenderer);
		}		
	}
	
}

void Animator::update()
{

	if (animations[currentAnimation].spriteRendererIndex >= 0 && 
		animations[currentAnimation].spriteRendererIndex < spriteRenderers.size() 
		&& spriteRenderers[animations[currentAnimation].spriteRendererIndex] != nullptr
		&& currentAnimation != "") {

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

			if (currentAnimation != "" && animations[name].spriteRendererIndex != animations[currentAnimation].spriteRendererIndex) {
				spriteRenderers[animations[currentAnimation].spriteRendererIndex]->setActive(false);
				spriteRenderers[animations[name].spriteRendererIndex]->setActive(true);
			}
			else if (currentAnimation != "" && !spriteRenderers[animations[currentAnimation].spriteRendererIndex]->isActive()) {
				spriteRenderers[animations[currentAnimation].spriteRendererIndex]->setActive(true);
			}
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
	Component::clean();
}

void Animator::addSpriteRenderer(SpriteRenderer* spriteRenderer)
{
	spriteRenderers.push_back(spriteRenderer);
}

void Animator::setRectRenderer()
{
	currentSprite = (currentSprite % animations[currentAnimation].nbSprites);
	SDL_Rect tempRect;

	if (animations[currentAnimation].reverse) {
		tempRect.x = (animations[currentAnimation].nbSprites - currentSprite + animations[currentAnimation].indexX) * spriteRenderers[animations[currentAnimation].spriteRendererIndex]->getSpriteSize().x;
	}
	else {
		tempRect.x = (currentSprite + animations[currentAnimation].indexX) * spriteRenderers[animations[currentAnimation].spriteRendererIndex]->getSpriteSize().x;
	}

	tempRect.y = animations[currentAnimation].indexY * spriteRenderers[animations[currentAnimation].spriteRendererIndex]->getSpriteSize().y;
	spriteRenderers[animations[currentAnimation].spriteRendererIndex]->setSourceRect(tempRect);

	OwnMathFuncs::Vector2 offset = { (float)animations[currentAnimation].offsetX,
		(float)animations[currentAnimation].offsetY };
	spriteRenderers[animations[currentAnimation].spriteRendererIndex]->setOffset(offset);
}

