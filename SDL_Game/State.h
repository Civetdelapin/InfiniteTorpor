#pragma once
#include "GameObject.h"
class State {

public:
	virtual void operation(GameObject* game_object) = 0;

};