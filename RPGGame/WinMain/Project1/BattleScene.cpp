#include "Game.h"
#include "BattleScene.h"

#include "Character.h"
#include "Map.h"
#include "TileCell.h"

#include "ComponentSystem.h"

#include "Player.h"
#include "Monster.h"
#include "GameUI.h"


BattleScene::BattleScene()
{

}


BattleScene::~BattleScene()
{
}

bool BattleScene::Init()
{
	//
	GAMESYS->Reset();
	EventSystem::GetSingleton()->SetGameType(eGameType::GT_BATTLE);
	//
	deltaTime = 1.5f;
	map = new Map("Map");

	if (!map->Init())
	{
		return false;
	}
	stageComponentList.push_back(map);


	EVENTSYS->QusetInit();

	playerList = EVENTSYS->GetPlayerList();
	monsterList = EVENTSYS->GetMonsterList();
	npcList = EVENTSYS->GetNPCList();

	GAMESYS->SetPlayerList(playerList);
	GAMESYS->SetMonsterList(monsterList);
	GAMESYS->SetNPCList(npcList);

	//playerList = GAMESYS->GetPlayerList();
	//monsterList = GAMESYS->GetMonsterList();
	//npcList = GAMESYS->GetNPCList();

	if (!playerList.empty())
	{
		for (size_t i = 0; i < playerList.size(); i++)
		{
			stageComponentList.push_back(playerList[i]);
			playerList[i]->SetTurn(false);
		}
		playerList[0]->ChangeState(eStateType::ST_PATH_IDLE);
		playerList[0]->SetTurn(true);
		map->SetViewer(playerList[0]);
	}
	if (!monsterList.empty())
	{
		for (size_t i = 0; i < monsterList.size(); i++)
		{
			monsterList[i]->SetTurn(false);
			stageComponentList.push_back(monsterList[i]);

		}

	}

	if (!npcList.empty())
	{
		for (size_t i = 0; i < npcList.size(); i++)
		{
			npcList[i]->SetTurn(false);
			stageComponentList.push_back(npcList[i]);

		}

	}
	//

	// 항상 0기준
	for (auto a : playerList)
	{
		GAMESYS->AddCharacterList(a);
	}

	for (auto a : monsterList)
	{
		GAMESYS->AddCharacterList(a);
	}
	GAMESYS->SetMap(map);
	gameUI = new GameUI();
	gameUI->Init();
	pause = false;
	return true;
}

void BattleScene::Release()
{
	gameUI->Release();
	SAFE_DELETE(gameUI);
	map->Release();
	delete map;
	map = NULL;
	ComponentSystem::GetInstance()->Release();
	stageComponentList.clear();

	playerList.clear();
	monsterList.clear();
	npcList.clear();
	
}

void BattleScene::Update()
{
	if (GAMESYS->GameOver())
	{
		pause = true;
		deltaTime -= TIMEMANAGER->GetElapsedTime();
		if (deltaTime <= 0)
		{
			SCENEMANAGER->ChangeScene(TEXT("TitleScene"));
			deltaTime = 1.5f;
			return;
		}
	}

	if (GAMESYS->GameClear())
	{
		pause = true;
		deltaTime -= TIMEMANAGER->GetElapsedTime();
		if (deltaTime <= 0)
		{
			deltaTime = 1.5f;
			if (EVENTSYS->GetQusetNumber() >= 4)
			{
				SCENEMANAGER->ChangeScene(TEXT("EndScene"));

			}
			else
			{
				SCENEMANAGER->ChangeScene(TEXT("QusetScene"));
				return;

			}
		}
	}
	gameUI->Update();

	COMSYS->Update();
	GAMESYS->Update();

	if (!pause)
	{
		//
		std::list< Component*>::iterator it;
		for (it = stageComponentList.begin(); it != stageComponentList.end(); it++)
		{
			(*it)->Update();
		}
	}
	

	EFFECTMANAGER->Update();


}

void BattleScene::Render(HDC hdc)
{
	{
		map->Render(hdc);

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
