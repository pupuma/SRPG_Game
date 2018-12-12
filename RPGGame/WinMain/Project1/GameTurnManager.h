#pragma once
class GameTurnManager
	: public SingletonBase<GameTurnManager>
{
private:

public:
	GameTurnManager();
	~GameTurnManager();
public:
	void NextTurn();
};

