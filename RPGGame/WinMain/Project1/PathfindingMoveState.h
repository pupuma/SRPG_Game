#pragma once
#include "State.h" 

class PathfindingMoveState
	: public  State
{
public:
	PathfindingMoveState(Character* character);
	~PathfindingMoveState();

private:
	float movingDuration;

public:
	void Start();
	void Stop();
	void Update();

	eDirection GetDirection(TilePoint toPostion, TilePoint fromPosition);
};

