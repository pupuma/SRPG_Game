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
private:
#if defined(_DEBUG_TEST)
	bool isTest;
	RECT rcTopTimer;
	RECT rcTest1;
	RECT rcTest2;
	RECT rcTest3;
	RECT rcTest4;
	RECT rcTest5;
	RECT rcTest6;
	RECT rcTest7;

#endif//
public:
	BattleSceneTest();
	~BattleSceneTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

