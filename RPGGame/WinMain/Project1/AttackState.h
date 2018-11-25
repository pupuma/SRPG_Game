#pragma once

#include "State.h"

class AttackState 
	: public State
{
public:
	AttackState(Character* _character);
	~AttackState();
public:
	void Start();
	void Stop() {}
	void Update();
	void Render(HDC hdc);
};

