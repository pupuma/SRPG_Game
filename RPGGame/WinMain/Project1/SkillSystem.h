#pragma once

class Character;

class SkillSystem
	: public SingletonBase<SkillSystem>
{
private:
	std::vector<TileInfo> skillRangeList;
	std::queue<TileCell*> pathfindingQueue;

	
private:
	TileCell* targetTileCell;
	int width;
	int height;
public:
	SkillSystem();
	~SkillSystem();
public:
	void Init();
public:
	std::vector<TileInfo> NomalSkillRange(Character* _character);
	std::vector<TileInfo> BoxSkillRange(Character* _character);
	std::vector<TileInfo> AllAttackSkillRange(Character* _character);
	std::vector<TileInfo> StraightAttackSkillRange(Character* _character);
	std::vector<TileInfo> BuffSkillRange(Character* _character);

};

