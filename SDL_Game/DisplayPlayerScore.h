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

private:
	PlayerStat * player_stat;

	float font_size = 40;
};

