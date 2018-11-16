#pragma once

enum eStateType;
class Character;


class State
{
protected:
	Character* character;
	eStateType nextState;
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
	void ChangeState(eStateType _nextState) { nextState = _nextState; }
};

