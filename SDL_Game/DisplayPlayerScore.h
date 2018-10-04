#pragma once
#include "Renderer.h"
#include "PlayerStat.h"

class DisplayPlayerScore : public Renderer
{
public:
	DisplayPlayerScore(GameObject* game_object, PlayerStat* player_stat);
	~DisplayPlayerScore();

	void start();
	void update();
	void render();

	void clean();

private:
	PlayerStat * player_stat;
	TTF_Font* ttf_font;

	float font_size = 40;
};

