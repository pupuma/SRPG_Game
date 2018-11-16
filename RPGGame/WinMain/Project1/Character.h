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
private:
	State* state;
	std::map<eStateType, State*> stateMap;

private:
	Image* img;
	Action* act;
public:
	Character(std::string _name);
	~Character();
public:
	bool Init();
	void Deinit();
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
public:
	virtual void InitState();
public:
	void ChangeState(eStateType stateType);

};