#pragma once
#include "Component.h"
#include <map>
#include "SpriteRenderer.h"

struct Animation {
	float speed;
	int y_index;
	int nb_sprites;
};


class Animator : public Component
{
public:
	Animator(GameObject* game_object, SpriteRenderer * spriteRenderer);
	~Animator();

	std::map <std::string, Animation> animations;

	void update();
	void play(std::string name);

private:
	SpriteRenderer * spriteRenderer;
	std::string cur_animation = "";
	int cur_sprite = 0;

	float time_passed = 0;
};

