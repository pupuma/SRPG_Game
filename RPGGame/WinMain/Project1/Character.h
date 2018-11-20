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
};

class State;
class Action;

class Character : public Component
{
protected:
	bool isMoving;
	bool isLive;
	
	int iMaxMoving;
	eStateType eType;
	eDirection nextDirection;

protected:
	State* state;
	std::map<eStateType, State*> stateMap;
protected:
	Image* img;
	Action* act;
public:
	Character(std::string _name);
	~Character();
public:
	bool Init( );
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
	void UpdateAI();
public:
	void MoveStart(TilePoint newTilePosition);
	void MoveStop();
	bool IsMoving();
	bool IsLive();
public:
	int GetMaxMoving() { return iMaxMoving; }
	State* GetState() { return state; }
public:
#if defined(_DEBUG_TEST)
	void SetStateType(eStateType _type) { eType = _type; }
	eStateType GetType() { return eType; }
#endif // StateTYpe Render Test 
};