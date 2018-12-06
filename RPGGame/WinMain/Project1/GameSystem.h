#pragma once

#include "SingletonBase.h"

class Map;
class Component;
class Character;

class GameSystem
	: public SingletonBase<GameSystem>
{
private:
	bool isAction;
	bool isAttacking;
	int round;
	int currentCharacterIndex;
	//std::list<TileInfo> moveTileList;
	TilePoint temp;
private:
	Map* g_Map;
private:
	std::vector<TileInfo> g_TileAttackList;
	std::vector<Character*> characterList;

public:
	GameSystem();
	~GameSystem();
public:
	void SetMousePosition(LPARAM lParam);
	POINT GetMousePosition();
public:
	void ResetTarget();
	void SetMap(Map* _map);
	bool TargetCheck(std::vector<Component*> _list, Character* _character);
	void AddCharacterList(Character* _character);
	void GameTurn();
	eDirection LookAtCharacter(std::vector<Component*> _list,  Character* _character);
public:
	bool IsAction() { return isAction; }
	void SetAction(bool _isAction) { isAction = _isAction; }
	bool IsAttacking() { return isAttacking; }
	void SetAttacking(bool _isAttack) { isAttacking = _isAttack; }
	std::vector<TileInfo> GetTileAttackList() { return g_TileAttackList; }
	void SetTileAttackList(std::vector<TileInfo> _list) { g_TileAttackList = _list; }
public:

};

