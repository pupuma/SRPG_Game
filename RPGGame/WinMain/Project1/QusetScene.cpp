#include "Game.h"
#include "QusetScene.h"
#include "EventSystem.h"

#include "Map.h"
#include "Character.h"
#include "Player.h"
#include "FontManager.h"

QusetScene::QusetScene()
{
	//player = NULL;
	map = NULL;
	EVENTSYS->SetNext(false);

}


QusetScene::~QusetScene()
{
}

bool QusetScene::Init()
{
	EventSystem::GetSingleton()->NextQusetNumber();
	EventSystem::GetSingleton()->SetGameType(eGameType::GT_EVENT);
	// map Parsing
	EVENTSYS->MapDataInit();
	frameX = 0;
	frameY = 0;
	map = new Map("Map");
	

	if (!map->Init())
	{
		return false;
	}
	stageComponentList.push_back(map);

	//

	// CharacterInit();
	EVENTSYS->QusetInit();
	
	playerList = EVENTSYS->GetPlayerList();
	monsterList = EVENTSYS->GetMonsterList();
	npcList = EVENTSYS->GetNPCList();

	//player = new Player(TEXT("Player"),0);
	//player->SetTilePosition(6, 8);

	//if (!player->Init())
	//{
	//	return false;
	//}

	//player->ChangeState(eStateType::ST_IDLE);
	if (!playerList.empty())
	{
		for (size_t i = 0; i < playerList.size(); i++)
		{
			stageComponentList.push_back(playerList[i]);
		}

		map->SetViewer(playerList[0]);
	}
	//stageComponentList.push_back(player);
	if (!monsterList.empty())
	{
		for (size_t i = 0; i < monsterList.size(); i++)
		{
			stageComponentList.push_back(monsterList[i]);
		}

	}

	if (!npcList.empty())
	{
		for (size_t i = 0; i < playerList.size(); i++)
		{
			stageComponentList.push_back(npcList[i]);
		}

		//map->SetViewer(npcList[0]);
	}
	//
	
	// 항상 0기준

	GAMESYS->SetMap(map);
	map->SortTile();

	//EVENTSYS->AddCharacterList(player);

	// 기본 세팅 
	rcTextBox = RectMake(100, 480, (WINSIZEX-200), 300);
	rcCharacterBox = RectMake(100, 180, 288, 288);
	rcNameBox = RectMake(1000, 410, 100, 50);
	rcDrawText = RectMake(120, 500, (WINSIZEX - 240), 260);
	EVENTSYS->SetEvent(true);

	deltaTime = 0.1f;
	count = 0;
	//bool test = EVENTSYS->IsEvent();

	
	//EVENTSYS->EventData();
	
	talkBox = IMAGEMANAGER->FindImage(TEXT("TextBox"));
	return true;
}

void QusetScene::Release()
{
	EVENTSYS->DeInit();
	map->Release();
	map = NULL;
	ComponentSystem::GetInstance()->Release();
	stageComponentList.clear();
}

void QusetScene::Update()
{

	{
		characterName = EVENTSYS->GetCharacterName();
		text = EVENTSYS->GetText();
		deltaTime -= TIMEMANAGER->GetElapsedTime();

	}

	
	if (KEYMANAGER->IsOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->ChangeScene(TEXT("QusetScene"));
		return;
	}


	if (!EVENTSYS->IsEvent())
	{
		if (EVENTSYS->GetBranch() == eBranch::B_BATTLE)
		{
			//EVENTSYS->SetNext(true);
			//EVENTSYS->SetEvent(false);
			//EVENTSYS->SetTextEnd(false);
			//EVENTSYS->SetBranch(eBranch::B_NONE);
			
		}
		
		EVENTSYS->Update();
		EVENTSYS->UpdateEvent(playerList[0]);
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

		img = EVENTSYS->FindFaceImg();
		

		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			if (EVENTSYS->GetQusetNumber() == EVENTSYS->GetSceneNumber())
			{
				if (EVENTSYS->GetBranch() == eBranch::B_TALK)
				{
					EVENTSYS->PopData();
					EVENTSYS->EventData();
					count = 0;
				}
			}
			
		}

		
	}

	if (EVENTSYS->IsNext())
	{
		EVENTSYS->ChangeScene();
		EVENTSYS->SetNext(false);
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
		//DrawObject(hdc, rcCharacterBox, 1, RGB(125, 0, 0), RECTANGLE);
		DrawObject(hdc, rcNameBox, 1, RGB(0, 0, 125), RECTANGLE);

		talkBox->Render(hdc, 100, 480);

		//
		FontManager::GetSingleton()->RenderTextBox(hdc, TEXT("NBG"), characterName, &rcNameBox, RGB(255, 255, 255));
		FontManager::GetSingleton()->RenderTextBox(hdc, TEXT("NBG"), count, text, &rcDrawText, RGB(255, 0, 0));
		if (deltaTime > 0)
		{
			//FontManager::GetSingleton()->RenderTextBox(hdc, TEXT("NBG"), text, &rcDrawText, RGB(100, 100, 100));
		}
		else
		{
			deltaTime = 0.1f;
			count++;
			if (text.size() <= count)
			{
				count = text.size();
				if (EVENTSYS->GetBranch() == eBranch::B_END)
				{
					EVENTSYS->SetTextEnd(true);
				}
				//EVENTSYS->EventData();
			}
			 
		}
		//FontManager::GetSingleton()->RenderTextBox(hdc, TEXT("NBG"), text, &rcDrawText, RGB(100, 100, 100));
		

		if (img != NULL)
		{
			img->FrameRender(hdc, rcCharacterBox.left,rcCharacterBox.top,EVENTSYS->GetBoxImgFrameX(), EVENTSYS->GetBoxImgFrameY());
		}
	}

	EVENTSYS->Render(hdc);
}
