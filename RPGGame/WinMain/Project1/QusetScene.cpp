#include "Game.h"
#include "QusetScene.h"
#include "EventSystem.h"

#include "Map.h"
#include "Character.h"
#include "Player.h"
#include "FontManager.h"

QusetScene::QusetScene()
{
}


QusetScene::~QusetScene()
{
}

bool QusetScene::Init()
{
	EventSystem::GetSingleton()->NextQusetNumber();
	EVENTSYS->SetGameType(eGameType::GT_EVENT);
	// 이미지 위에 ㄴㄴ


	// 컴포넌트 등록 

	// 이벤트 퀘스트 



	map = new Map("Map");

	if (!map->Init())
	{
		return false;
	}

	
	stageComponentList.push_back(map);
	
	player = new Player(TEXT("Player"),0);
	
	if (!player->Init())
	{
		return false;
	}

	player->SetTilePosition(6,8);
	player->ChangeState(eStateType::ST_IDLE);
	stageComponentList.push_back(player);

	map->SetViewer(player);
	GAMESYS->SetMap(map);
	map->SortTile();

	EVENTSYS->AddCharacterList(player);

	// 기본 세팅 
	rcTextBox = RectMake(100, 480, (WINSIZEX-200), 300);
	rcCharacterBox = RectMake(100, 180, 288, 288);
	rcNameBox = RectMake(1000, 410, 100, 50);
	rcDrawText = RectMake(120, 500, (WINSIZEX - 240), 260);
	EVENTSYS->SetEvent(false);
	return true;
}

void QusetScene::Release()
{
}

void QusetScene::Update()
{
	characterName = EVENTSYS->GetCharacterName();


	if (!EVENTSYS->IsEvent())
	{
		COMSYS->Update();
		EVENTSYS->UpdateEvent(player);

		//
		std::list< Component*>::iterator it;
		for (it = stageComponentList.begin(); it != stageComponentList.end(); it++)
		{
			(*it)->Update();
		}

	}
	else
	{
		// Evnet
		EVENTSYS->Update();
	}

	if (EVENTSYS->IsFadeOut())
	{
		SCENEMANAGER->ChangeScene(TEXT("BattleSceneTest"));
		EVENTSYS->SetEvent(false);
	}

}

void QusetScene::Render(HDC hdc)
{
	//
	{
		map->Render(hdc);
		
	}

	if (EVENTSYS->IsEvent())
	{
		DrawObject(hdc, rcTextBox, 1, RGB(125, 125, 125), RECTANGLE);
		DrawObject(hdc, rcDrawText, 1, RGB(0, 125, 0), RECTANGLE);
		DrawObject(hdc, rcCharacterBox, 1, RGB(125, 0, 0), RECTANGLE);
		DrawObject(hdc, rcNameBox, 1, RGB(0, 0, 125), RECTANGLE);


		//
		FontManager::GetSingleton()->RenderTextBox(hdc, TEXT("NBG"), characterName, &rcNameBox, RGB(255, 255, 255));
		//FontManager::GetSingleton()->RenderTextBox(hdc, TEXT("NBG"), text, &rcDrawText, RGB(255, 255, 255));
		
	}

	EVENTSYS->Render(hdc);
}
