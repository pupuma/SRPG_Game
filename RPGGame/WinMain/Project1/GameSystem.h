#pragma once

#include "SingletonBase.h"

class Map;

class GameSystem
	: public SingletonBase<GameSystem>
{
private:
	bool isAction;
	bool isAttacking;
	//std::list<TileInfo> moveTileList;
private:
	Map* g_Map;
private:
	std::vector<TileInfo> g_TileAttackList;

public:
	GameSystem();
	~GameSystem();
public:
	void SetMousePosition(LPARAM lParam);
	POINT GetMousePosition();
public:
	void ResetTarget();
	void SetMap(Map* _map);

public:
	
	bool IsAction() { return isAction; }
	void SetAction(bool _isAction) { isAction = _isAction; }
	bool IsAttacking() { return isAttacking; }
	void SetAttacking(bool _isAttack) { isAttacking = _isAttack; }
	std::vector<TileInfo> GetTileAttackList() { return g_TileAttackList; }
	void SetTileAttackList(std::vector<TileInfo> _list) { g_TileAttackList = _list; }

};

