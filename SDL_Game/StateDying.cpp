#include "StateDying.h"
#include "Game.h"


StateDying::StateDying(GameObject * game_object, std::string next_state) : State(next_state)
{
	animator = game_object->getComponent<Animator>();

	sprite_renderer = game_object->getComponent<SpriteRenderer>();
}


StateDying::~StateDying()
{
}

void StateDying::start(StateMachine * state_machine)
{
	timeLeft = time_animation;

	animator->play("Dying");
}

void StateDying::operation(StateMachine * state_machine)
{
	if (is_alpha_phase) {
		float alpha_value = (timeLeft / time_alpha_0) * SDL_ALPHA_OPAQUE;
		state_machine->getGameObject()->getComponent<SpriteRenderer>()->setAlpha(alpha_value);
	}

	timeLeft -= Time::deltaTime;
	if (timeLeft <= 0) {
		if (is_alpha_phase) {

			//Manage the game_object
			//state_machine->getGameObject()->is_active = false;
			Game::instance()->destroyGameObject(state_machine->getGameObject()->getRootParent());
		}
		else {
			is_alpha_phase = true;

			timeLeft = time_alpha_0;
		}
	}
}

void StateDying::exit(StateMachine * state_machine)
{
}
