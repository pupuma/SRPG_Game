#pragma once


class GameTurnManager
	: public SingletonBase<GameTurnManager>
{
private:
	int characterIndex;
public:
	GameTurnManager();
	~GameTurnManager();
public:
	void Init();
	void NextTurn();
	void AttackAction();
	bool PlayerTrun();
	bool MyTurn(TilePoint _pos);
	void SkillAction(int _number);
};

