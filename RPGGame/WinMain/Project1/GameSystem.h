#pragma once

#include "SingletonBase.h"

enum eStateType;

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
	bool isMove;
	bool isAttacking;
	int round;
	int currentCharacterIndex;

	int width;
	int height;
	//std::list<TileInfo> moveTileList;
	TilePoint temp;
	eStateType eType;
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
	bool AttackRangeCheck(Character* _character);
	void AddProioritySelectList(Character* _character);
	
public:
	bool IsAction() { return isAction; }
	void SetAction(bool _isAction) { isAction = _isAction; }
	bool IsAttacking() { return isAttacking; }
	void SetAttacking(bool _isAttack) { isAttacking = _isAttack; }
	std::vector<TileInfo> GetTileAttackList() { return g_TileAttackList; }
	void SetTileAttackList(std::vector<TileInfo> _list) { g_TileAttackList = _list; }
	TileCell* GetTargetTileCell() { return targetTileCell; }
	void SetTargetTileCell(TileCell* _targetTileCell) { targetTileCell = _targetTileCell; }
	std::vector<Character*> GetCharacterList() { return characterList; }
	void SetMove(bool _move) { isMove = _move; }
	bool GetMove() { return isMove; }
	void SetType(eStateType _type) { eType = _type; }
	eStateType GetType() { return eType; }
};