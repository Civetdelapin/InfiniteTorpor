#include "StateLaunchProjectile.h"
#include "Game.h"


StateLaunchProjectile::StateLaunchProjectile(GameObject* gameObject, std::string next_state) : State(next_state)
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

	before_attack = true;

	state_machine->getGameObject()->getComponent<Animator>()->play("BeforeAttack");
	time_left = time_attack;

	dir_vect = (target->getWorldPosition() - state_machine->getGameObject()->getWorldPosition());
	OwnMathFuncs::OwnMathFuncs::normalize(dir_vect);

	if (dir_vect.x < 0 && state_machine->getGameObject()->getWorldScale().x > 0) {
		state_machine->getGameObject()->localScale.x *= -1;
	}
	else if (dir_vect.x > 0 && state_machine->getGameObject()->getWorldScale().x < 0) {
		state_machine->getGameObject()->localScale.x *= -1;
	}
}

void StateLaunchProjectile::operation(StateMachine * state_machine)
{

	time_left -= Time::deltaTime;
	if (time_left <= 0) {
		if (before_attack) {

			state_machine->getGameObject()->getComponent<Animator>()->play("Attack");
			before_attack = false;
			time_left = time_cd;


			SlimProjectilePrefab* project = new SlimProjectilePrefab({ state_machine->getGameObject()->getWorldPosition().x + (4 * state_machine->getGameObject()->localScale.x), state_machine->getGameObject()->getWorldPosition().y + 12 });
			project->getComponent<ProjectileBehavior>()->setDirection(dir_vect);
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
