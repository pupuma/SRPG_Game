#pragma once

enum eStateType;
class Character;
class TileCell;


class State
{
protected:
	TileInfo tileInfo;
protected:
	int distSize;


protected:
	Character* character;
	eStateType nextState;
protected:
	std::list<TileInfo> tileCellOpenList;
	std::list<Image*> moveTileList;
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
	//void PathFindingIdle();
	//void PathFindingMove();
	//void MovingAbleTile(int _distSize, TilePoint _prevPos);

public:
	void ChangeState(eStateType _nextState) { nextState = _nextState; }
public:
	std::list<Image*> GetMoveTileList() { return moveTileList; }
};

