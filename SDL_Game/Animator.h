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

	int y_index = 0;
	int x_index = 0;

	int nb_sprites;
	bool is_looping = true;

	std::vector<Transition> transitions;
};


class Animator : public Component
{
public:
	Animator(GameObject* game_object);
	~Animator();

	void addAnimation(std::pair <std::string, Animation> animation);

	void start();
	void update();
	void play(std::string name);

	void clean();

private:
	SpriteRenderer * spriteRenderer;

	std::string cur_animation = "";
	std::map <std::string, Animation> animations;

	int cur_sprite = 0;

	float time_passed = 0;
};

