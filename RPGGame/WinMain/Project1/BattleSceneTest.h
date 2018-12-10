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
	Character* test2;
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

	Image* imgTest1;
	Image* imgTest2;
	Image* imgTest3;
	Image* imgTest4;
	Image* imgTest5;
	Image* imgTest6;
	Image* imgTest7;


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

