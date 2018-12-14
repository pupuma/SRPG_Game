#pragma once

#include "State.h"

class AttackState 
	: public State
{
private:
	float deltaTime;
public:
	AttackState(Character* _character);
	~AttackState();
public:
	void Start();
	void Stop() {}
	void Update();
	void Render(HDC hdc);
public:
};

