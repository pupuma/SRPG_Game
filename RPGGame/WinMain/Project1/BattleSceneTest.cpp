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
#if defined(_DEBUG_TEST)
	{
		isTest = true;

		rcTopTimer = RectMake(552,0, 96, 96);
		rcTest1 = RectMake(11, 407, 252, 123);
		rcTest2 = RectMake(31, 533, 253, 253);
		rcTest3 = RectMake(320, 549, 141, 220);
		rcTest4 = RectMake(498, 549, 383, 220);
		rcTest5 = RectMake(535, 465, 129, 75);
		rcTest6 = RectMake(917, 533, 253, 253);
		rcTest7 = RectMake(937, 407, 252, 123);
	}
#endif//

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
	//test->AttackPattern();

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
	
#if defined(_DEBUG_TEST)
	if (KEYMANAGER->IsOnceKeyDown('3'))
	{
		isTest = true;
	}
	if (KEYMANAGER->IsOnceKeyDown('4'))
	{
		isTest = false;
	}
#endif 
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


	// RECT
	if (isTest)
	{
		DrawObject(hdc, rcTopTimer, 1, RGB(255, 0, 0), RECTANGLE);
		DrawObject(hdc, rcTest1, 1, RGB(125, 0, 125), RECTANGLE);
		DrawObject(hdc, rcTest2, 1, RGB(125, 255, 125), RECTANGLE);
		DrawObject(hdc, rcTest3, 1, RGB(125, 125, 125), RECTANGLE);
		DrawObject(hdc, rcTest4, 1, RGB(125, 125, 125), RECTANGLE);
		DrawObject(hdc, rcTest5, 1, RGB(255, 255, 125), RECTANGLE);
		DrawObject(hdc, rcTest6, 1, RGB(125, 255, 125), RECTANGLE);
		DrawObject(hdc, rcTest7, 1, RGB(125, 0, 125), RECTANGLE);
	}

#endif //
}
