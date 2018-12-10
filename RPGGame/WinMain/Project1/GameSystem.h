#pragma once

#include "SingletonBase.h"

class Map;
class Component;
class Character;
class TileCell;

class GameSystem
	: public SingletonBase<GameSystem>
{
private:
	typedef struct tagTileMoveInfo
	{
		TileCell* tileCell;
		int distance;
	}MoveInfo;
	MoveInfo moveInfo;
private:
	bool isAction;
	bool isAttacking;
	int round;
	int currentCharacterIndex;

	int width;
	int height;
	//std::list<TileInfo> moveTileList;
	TilePoint temp;
private:
	Map* g_Map;
	TileCell* targetTileCell;
private:
	std::vector<TileInfo> g_TileAttackList;
	std::vector<Character*> characterList;

	std::vector<Character*> playerList;
	std::vector<Character*> monsterList;
	std::vector<Character*> npcList;

	std::queue<TileCell*> pathfindingQueue;

	std::list<MoveInfo> moveList;

	std::vector<Character*> selectTargetList;
public:
	GameSystem();
	~GameSystem();
public:
	void Init();
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
	TileCell* FindPriorityTarget(Character* _character);
	std::list<MoveInfo> MaxMoveFinder(Character* _target);
	void ResetMovefinding();
	TileCell* CharacterPrioritySort(Character* _character);
	TileCell* CharacterSelectTileCell(Character* _character);
public:
	bool IsAction() { return isAction; }
	void SetAction(bool _isAction) { isAction = _isAction; }
	bool IsAttacking() { return isAttacking; }
	void SetAttacking(bool _isAttack) { isAttacking = _isAttack; }
	std::vector<TileInfo> GetTileAttackList() { return g_TileAttackList; }
	void SetTileAttackList(std::vector<TileInfo> _list) { g_TileAttackList = _list; }
	TileCell* GetTargetTileCell() { return targetTileCell; }
	void SetTargetTileCell(TileCell* _targetTileCell) { targetTileCell = _targetTileCell; }

public:

};

