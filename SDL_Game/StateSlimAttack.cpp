#include "StateSlimAttack.h"
#include "Game.h"

StateSlimAttack::StateSlimAttack(GameObject * game_object, int nb_projectile, std::string next_state) : State(next_state), nb_projectile(nb_projectile)
{

}


StateSlimAttack::~StateSlimAttack()
{

}

void StateSlimAttack::start(StateMachine* state_machine)
{

}

void StateSlimAttack::operation(StateMachine* state_machine)
{
	int incr_degree = 360 / nb_projectile;

	for (int i = 0; i <= nb_projectile; i++) {
		double incr_rad = (incr_degree * i) * (M_PI / 180);
		OwnMathFuncs::Vector2 direction = {(float) std::cos(incr_rad), (float) std::sin(incr_rad) };

		SlimProjectilePrefab* project = new SlimProjectilePrefab({state_machine->getGameObject()->getWorldPosition().x, state_machine->getGameObject()->getWorldPosition().y + 50});
		project->getComponent<ProjectileBehavior>()->setDirection(direction);

		Game::instance()->addGameObjectInGame(project);

		//std::cout << incr_rad << " : " <<(incr_degree * i) << " : " << direction.x << ", " << direction.y << std::endl;
	}

	state_machine->play(getNextState());
}

void StateSlimAttack::exit(StateMachine* state_machine)
{
	
}