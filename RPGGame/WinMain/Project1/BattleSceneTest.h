#pragma once

class Character;
class Map;
class BattleSceneTest
	: public GameNode
{
private:
	std::list<Component*> stageComponentList;
private:
	Character*	test;
	Map*		mapTest;
public:
	BattleSceneTest();
	~BattleSceneTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

