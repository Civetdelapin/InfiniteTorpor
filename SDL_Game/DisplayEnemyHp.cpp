#include "DisplayEnemyHp.h"



DisplayEnemyHp::DisplayEnemyHp(GameObject* game_object, EnemyBasicBehavior* enemy_stat) : Component(game_object), enemy_stat(enemy_stat)
{
	
}


DisplayEnemyHp::~DisplayEnemyHp()
{


}

void DisplayEnemyHp::start()
{
	last_hp = enemy_stat->getMaxHP();
}

void DisplayEnemyHp::update()
{
	if (last_hp != enemy_stat->getCurHP()) {
		
		last_hp_display = last_hp;
		if (last_hp_display > enemy_stat->getMaxHP()) {
			last_hp_display = enemy_stat->getMaxHP();
		}
		else {
			time_passed = time_display_when_hit;
		}

		last_hp = enemy_stat->getCurHP();
	}

	time_passed -= Time::deltaTime;
}

void DisplayEnemyHp::render()
{
	
	if (time_passed > 0 && last_hp > 0) {
		SDL_Rect rect;
		rect.x = game_object->getWorldPosition().x - ((size.x / 2) * abs(game_object->getWorldScale().x));
		rect.y = game_object->getWorldPosition().y - (y_offset * abs(game_object->getWorldScale().y));


		//Draw the background
		rect.w = size.x * abs(game_object->getWorldScale().x);
		rect.h = size.y * abs(game_object->getWorldScale().y);

		TextureManager::DrawRect(rect, 255, 255, 255, 255, true);

		//Draw the damage taken
		float pourc_damage = last_hp_display * 100 / enemy_stat->getMaxHP();
		rect.w = pourc_damage / 100 * (size.x * abs(game_object->getWorldScale().x));

		TextureManager::DrawRect(rect, 255, 255, 0, 255, true);

		//Draw the health bar
		float pourc = enemy_stat->getCurHP() * 100 / enemy_stat->getMaxHP();
		rect.w = pourc / 100 * (size.x * abs(game_object->getWorldScale().x));

		TextureManager::DrawRect(rect, 255, 0, 0, 255, true);
	}

}

void DisplayEnemyHp::clean()
{
	enemy_stat = NULL;
	Component::clean();
}

void DisplayEnemyHp::setYOffset(float value)
{
	y_offset = value;
}
