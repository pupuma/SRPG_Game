#include "Game.h"
#include "BattleSceneTest.h"

#include "Character.h"
#include "Map.h"
#include "TileCell.h"

#include "ComponentSystem.h"

//
#include "Player.h"
#include "Monster.h"

BattleSceneTest::BattleSceneTest()
{
}


BattleSceneTest::~BattleSceneTest()
{
}

bool BattleSceneTest::Init()
{
	{
	}

	mapTest = new Map("Map");
	if (!mapTest->Init())
	{
		return false;
	}
	stageComponentList.push_back(mapTest);

	test = new Player("Test",1.5f);
	if (!test->Init( ))
	{
		return false;
	}

	stageComponentList.push_back(test);
	
	// Monster
	Character* monster = new Monster("Monster", 1.5f);
	if (!monster->Init())
	{
		return false;
	}
	stageComponentList.push_back(monster);

	//Viewer 
	
	mapTest->SetViewer(test);
	//
	//
	
	mapTest->SortTile();

	// Test
	GAMESYS->SetMap(mapTest);
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
	//{
	//	std::list< Component*>::iterator it;
	//	for (it = stageComponentList.begin(); it != stageComponentList.end(); it++)
	//	{
	//		(*it)->Render(hdc);
	//	}
	//}
	
	{
		mapTest->Render(hdc);
		
	}

#if defined(_DEBUG_TEST)
	{
		std::string testStr;
		eStateType eType = test->GetType();
		switch (eType)
		{
		case eStateType::ST_NONE:
			testStr = TEXT("State : STATE_NONE");
			break;
		case eStateType::ST_IDLE:
			testStr = TEXT("State : STATE_IDLE");
			break;
		case eStateType::ST_MOVE:
			testStr = TEXT("State : STATE_MOVE");
			break;
		case eStateType::ST_ATTACK:
			testStr = TEXT("State : STATE_ATTACK");
			break;
		case eStateType::ST_DEFENSE:
			testStr = TEXT("State : STATE_DEFFENSE");
			break;
		case eStateType::ST_DEAD:
			testStr = TEXT("State : STATE_DEAD");
		case eStateType::ST_PATHFINDING:
			testStr = TEXT("State : ST_PATHFINDING");
			break;
		case eStateType::ST_PATH_IDLE:
			testStr = TEXT("State : ST_PATH_IDLE");
			break;
		case eStateType::ST_PATH_MOVE:
			testStr = TEXT("State : ST_PATH_MOVE");
			break;

		}
		TextOut(hdc, 10, 10, testStr.c_str(), testStr.length());
	}
#endif //
}
