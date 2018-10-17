#include "StateMeleeAttack.h"
#include "Game.h"


StateMeleeAttack::StateMeleeAttack(GameObject * gameObject, std::string nextState, float timeAttack, float velocityAttack) : State(nextState), timeAttack(timeAttack), velocityAttack(velocityAttack)
{
	enemyBasicBehavior = gameObject->getComponent<EnemyBasicBehavior>();
	colliderActive = gameObject->getRootParent()->getComponentInChildren<EnemyAttackCollider>()->getDamageCollider();
}


StateMeleeAttack::~StateMeleeAttack()
{
	
}

void StateMeleeAttack::start(StateMachine* state_machine)
{
	state_machine->getGameObject()->getComponent<Animator>()->play("BeforeAttack");
	target = Game::instance()->findGameObject("Player");

	timeLeft = timeAttack;
	beforeAttack = true;
	normalizeDirection = (target->getWorldPosition() - state_machine->getGameObject()->getWorldPosition());
	OwnMathFuncs::OwnMathFuncs::normalize(normalizeDirection);

	if (normalizeDirection.x < 0 && state_machine->getGameObject()->getWorldScale().x > 0) {
		state_machine->getGameObject()->localScale.x *= -1;
	}
	else if (normalizeDirection.x > 0 && state_machine->getGameObject()->getWorldScale().x < 0) {
		state_machine->getGameObject()->localScale.x *= -1;
	}
}

void StateMeleeAttack::operation(StateMachine* state_machine)
{
	timeLeft -= Time::deltaTime;
	if (timeLeft <= 0) {
		if (beforeAttack) {
			state_machine->getGameObject()->getComponent<Animator>()->play("Attack");
			state_machine->getGameObject()->getComponent<EnemyBasicBehavior>()->addForce(normalizeDirection, velocityAttack, false);

			beforeAttack = false;

			timeLeft = timeAttack * 0.5;

			colliderActive->setActive(true);
		}
		else {
			colliderActive->setActive(false);

			state_machine->play(getNextState());
		}
	}
	
}

void StateMeleeAttack::exit(StateMachine* state_machine)
{
	colliderActive->setActive(false);
}
