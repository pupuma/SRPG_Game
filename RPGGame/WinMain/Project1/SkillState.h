#pragma once
#include "State.h"

class Character;

class SkillState
	: public State
{
public:
	SkillState(Character* _character);
	~SkillState();
public:
	void Start();
	void Stop() {}
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
};