#pragma once

class Character;
class TileCell;

class NaviGationSystem
	: public SingletonBase<NaviGationSystem>
{
private:
	struct sPathCommand
	{
		TileCell* tileCell;
		float heuristic;	// 이 값이 작을수록 더 빨리 검사해야 할 타일이다
	};

	enum eUpdateState
	{
		PATHFINDING,
		BUILD_PATH
	};
	eUpdateState updateState;
	TileCell* reverseTileCell;
	struct compare
	{
		bool operator()(sPathCommand& a, sPathCommand& b)
		{
			return a.heuristic > b.heuristic;
		}
	};
	std::priority_queue<sPathCommand, std::vector<sPathCommand>, compare> pathfindingQueue;
private:
	TileCell* startTileCell;
	TileCell* endTileCell;
private:
	std::list<TileCell*> closeList;
	std::queue<TileCell*> q_Close;
public:
	NaviGationSystem();
	~NaviGationSystem();
public:
	TileCell* AStarPathFinder(Character* _startCharacter, Character* _endCharacter);
	TileCell* AStarPathFinder(Character* _startCharacter, TileCell* _endTileCell);

	void UpdatePathfinding();
	void UpdateBuildPath();

	TilePoint GetSearchTilePositionByDirection(TilePoint _tilePosition, eDirection _direction);

	float CalcComplexHeuristic(TileCell* search, TileCell* goal);
	float CalcAStarHeuristic(float distanceFromStart, TileCell* search, TileCell* goal);
	TileCell* DistanceTileCell(std::list<TileInfo> _list);

	void Reset();
};

