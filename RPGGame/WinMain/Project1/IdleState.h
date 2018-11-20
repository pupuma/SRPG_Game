#pragma once

#include "State.h"

class Character;

class IdleState
	: public State
{
public:
	IdleState(Character* _character);
	~IdleState();
public:
	void Start();
	void Update();
	
	//
	void Render(HDC hdc);
};

