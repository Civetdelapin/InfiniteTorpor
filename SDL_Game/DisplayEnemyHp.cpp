#include "DisplayEnemyHp.h"



DisplayEnemyHp::DisplayEnemyHp(GameObject* game_object, EnemyBasicBehavior* enemy_stat) : Component(game_object), enemy_stat(enemy_stat)
{
	last_hp = enemy_stat->max_hp;
}


DisplayEnemyHp::~DisplayEnemyHp()
{


}

void DisplayEnemyHp::update()
{
	if (last_hp != enemy_stat->cur_hp) {
		
		last_hp_display = last_hp;
		if (last_hp_display > enemy_stat->max_hp) {
			last_hp_display = enemy_stat->max_hp;
		}
		else {
			time_passed = time_display_when_hit;
		}

		last_hp = enemy_stat->cur_hp;
	}

	time_passed -= Time::deltaTime;
}

void DisplayEnemyHp::render()
{
	
	if (time_passed > 0) {
		SDL_Rect rect;
		rect.x = game_object->getWorldPosition().x - ((size.x / 2) * abs(game_object->getWorldScale().x));
		rect.y = game_object->getWorldPosition().y - (1.75 * abs(game_object->getWorldScale().y));


		//Draw the background
		rect.w = size.x * abs(game_object->getWorldScale().x);
		rect.h = size.y * abs(game_object->getWorldScale().y);

		TextureManager::DrawRect(rect, 255, 255, 255, 255, true);

		//Draw the damage taken
		float pourc_damage = last_hp_display * 100 / enemy_stat->max_hp;
		rect.w = pourc_damage / 100 * (size.x * abs(game_object->getWorldScale().x));

		TextureManager::DrawRect(rect, 255, 255, 0, 255, true);

		//Draw the health bar
		float pourc = enemy_stat->cur_hp * 100 / enemy_stat->max_hp;
		rect.w = pourc / 100 * (size.x * abs(game_object->getWorldScale().x));

		TextureManager::DrawRect(rect, 255, 0, 0, 255, true);
	}

}
