#pragma once

#include "State.h"
class MoveState
	: public State
{
public:
	MoveState(Character* _character);
	~MoveState();
};

