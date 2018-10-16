#include "DisplayEnemyHp.h"



DisplayEnemyHp::DisplayEnemyHp(GameObject* gameObject, EnemyBasicBehavior* enemyBehavior) : Renderer(this), Component(gameObject),enemyBehavior(enemyBehavior)
{
}


DisplayEnemyHp::~DisplayEnemyHp()
{


}

void DisplayEnemyHp::start()
{
	lastHP = enemyBehavior->getMaxHP();
}

void DisplayEnemyHp::update()
{
	if (lastHP != enemyBehavior->getCurHP()) {
		
		lastHpDisplay = lastHP;
		if (lastHpDisplay > enemyBehavior->getMaxHP()) {
			lastHpDisplay = enemyBehavior->getMaxHP();
		}
		else {
			timeLeft = timeToDisplayWhenHit;
		}

		lastHP = enemyBehavior->getCurHP();
	}

	timeLeft -= Time::deltaTime;
}

void DisplayEnemyHp::render()
{
	
	if (timeLeft > 0 && lastHP > 0) {
		SDL_Rect rect;
		rect.x = gameObject->getWorldPosition().x - ((size.x / 2) * abs(gameObject->getWorldScale().x));
		rect.y = gameObject->getWorldPosition().y - (Yoffset * abs(gameObject->getWorldScale().y));


		//Draw the background
		rect.w = size.x * abs(gameObject->getWorldScale().x);
		rect.h = size.y * abs(gameObject->getWorldScale().y);

		TextureManager::DrawRect(rect, 255, 255, 255, 255, true);

		//Draw the damage taken
		float pourc_damage = lastHpDisplay * 100 / enemyBehavior->getMaxHP();
		rect.w = pourc_damage / 100 * (size.x * abs(gameObject->getWorldScale().x));

		TextureManager::DrawRect(rect, 255, 255, 0, 255, true);

		//Draw the health bar
		float pourc = enemyBehavior->getCurHP() * 100 / enemyBehavior->getMaxHP();
		rect.w = pourc / 100 * (size.x * abs(gameObject->getWorldScale().x));

		TextureManager::DrawRect(rect, 255, 0, 0, 255, true);
	}

}

void DisplayEnemyHp::clean()
{
	enemyBehavior = NULL;
	Renderer::clean();
	Component::clean();
}

void DisplayEnemyHp::setYOffset(float value)
{
	Yoffset = value;
}
