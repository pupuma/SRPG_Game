#pragma once

class Character;
class BattleSceneTest
	: public GameNode
{
private:
	std::list<Component*> stageComponentList;
private:
	Character* test;
public:
	BattleSceneTest();
	~BattleSceneTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

