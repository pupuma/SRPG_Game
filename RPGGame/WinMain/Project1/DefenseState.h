#pragma once

#include "State.h"

class DefenseState
	: public State
{
public:
	DefenseState(Character* _character);
	~DefenseState();
};

