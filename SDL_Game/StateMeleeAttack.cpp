#include "StateMeleeAttack.h"
#include "Game.h"


StateMeleeAttack::StateMeleeAttack(GameObject * game_object, std::string next_state, float time_attack, float velocity_attack) : State(next_state), time_attack(time_attack), velocity_attack(velocity_attack)
{
	enemy_basic_behavior = game_object->getComponent<EnemyBasicBehavior>();
	collider_active = game_object->getRootParent()->getComponentInChildren<EnemyAttackCollider>()->getDamageCollider();
}


StateMeleeAttack::~StateMeleeAttack()
{
	
}

void StateMeleeAttack::start(StateMachine* state_machine)
{
	state_machine->getGameObject()->getComponent<Animator>()->play("BeforeAttack");
	target = Game::instance()->findGameObject("Player");

	time_passed = time_attack;
	before_attack = true;
	normalize_dir = (target->getWorldPosition() - state_machine->getGameObject()->getWorldPosition());
	OwnMathFuncs::OwnMathFuncs::normalize(normalize_dir);

	if (normalize_dir.x < 0 && state_machine->getGameObject()->getWorldScale().x > 0) {
		state_machine->getGameObject()->local_scale.x *= -1;
	}
	else if (normalize_dir.x > 0 && state_machine->getGameObject()->getWorldScale().x < 0) {
		state_machine->getGameObject()->local_scale.x *= -1;
	}
}

void StateMeleeAttack::operation(StateMachine* state_machine)
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

			state_machine->play(getNextState());
		}
	}
	
}

void StateMeleeAttack::exit(StateMachine* state_machine)
{
	collider_active->setIsActive(false);
}
