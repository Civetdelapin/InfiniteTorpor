#include "StateMeleeAttack.h"
#include "Game.h"


StateMeleeAttack::StateMeleeAttack(GameObject * gameObject, std::string next_state, float time_attack, float velocity_attack) : State(next_state), time_attack(time_attack), velocity_attack(velocity_attack)
{
	enemy_basic_behavior = gameObject->getComponent<EnemyBasicBehavior>();
	collider_active = gameObject->getRootParent()->getComponentInChildren<EnemyAttackCollider>()->getDamageCollider();
}


StateMeleeAttack::~StateMeleeAttack()
{
	
}

void StateMeleeAttack::start(StateMachine* state_machine)
{
	state_machine->getGameObject()->getComponent<Animator>()->play("BeforeAttack");
	target = Game::instance()->findGameObject("Player");

	timeLeft = time_attack;
	before_attack = true;
	normalize_dir = (target->getWorldPosition() - state_machine->getGameObject()->getWorldPosition());
	OwnMathFuncs::OwnMathFuncs::normalize(normalize_dir);

	if (normalize_dir.x < 0 && state_machine->getGameObject()->getWorldScale().x > 0) {
		state_machine->getGameObject()->localScale.x *= -1;
	}
	else if (normalize_dir.x > 0 && state_machine->getGameObject()->getWorldScale().x < 0) {
		state_machine->getGameObject()->localScale.x *= -1;
	}
}

void StateMeleeAttack::operation(StateMachine* state_machine)
{
	timeLeft -= Time::deltaTime;
	if (timeLeft <= 0) {
		if (before_attack) {
			state_machine->getGameObject()->getComponent<Animator>()->play("Attack");
			state_machine->getGameObject()->getComponent<EnemyBasicBehavior>()->addForce(normalize_dir, velocity_attack, false);

			before_attack = false;

			timeLeft = time_attack * 0.5;

			collider_active->setActive(true);
		}
		else {
			collider_active->setActive(false);

			state_machine->play(getNextState());
		}
	}
	
}

void StateMeleeAttack::exit(StateMachine* state_machine)
{
	collider_active->setActive(false);
}
