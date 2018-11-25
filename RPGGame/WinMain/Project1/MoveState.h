#pragma once

#include "State.h"
class MoveState
	: public State
{
private:
public:
	MoveState(Character* _character);
	~MoveState();
public:
	void Start();
	void Stop();
	void Update();
public:
	void UpdateMove();

};

