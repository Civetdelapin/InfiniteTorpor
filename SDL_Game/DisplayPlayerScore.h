#pragma once
#include "Renderer.h"
#include "PlayerBehavior.h"
#include "Component.h"

class DisplayPlayerScore : public Renderer, public Component
{
public:
	DisplayPlayerScore(GameObject* game_object);
	~DisplayPlayerScore();

	void start();
	void update();
	void render();

	void clean();

private:
	PlayerBehavior * player_stat;
	TTF_Font* ttf_font;

	float font_size = 40;
};

