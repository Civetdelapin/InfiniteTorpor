#include "StateGoblinAttack.h"
#include "Game.h"


StateGoblinAttack::StateGoblinAttack(GameObject * game_object, std::string next_state) : State(next_state)
{
	enemy_basic_behavior = game_object->getComponent<EnemyBasicBehavior>();
	target = Game::instance()->findGameObject("Player");
	collider_active = game_object->getRootParent()->getComponentInChild<EnemyAttackCollider>()->getDamageCollider();
}


StateGoblinAttack::~StateGoblinAttack()
{
	
}

void StateGoblinAttack::start(StateMachine* state_machine)
{
	state_machine->getGameObject()->getComponent<Animator>()->play("BeforeAttack");

	time_passed = time_attack;
	before_attack = true;
	normalize_dir = (target->getWorldPosition() - state_machine->getGameObject()->getWorldPosition());
}

void StateGoblinAttack::operation(StateMachine* state_machine)
{
	time_passed -= Time::deltaTime;
	if (time_passed <= 0) {
		if (before_attack) {
			state_machine->getGameObject()->getComponent<Animator>()->play("Attack");
			state_machine->getGameObject()->getComponent<EnemyBasicBehavior>()->addForce(normalize_dir, velocity_attack);

			before_attack = false;

			time_passed = time_attack * 0.5;

			collider_active->setIsActive(true);
		}
		else {
			collider_active->setIsActive(false);

			state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
		}
	}
	
}

void StateGoblinAttack::exit(StateMachine* state_machine)
{
	collider_active->setIsActive(false);
}
