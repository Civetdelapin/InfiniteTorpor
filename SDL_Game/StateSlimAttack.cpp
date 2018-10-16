#include "StateSlimAttack.h"
#include "Game.h"

StateSlimAttack::StateSlimAttack(GameObject * gameObject, int nb_projectile, std::string next_state) : State(next_state), nb_projectile(nb_projectile)
{

}


StateSlimAttack::~StateSlimAttack()
{

}

void StateSlimAttack::start(StateMachine* state_machine)
{
	attack = false;
	timeLeft = time_attack;

	state_machine->getGameObject()->getComponent<Animator>()->play("Jump");
}

void StateSlimAttack::operation(StateMachine* state_machine)
{
	timeLeft -= Time::deltaTime;

	if (timeLeft <= 0) {

		if (!attack) {
			createProjectiles(state_machine);

			attack = true;
			timeLeft = time_cd;
		}
		else {
			state_machine->play(getNextState());
		}
	}

	
}

void StateSlimAttack::exit(StateMachine* state_machine)
{
	
}

void StateSlimAttack::createProjectiles(StateMachine* state_machine)
{
	float incr_degree = 360.0f / nb_projectile;

	for (int i = 0; i < nb_projectile; i++) {
		float cur_degree = (incr_degree * i);

		double incr_rad = cur_degree * (M_PI / 180);
		OwnMathFuncs::Vector2 direction = { (float)std::cos(incr_rad), (float)std::sin(incr_rad) };

		SlimProjectilePrefab* project = new SlimProjectilePrefab({ state_machine->getGameObject()->getWorldPosition().x, state_machine->getGameObject()->getWorldPosition().y + 50 });
		project->getComponent<ProjectileBehavior>()->setDirection(direction);

		Game::instance()->instantiateGameObject(project);

		//std::cout << cur_degree << std::endl;
		//std::cout << incr_rad << " : " <<(incr_degree * i) << " : " << direction.x << ", " << direction.y << std::endl;
	}
}
