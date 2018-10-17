#pragma once
#include "Component.h"
#include <map>
#include "SpriteRenderer.h"

struct Transition {

	bool ready_when_animation_is_over = false;
	std::string next_animation = "";

};


struct Animation {
	float speed;

	int indexY = 0;
	int indexX = 0;

	int nbSprites;
	bool looping = true;

	bool reverse = false;

	std::vector<Transition> transitions;
};


class Animator : public Component
{
public:
	Animator(GameObject* gameObject);
	~Animator();

	void addAnimation(std::pair <std::string, Animation> animation);

	void start();
	void update();
	void play(std::string name);

	void clean();

private:
	SpriteRenderer * spriteRenderer;

	std::string currentAnimation = "";
	std::map <std::string, Animation> animations;

	int currentSprite = 0;

	float timeLeft = 0;

	void setRectRenderer();
};

