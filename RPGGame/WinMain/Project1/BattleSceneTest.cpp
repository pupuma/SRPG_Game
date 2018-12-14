#include "Game.h"
#include "BattleSceneTest.h"

#include "Character.h"
#include "Map.h"
#include "TileCell.h"

#include "ComponentSystem.h"

#include "Player.h"
#include "Monster.h"
#include "GameUI.h"

BattleSceneTest::BattleSceneTest()
{

}


BattleSceneTest::~BattleSceneTest()
{
	
}

bool BattleSceneTest::Init()
{
	gameUI = new GameUI();
	gameUI->Init();
#if defined(_DEBUG_TEST)
	{
		/*isTest = false;

		rcTopTimer = RectMake(552,0, 96, 96);
		rcTest1 = RectMake(11, 407, 252, 123);
		rcTest2 = RectMake(31, 533, 253, 253);
		rcTest3 = RectMake(320, 549, 140, 220);
		rcTest4 = RectMake(498, 549, 383, 220);
		rcTest5 = RectMake(535, 465, 130, 75);
		rcTest6 = RectMake(917, 533, 253, 253);
		rcTest7 = RectMake(937, 407, 252, 123);

		imgTest1 = IMAGEMANAGER->FindImage(TEXT("UI1"));
		imgTest2 = IMAGEMANAGER->FindImage(TEXT("UI2"));
		imgTest3 = IMAGEMANAGER->FindImage(TEXT("UI3"));
		imgTest4 = IMAGEMANAGER->FindImage(TEXT("UI4"));
		imgTest5 = IMAGEMANAGER->FindImage(TEXT("UI5"));
		imgTest6 = IMAGEMANAGER->FindImage(TEXT("UI2"));
		imgTest7 = IMAGEMANAGER->FindImage(TEXT("UI1"));


		rcButton1 = RectMake(326, 563, 131, 48);
		rcButton2 = RectMake(326, 611, 131, 48);
		rcButton3 = RectMake(326, 659, 131, 48);
		rcButton4 = RectMake(326, 707, 131, 48);

		imgSelectButton1 = IMAGEMANAGER->FindImage(TEXT("SelectButton"));
		imgSelectButton2 = IMAGEMANAGER->FindImage(TEXT("SelectButton"));
		imgSelectButton3 = IMAGEMANAGER->FindImage(TEXT("SelectButton"));
		imgSelectButton4 = IMAGEMANAGER->FindImage(TEXT("SelectButton"));

*/
	}
#endif//

	mapTest = new Map("Map");

	if (!mapTest->Init())
	{
		return false;
	}
	stageComponentList.push_back(mapTest);

	test = new Player("Test",1.5f);
	test->SetTurn(true);

	test->SetTilePosition(9, 9);

	if (!test->Init( ))
	{
		return false;
	}
	stageComponentList.push_back(test);

	//
	/*Character* test1 = new Player("1", 1.5f);
	test1->SetTurn(false);
	test1->SetTilePosition(8, 9);
	test1->Init();
	stageComponentList.push_back(test1);*/

	////
	//Character* test2 = new Player("2", 1.5f);
	//test2->SetTurn(false);
	//test2->SetTilePosition(10, 9);
	//test2->Init();
	////stageComponentList.push_back(test2);
	////
	//Character* test3 = new Player("3", 1.5f);
	//test3->SetTurn(false);
	//test3->SetTilePosition(9, 10);
	//test3->Init();
	////stageComponentList.push_back(test3);
	////
	//Character* test4 = new Player("4", 1.5f);
	//test4->SetTurn(false);
	//test4->SetTilePosition(9, 8);
	//test4->Init();
	////stageComponentList.push_back(test4);
	
	//test2 = new Player("Test2", 1.5f);
	//test2->SetTurn(false);
	//test2->SetTilePosition(6, 6);

	//if (!test2->Init())
	//{
	//	return false;
	//}
	//test2->ChangeState(eStateType::ST_IDLE);

	//stageComponentList.push_back(test2);


	// Monster
	Character* monster = new Monster("Monster", 1.5f);
	Character* monster1 = new Monster("Monster", 1.5f);
	Character* monster2 = new Monster("Monster", 1.5f);
	Character* monster3 = new Monster("Monster", 1.5f);
	Character* monster4 = new Monster("Monster", 1.5f);
	Character* monster5 = new Monster("Monster", 1.5f);
	Character* monster6 = new Monster("Monster", 1.5f);

	monster->SetTurn(false);
	monster->SetTilePosition(5, 6);

	if (!monster->Init())
	{
		return false;
	}
	if (!monster1->Init())
	{
		return false;
	}

	if (!monster2->Init())
	{
		return false;
	}

	if (!monster3->Init())
	{
		return false;
	}

	if (!monster4->Init())
	{
		return false;
	}

	if (!monster5->Init())
	{
		return false;
	}

	if (!monster6->Init())
	{
		return false;
	}

	monster1->SetTurn(false);
	monster1->SetTilePosition(6, 6);
	monster2->SetTurn(false);
	monster2->SetTilePosition(7, 6);
	monster3->SetTurn(false);
	monster3->SetTilePosition(8, 6);
	monster4->SetTurn(false);
	monster4->SetTilePosition(9, 6);
	monster5->SetTurn(false);
	monster5->SetTilePosition(10, 6);
	monster6->SetTurn(false);
	monster6->SetTilePosition(11, 6);



	stageComponentList.push_back(monster);
	//
	stageComponentList.push_back(monster1);
	stageComponentList.push_back(monster2);
	stageComponentList.push_back(monster3);
	stageComponentList.push_back(monster4);
	stageComponentList.push_back(monster5);
	stageComponentList.push_back(monster6);


	// Chacter
	GAMESYS->AddCharacterList(test);
	//GAMESYS->AddCharacterList(test2);
	GAMESYS->AddCharacterList(monster);
	GAMESYS->AddCharacterList(monster1);
	GAMESYS->AddCharacterList(monster2);
	GAMESYS->AddCharacterList(monster3);
	GAMESYS->AddCharacterList(monster4);
	GAMESYS->AddCharacterList(monster5);
	GAMESYS->AddCharacterList(monster6);


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

	if (KEYMANAGER->IsOnceKeyDown('1'))
	{
		//EFFECTMANAGER->Play(TEXT("Absorb"), 500, 500);
	}
	gameUI->Update();

	COMSYS->Update();
	//
	std::list< Component*>::iterator it;
	for(it = stageComponentList.begin(); it != stageComponentList.end(); it++)
	{
		(*it)->Update();
	}

	EFFECTMANAGER->Update();

#if defined(_DEBUG_TEST)
	
	
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

	gameUI->Render(hdc);

#if defined(_DEBUG_TEST)

	{
		std::string testStr;
		eStateType eType = GAMESYS->GetType();
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
	EFFECTMANAGER->Render(hdc);

	// RECT
	

#endif //
}
