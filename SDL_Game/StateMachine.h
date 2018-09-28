#pragma once
#include "Component.h"
#include "State.h"
#include <map>

class StateMachine : public Component
{
public:
	StateMachine(GameObject* game_object);
	~StateMachine();

	void update();
	void clean();

	void addState(std::pair <std::string, State*> state);

	void play(std::string state_name);

	std::string getDefaultState();
	void setDefaultState(std::string value);

private:
	std::map <std::string, State*> states;
	std::string cur_state = "";

	std::string default_state = "";
};

