#pragma once


// Game State 
enum eStateType
{
	ST_NONE,
	ST_IDLE,
	ST_MOVE,
	ST_ATTACK,
	ST_SKILL,
	ST_DEFENSE,
	ST_DEAD,
	ST_PATHFINDING,
	ST_PATH_MOVE,
	ST_PATH_IDLE,
	ST_PATH_NAVI,
};



class State;
class Action;
class TileCell;

class Character 
	: public Component
{
protected:
	//eJobClass job;

protected:
	bool isMoving;
	bool isLive;
	bool isTurn;
	float moveTime;
	int frameX;
	int frameY;

	int faceNumberX;
	int faceNumberY;
	int faceNumber;

	std::string name;
	
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
	std::vector<TileInfo> skillList1;
	std::vector<TileInfo> skillList2;
	std::vector<TileInfo> skillList3;

	
protected:
	TileCell* targetCharacterTile;
protected:
	Image* img;
	//Action* act;
protected:
	int attackPoint;
	int damagePoint;
	int healPoint;

	int iHp;
	int iMaxHp;
	int iMp;
	int iMaxMp;
public:
	Character(std::string _name, float _deep);
	~Character();
public:
	virtual bool Init();
	virtual bool Init(int _index);

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
	void InCreaseHP(int _healPoint);

	void SetTilePosition(int _tilePosX, int _tilePosY);
	void SetImgFrame(int _frameX, int _frameY);
	void SetTurn(bool _isTurn);
	virtual void SkillPattern(int _number);
	void EatItem();
public:
	void SetFrameX(int _frameX) { frameX = _frameX; }
	void SetFrameY(int _frameY) { frameY = _frameY; }
	void SetFaceFrameX(int _faceX) { faceNumberX = _faceX; }
	void SetFaceFrameY(int _faceY) { faceNumberY = _faceY; }
	int GetFaceFrameX() { return faceNumberX; }
	int GetFaceFrameY() { return faceNumberY; }
	int GetFaceNumber() { return faceNumber; }

	State* GetState() { return state; }
	int GetAttackPoint() { return attackPoint; }
	void SetTarget(std::vector<Component*> _target) { targetList = _target; }
	int GetDamagePoint() { return damagePoint; }
	eDirection GetDirection() { return currentDirection; }
	int GetDistance() { return iMaxMoving; }
	eDirection GetNextDirection() { return nextDirection; }
	//eJobClass GetJobClass() { return job; }
	//void SetJobClass(eJobClass _job) { job = _job; }
	int GetHp() { return iHp; }
	void SetHp(int _hp) { iHp = _hp; }
	int MaxGetHp() { return iMaxHp; }
	int GetMp() { return iMp; }
	void SetMp(int _mp) { iMp = _mp; }
	int GetMaxMp() { return iMaxMp; }
	void SetTargetCharacterTileCell(TileCell* _targetTileCellCharacter) { targetCharacterTile = _targetTileCellCharacter; }
	TileCell* GetTargetCharacterTileCell() { return targetCharacterTile; }
	int GetHealPoint() { return healPoint; }
	void SetHealPoint(int _heal) { healPoint = _heal; }
	std::string GetName() { return name; }
public:
#if defined(_DEBUG_TEST)
	void SetStateType(eStateType _type) { eType = _type; }
	eStateType GetType() { return eType; }
	bool IsTurn() { return isTurn; }
	
	
#endif // StateTYpe Render Test 
};