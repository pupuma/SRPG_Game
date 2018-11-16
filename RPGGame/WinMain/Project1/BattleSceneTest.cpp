#include "Game.h"
#include "BattleSceneTest.h"

#include "Character.h"


BattleSceneTest::BattleSceneTest()
{
}


BattleSceneTest::~BattleSceneTest()
{
}

bool BattleSceneTest::Init()
{
	test = new Character("Test");
	test->Init();
	stageComponentList.push_back(test);
	return true;
}

void BattleSceneTest::Release()
{
}

void BattleSceneTest::Update()
{
	// 
	COMSYS->Update();
	//
	std::list< Component*>::iterator it;
	for(it = stageComponentList.begin(); it != stageComponentList.end(); it++)
	{
		(*it)->Update();
	}
}

void BattleSceneTest::Render(HDC hdc)
{
	std::list< Component*>::iterator it;
	for (it = stageComponentList.begin(); it != stageComponentList.end(); it++)
	{
		(*it)->Render(hdc);
	}
}
