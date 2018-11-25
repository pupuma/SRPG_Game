#pragma once

#include "State.h"

class PathfindingState 
	: public State
{
protected:
	TileInfo tileInfo;
	TileCell* targetTileCell;
	TileCell* reverseTileCell;

protected:
	//int distSize;
	Map* map;

protected:

protected:
	struct sPathCommand
	{
		TileCell* tileCell;
		float heuristic;	// �� ���� �������� �� ���� �˻��ؾ� �� Ÿ���̴�
	};
protected:

	struct compare
	{
		bool operator()(sPathCommand& a, sPathCommand& b)
		{
			return a.heuristic > b.heuristic;
		}
	};
protected:
	enum eUpdateState
	{
		PATHFINDING,
		BUILD_PATH
	};
	eUpdateState updateState;

protected:
	std::priority_queue<sPathCommand, std::vector<sPathCommand>, compare> pathfindingQueue;
public:
	PathfindingState(Character* _character);
	~PathfindingState();
public:
	void Start();
	void Stop();
	void Update();

public:
	void UpdatePathfinding();
	void UpdateBuildPath();
	TilePoint GetSearchTilePositionByDirection(TilePoint _tilePosition, eDirection _direction);

};

