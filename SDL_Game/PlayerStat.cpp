#include "PlayerStat.h"



PlayerStat::PlayerStat(GameObject* game_object) : Component(game_object)
{
}


PlayerStat::~PlayerStat()
{
}

float PlayerStat::getCurHP()
{
	return cur_hp;
}

void PlayerStat::update()
{	
	if (is_invicible) {

		time_passed -= Time::deltaTime;

		if (time_passed <= 0) {
			is_invicible = false;
		}
	}	
}

void PlayerStat::addDamage(float dmg)
{
	if (!is_invicible) {
		cur_hp -= dmg;

		is_invicible = true;

		time_passed = time_invicible;
	}
}
