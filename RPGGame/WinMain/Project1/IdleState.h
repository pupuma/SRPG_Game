#pragma once

#include "State.h"
class IdleState
	: public State
{
public:
	IdleState(Character* _character);
	~IdleState();
public:
	void Start();
	void Update();
};

