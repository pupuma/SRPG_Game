#pragma once

#include "State.h"

class DeadState
	: public State
{
public:
	DeadState(Character* _character);
	~DeadState();
public:
	void Start();
	void Update();
};

