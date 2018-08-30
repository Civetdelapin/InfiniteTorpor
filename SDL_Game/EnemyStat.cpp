#include "EnemyStat.h"
#include "Game.h"

EnemyStat::EnemyStat(GameObject* game_object) : Component(game_object)
{
	cur_hp = max_hp;
}


EnemyStat::~EnemyStat()
{
}

void EnemyStat::update()
{
	if (cur_hp > max_hp) {
		cur_hp = max_hp;
	}
	else if (cur_hp <= 0) {
		Game::instance()->destroyGameObject(game_object->getRootParent());
	}
}
