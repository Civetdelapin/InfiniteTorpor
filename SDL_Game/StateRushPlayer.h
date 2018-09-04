#pragma once
#include "State.h"
#include "VelocityBody.h"
class StateRushPlayer : public State
{
public:
	StateRushPlayer(GameObject * game_object);
	~StateRushPlayer();

	void operation(GameObject* game_object);

private:
	GameObject * target;
	VelocityBody* velocity_body;
};

