#pragma once

#include "State.h"

class NavigationState
	: public State
{
public:
	bool isNavi;
	float deltaTime;
public:
	NavigationState(Character* _character);
	~NavigationState();
public:
	void Start();
	void Stop() {}
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
};

