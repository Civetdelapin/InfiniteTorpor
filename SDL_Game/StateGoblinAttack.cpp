#include "StateGoblinAttack.h"
#include "Game.h"


StateGoblinAttack::StateGoblinAttack(GameObject * game_object)
{
	enemy_basic_behavior = game_object->getComponent<EnemyBasicBehavior>();

	if (enemy_basic_behavior->isStunned()) {
		game_object->getComponent<StateMachine>()->setSet(new StateRushPlayer(game_object));
	}
	else {
		
		target = Game::instance()->findGameObject("Player");
		game_object->getComponent<Animator>()->play("BeforeAttack");

		time_passed = time_attack;
		before_attack = true;
		normalize_dir = (target->getWorldPosition() - game_object->getWorldPosition());
	}
	
}


StateGoblinAttack::~StateGoblinAttack()
{

}

void StateGoblinAttack::operation(GameObject * game_object)
{
	if (enemy_basic_behavior->isStunned()) {
		game_object->getComponent<StateMachine>()->setSet(new StateRushPlayer(game_object));
	}
	else {
		time_passed -= Time::deltaTime;
		if (time_passed <= 0) {
			if (before_attack) {
				game_object->getComponent<Animator>()->play("Attack");
				game_object->getComponent<EnemyBasicBehavior>()->addForce(normalize_dir, velocity_attack);

				before_attack = false;

				time_passed = time_attack;
			}
			else {
				game_object->getComponent<StateMachine>()->setSet(new StateRushPlayer(game_object));
			}
		}
	}
}