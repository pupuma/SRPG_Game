#pragma once

enum eStateType;

class Character;
class TileCell;
class Map;

class State
{
protected:
	bool isMove;
protected:
	TileInfo tileInfo;
	TileCell* targetTileCell;
	TileCell* reverseTileCell;

protected:
	//int distSize;
	Map* map;
	std::vector<Component*> attackList;
protected:
	Character* character;
	eStateType nextState;
protected:
	struct sPathCommand
	{
		TileCell* tileCell;
		float heuristic;	// 이 값이 작을수록 더 빨리 검사해야 할 타일이다
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

	//std::list<TileInfo> tileCellOpenList;
	//std::list<Image*> moveTileList;
public:
	State(Character* _character);
	virtual ~State();
public:
	virtual void Start();
	virtual void Stop() {}
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Release();
	virtual void Reset();
public:
	void Direction();
public:
	//void UpdatePathfinding();
	//void UpdateBuildPath();
	//TilePoint GetSearchTilePositionByDirection(TilePoint _tilePosition, eDirection _direction);

public:
	//void PathFindingIdle();
	//void PathFindingMove();
	//void MovingAbleTile(int _distSize, TilePoint _prevPos);

public:
	void ChangeState(eStateType _nextState) { nextState = _nextState; }
public:
	void SetMove(bool _move) { isMove = _move; }
	bool GetMove() { return isMove; }
	//std::list<Image*> GetMoveTileList() { return moveTileList; }
};
