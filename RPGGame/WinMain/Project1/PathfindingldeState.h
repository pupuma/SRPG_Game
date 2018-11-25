#pragma once

#include "State.h" 
class PathfindingldeState
	: public State

{
public:
	PathfindingldeState(Character* _character);
	~PathfindingldeState();
public:
	void Start();
	void Update();
};

