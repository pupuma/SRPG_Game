#pragma once

class Character;
class Map;
class GameUI;

class BattleSceneTest
	: public GameNode
{
private:
	std::list<Component*> stageComponentList;
private:
	Character*	test;
	Character* test2;
	Map*		mapTest;
	GameUI*		gameUI;
private:
//#if defined(_DEBUG_TEST)
//	bool isTest;
//	RECT rcTopTimer;
//	RECT rcTest1;
//	RECT rcTest2;
//	RECT rcTest3;
//	RECT rcTest4;
//	RECT rcTest5;
//	RECT rcTest6;
//	RECT rcTest7;
//
//	RECT rcButton1;
//	RECT rcButton2;
//	RECT rcButton3;
//	RECT rcButton4;
//
//
//	Image* imgTest1;
//	Image* imgTest2;
//	Image* imgTest3;
//	Image* imgTest4;
//	Image* imgTest5;
//	Image* imgTest6;
//	Image* imgTest7;
//
//
//	Image* imgSelectButton1;
//	Image* imgSelectButton2;
//	Image* imgSelectButton3;
//	Image* imgSelectButton4;
//
//
//#endif//
public:
	BattleSceneTest();
	~BattleSceneTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

