#pragma once

#include "SingletonBase.h"


enum eStateType;
enum eJobClass;

class Map;
class Component;
class Character;
class TileCell;
class HpBar;
class MpBar;
enum eItemType
{
	ITEM_HP,
	ITEM_MP,
};
typedef struct tagTileMoveInfo
{
	TileCell* tileCell;
	int distance;
}MoveInfo;

typedef struct tagSkillInfo
{
	eJobClass jobs;
	int number;
	int damage;
	std::string text;
	int frameX;
	int frameY;
}SkillInfo;

class GameSystem
	: public SingletonBase<GameSystem>
{
private:
	eItemType item;

	HpBar* hpBar;
	MpBar* mpBar;
	int hpDrinkCount;
	int mpDrinkCount;
private:
	MoveInfo moveInfo;
	SkillInfo skillInfo;
	POINT saveClickMousePos;
	TileCell* saveClickTile;
private:
	bool isAction;
	bool isMove;
	bool isAttacking;
	bool isSkilling;
	bool isHeal;
	bool isClickCharacter;
	int round;
	int currentCharacterIndex;

	int width;
	int height;
	int index;
	bool isItem;
	//std::list<TileInfo> moveTileList;
	TilePoint temp;
	eStateType eType;
	eJobClass playerJobType;
private:
	Map* g_Map;
	TileCell* targetTileCell;
private:
	std::map<int, SkillInfo> m_Skill;
	std::vector<TileInfo> g_TileAttackList;
	std::vector<Character*> characterList;

	std::vector<Character*> playerList;
	std::vector<Character*> monsterList;
	std::vector<Character*> npcList;

	std::queue<TileCell*> pathfindingQueue;

	std::list<MoveInfo> moveList;

	std::vector<Character*> selectTargetList;
	std::vector<Image*> characterSkillList;
	//std::map<std::pair<eJobClass, int>, std::vector<TileInfo>> m_playerSkill;
public:
	GameSystem();
	~GameSystem();
public:
	void Init();
	void Update();
	void Reset();
public:
	void SetMousePosition(LPARAM lParam);
	POINT GetMousePosition();
public:
	void ResetTarget();
	void SetMap(Map* _map);
	bool TargetCheck(std::vector<Component*> _list, Character* _character);
	void AddCharacterList(Character* _character);
	void GameTurn();
	eDirection LookAtCharacter(std::vector<Component*> _list, Character* _character);
	TileCell* FindPriorityTarget(Character* _character);
	std::list<MoveInfo> MaxMoveFinder(Character* _target);
	void ResetMovefinding();
	TileCell* CharacterPrioritySort(Character* _character);
	TileCell* CharacterSelectTileCell(Character* _character);
	bool AttackRangeCheck(Character* _character);
	void AddProioritySelectList(Character* _character);
	void SkillActivation();
	std::vector<Component*> SkillListTarget(std::vector<Component*> _list, Character* _character);
	bool GameOver();
	bool GameClear();
	Image* FindCharacterImage(int _index, Character* _character);
	void DeleteCharacter(Character* _character);
	bool SkillCheck(int _index);
	TileCell* NextTarget();
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
	std::vector<Image*> GetCharacterSkillList() { return characterSkillList; }
	void SetSkilling(bool _isSkill) { isSkilling = _isSkill; }
	bool IsSkilling() { return isSkilling; }
	bool IsHeal() { return isHeal; }
	void SetHeal(bool _isHeal) { isHeal = _isHeal; }
	std::vector<Character*> GetPlayerList() { return playerList; }
	std::vector<Character*> GetMonsterList() { return monsterList; }
	std::vector<Character*> GetNPCList() { return npcList; }

	void SetPlayerList(std::vector<Character*>  _player) { playerList = _player; }
	void SetMonsterList(std::vector<Character*>  _monster) { monsterList = _monster; }
	void SetNPCList(std::vector<Character*>  _npc) { npcList = _npc; }

	void AddPlayer(Character* _player) { playerList.push_back(_player); }
	void AddMonster(Character* _monster) { playerList.push_back(_monster); }
	void AddNPC(Character* _npc) { playerList.push_back(_npc); }
	void SetHpBar(HpBar* _hpBar) { hpBar = _hpBar; }
	void SetMpBar(MpBar* _mpBar) { mpBar = _mpBar; }
	bool IsClickCharacter() { return isClickCharacter; }
	TileCell* GetSaveClickTileCell() { return saveClickTile; }
	std::map<int, SkillInfo> GetSkillMap() { return m_Skill; }
	bool IsItem() { return isItem; }
	void SetItem(bool _isItem) { isItem = _isItem; }
	int GetHpDrinkCount(){ return hpDrinkCount; }
	int GetMpDrinkCount(){ return mpDrinkCount; }
	void SetHpDrinkCount(int _count) {hpDrinkCount = _count; }
	void SetMpDrinkCount(int _count) { mpDrinkCount = _count; }
	void SetItemType(eItemType _type) { item = _type; }
	eItemType GetItemType() { return item; }
};