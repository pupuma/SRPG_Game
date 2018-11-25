#pragma once

#include "PathfindingState.h"
class PathfindingImmedateState
	: public PathfindingState
{
public:
	PathfindingImmedateState(Character* _character);
	~PathfindingImmedateState();
public:
	void Start();
};

