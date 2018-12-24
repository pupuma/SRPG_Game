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
	EVENTSYS->SetGameType(eGameType::GT_BATTLE);
	
	mapTest = new Map("Map");

	if (!mapTest->Init())
	{
		return false;
	}
	stageComponentList.push_back(mapTest);

	test = new Player("Test",1.5f);
	test->SetTurn(true);

	test->SetTilePosition(11, 9);

	if (!test->Init(1))
	{
		return false;
	}
	stageComponentList.push_back(test);

	Character* test2 = new Player("Test", 1.5f);
	test2->SetTurn(true);
		
	test2->SetTilePosition(10, 9);

	if (!test2->Init(2))
	{
		return false;
	}
	stageComponentList.push_back(test2);

	

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

	if (!monster->Init(1))
	{
		return false;
	}
	if (!monster1->Init(1))
	{
		return false;
	}

	if (!monster2->Init(1))
	{
		return false;
	}

	if (!monster3->Init(1))
	{
		return false;
	}

	if (!monster4->Init(1))
	{
		return false;
	}

	if (!monster5->Init(2))
	{
		return false;
	}

	if (!monster6->Init(2))
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
	GAMESYS->AddCharacterList(test2);
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

	gameUI = new GameUI();
	gameUI->Init();


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
	GAMESYS->Update();
	//
	std::list< Component*>::iterator it;
	for(it = stageComponentList.begin(); it != stageComponentList.end(); it++)
	{
		(*it)->Update();
	}

	EFFECTMANAGER->Update();

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
