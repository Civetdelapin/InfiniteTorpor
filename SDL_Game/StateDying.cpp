#include "StateDying.h"
#include "Game.h"


StateDying::StateDying(GameObject * gameObject, std::string nextState) : State(nextState)
{
	animator = gameObject->getComponent<Animator>();

	spriteRenderer = gameObject->getComponent<SpriteRenderer>();
}


StateDying::~StateDying()
{
}

void StateDying::start(StateMachine * state_machine)
{
	timeLeft = timeAnimation;

	animator->play("Dying");
}

void StateDying::operation(StateMachine * state_machine)
{
	if (alphaPhase) {
		float alpha_value = (timeLeft / timeAlphaToZero) * SDL_ALPHA_OPAQUE;
		state_machine->getGameObject()->getComponent<SpriteRenderer>()->setAlpha(alpha_value);
	}

	timeLeft -= Time::deltaTime;
	if (timeLeft <= 0) {
		if (alphaPhase) {

			//Manage the gameObject
			//state_machine->getGameObject()->active = false;
			Game::instance()->destroyGameObject(state_machine->getGameObject()->getRootParent());
		}
		else {
			alphaPhase = true;

			timeLeft = timeAlphaToZero;
		}
	}
}

void StateDying::exit(StateMachine * state_machine)
{
}
