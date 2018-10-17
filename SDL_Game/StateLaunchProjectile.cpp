#include "StateLaunchProjectile.h"
#include "Game.h"


StateLaunchProjectile::StateLaunchProjectile(GameObject* gameObject, std::string nextState) : State(nextState)
{

}


StateLaunchProjectile::~StateLaunchProjectile()
{

}

void StateLaunchProjectile::start(StateMachine * state_machine)
{
	if (target == nullptr) {
		target = Game::instance()->findGameObject("Player");
	}

	beforeAttack = true;

	state_machine->getGameObject()->getComponent<Animator>()->play("BeforeAttack");
	timeLeft = timeAttack;

	directionVector = (target->getWorldPosition() - state_machine->getGameObject()->getWorldPosition());
	OwnMathFuncs::OwnMathFuncs::normalize(directionVector);

	if (directionVector.x < 0 && state_machine->getGameObject()->getWorldScale().x > 0) {
		state_machine->getGameObject()->localScale.x *= -1;
	}
	else if (directionVector.x > 0 && state_machine->getGameObject()->getWorldScale().x < 0) {
		state_machine->getGameObject()->localScale.x *= -1;
	}
}

void StateLaunchProjectile::operation(StateMachine * state_machine)
{

	timeLeft -= Time::deltaTime;
	if (timeLeft <= 0) {
		if (beforeAttack) {

			state_machine->getGameObject()->getComponent<Animator>()->play("Attack");
			beforeAttack = false;
			timeLeft = timeCd;


			SlimProjectilePrefab* project = new SlimProjectilePrefab({ state_machine->getGameObject()->getWorldPosition().x + (4 * state_machine->getGameObject()->localScale.x), state_machine->getGameObject()->getWorldPosition().y + 12 });
			project->getComponent<ProjectileBehavior>()->setDirection(directionVector);
			project->getComponent<ProjectileBehavior>()->setSpeed(400);

			Game::instance()->instantiateGameObject(project);
		}
		else {

			state_machine->play(getNextState());
		}
	}
}

void StateLaunchProjectile::exit(StateMachine * state_machine)
{

}
