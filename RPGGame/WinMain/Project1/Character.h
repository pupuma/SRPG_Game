#pragma once


// Game State 
enum eStateType
{
	ST_NONE,
	ST_IDLE,
	ST_MOVE,
	ST_ATTACK,
	ST_DEFENSE,
	ST_DEAD,
	ST_PATHFINDING,
	ST_PATH_MOVE,
	ST_PATH_IDLE,
	ST_PATH_NAVI

};


enum eJobClass
{
	JOB_NONE,
	JOB_WARRIOR,
	JOB_ARCHER,
	JOB_HEALER,
};

class State;
class Action;
class TileCell;

class Character 
	: public Component
{
protected:
	eJobClass job;

protected:
	bool isMoving;
	bool isLive;
	bool isTurn;
	float moveTime;
	int frameX;
	int frameY;

	eStateType eType;
	eDirection nextDirection;
	eDirection currentDirection;
	TileCell* targetTileCell;
protected:
	State* state;
	std::map<eStateType, State*> stateMap;
	std::stack<TileCell*> pathfindingCellStack;
	std::vector<TileInfo> attackList;
	std::vector<Component*> targetList;
protected:
	TileCell* targetCharacterTile;
protected:
	Image* img;
	//Action* act;
protected:
	int attackPoint;
	int damagePoint;

	int iHp;
public:
	Character(std::string _name, float _deep);
	~Character();
public:
	virtual bool Init();
	void Deinit();
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
public:
	virtual void InitState();
public:
	void ChangeState(eStateType stateType);
public:
	virtual void UpdateAI();
public:
	virtual void AttackPattern();
public:
	void ReceiveMsg(const sMessageParam& param);
public:

	void MoveStart(TilePoint newTilePosition);
	void MoveStop();
	bool IsMoving();
	bool IsLive();
	TileCell* GetTargetTileCell();
	void SetTargetTileCell(TileCell* _targetTileCell);
	void PushPathfindingCell(TileCell* _tileCell);
	TileCell* PopPathfindingCell();
	float GetMoveTime();
	bool IsEmptyPathfindingStack();
	void SetNextDirection(eDirection _direction);
	void SetDirection(eDirection _direction);
	std::vector<Component*> GetTargetList();
	void AddTarget(Component* _target);
	void ResetTarget();
	void DecreaseHP(int _damagePoint);
	void SetTilePosition(int _tilePosX, int _tilePosY);
	void SetImgFrame(int _frameX, int _frameY);
	void SetTurn(bool _isTurn);
public:
	State* GetState() { return state; }
	int GetAttackPoint() { return attackPoint; }
	void SetTarget(std::vector<Component*> _target) { targetList = _target; }
	int GetDamagePoint() { return damagePoint; }
	eDirection GetDirection() { return currentDirection; }
	int GetDistance() { return iMaxMoving; }
	eDirection GetNextDirection() { return nextDirection; }
	eJobClass GetJobClass() { return job; }
	void SetJobClass(eJobClass _job) { job = _job; }
	int GetHp() { return iHp; }
	void SetHp(int _hp) { iHp = _hp; }
	void SetCharacterTileCell(TileCell* _targetTileCellCharacter) { targetCharacterTile = _targetTileCellCharacter; }
	TileCell* GetCharacterTileCell() { return targetCharacterTile; }

public:
#if defined(_DEBUG_TEST)
	void SetStateType(eStateType _type) { eType = _type; }
	eStateType GetType() { return eType; }
	bool IsTurn() { return isTurn; }
	
	
#endif // StateTYpe Render Test 
};