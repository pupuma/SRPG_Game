#include "Game.h"
#include "EventSystem.h"

#include "Character.h"
#include "ParsingSystem.h"

#include "Player.h"
#include "Monster.h"
#include "NPC.h"
EventSystem::EventSystem()
{
}


EventSystem::~EventSystem()
{
}

void EventSystem::Init()
{
	qusetNumber = 0;
	index = 0;
	textIndex = 0;
	deltaTime = 0.5f;
	type = eGameType::GT_NONE;
	isEvent = true;
	isFadeIn = false;
	isFadeOut = false;
	isTextEnd = false;
	isTextStart = false;
	isEventStart = false;
	isEvnetEnd = false;
	isNext = false;
	fadeImg = IMAGEMANAGER->FindImage(TEXT("Background"));
	q_Data = ParsingSystem::GetSingleton()->GetTalkString();
	branch = eBranch::B_NONE;
}

void EventSystem::Update()
{
	if (iSceneNumber == qusetNumber)
	{
		if (eBranch::B_END == branch)
		{
			if (isTextEnd)
			{
				isEvent = false;
				isTextEnd = false;
				branch = B_NONE;
			}
		}
	}
	else
	{
	/*	deltaTime -= TIMEMANAGER->GetElapsedTime();

		colorKey += 3;
		if (colorKey >= 255)
		{
			colorKey = 255;
			isFadeOut = true;
		}
*/
	}



	if (isFadeOut)
	{
		deltaTime = 0.5f;
		colorKey += 3;
		if (colorKey >= 255)
		{
			colorKey = 255;
			isNext = true;
		}
	}

	if (isFadeIn)
	{
		deltaTime = 0.5f;
		colorKey -= 3;
		if (colorKey <= 0)
		{
			colorKey = 0;
		}
	}

}

void EventSystem::Render(HDC hdc)
{
	if (isFadeOut == true)
	{
		FadeOut(hdc);
	}
	else if (isFadeIn == true)
	{
		FadeIn(hdc);
	}
}

void EventSystem::DeInit()
{
	if (type == eGameType::GT_EVENT)
	{
		for (auto a : playerList)
		{
			delete a;
		}
		playerList.clear();

		for (auto a : monsterList)
		{
			a = NULL;
			delete a;

		}
		monsterList.clear();

		for (auto a : npcList)
		{
			delete a;

		}
		npcList.clear();


		characterList.clear();
	}
	
}

void EventSystem::MapDataInit()
{
	switch (qusetNumber)
	{
	case 1:
		PARSING->MapDataParsing(TEXT("Map_2"));
		break;
	case 2:
		PARSING->MapDataParsing(TEXT("Map_1"));
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	}
	isEvent = true;
}

void EventSystem::QusetInit()
{
	if (type == eGameType::GT_EVENT)
	{
		switch (qusetNumber)
		{
		case 1:
		{
			Character* player = new Player(TEXT("Player"), 0);
			player->SetTilePosition(6, 8);
			if (!player->Init(1))
			{
				return;
			}
			player->ChangeState(eStateType::ST_IDLE);
			AddCharacterList(player);
			playerList.push_back(player);
		}
		break;
		case 2:
		{
			Character* player = new Player(TEXT("Player"), 0);
			player->SetTilePosition(0, 8);
			player->SetTurn(true);

			if (!player->Init(1))
			{
				return;
			}
			player->SetDirection(eDirection::DIR_RIGHT);
			player->ChangeState(eStateType::ST_IDLE);
			AddCharacterList(player);
			playerList.push_back(player);

			//GAMESYS->SetPlayerList(playerList);
			//GAMESYS->AddPlayer(player);
			//
			Character* slime1 = new Monster(TEXT("CompilEerror1"), 0);
			slime1->SetTilePosition(12, 8);
			if (!slime1->Init(1))
			{
				return;
			}
			slime1->SetFaceFrameX(4);
			slime1->SetDirection(eDirection::DIR_LEFT);
			slime1->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(slime1);
			monsterList.push_back(slime1);
			//GAMESYS->AddMonster(slime1);
			Character* slime2 = new Monster(TEXT("CompilEerror1"), 0);
			slime2->SetTilePosition(13, 7);
			if (!slime2->Init(1))
			{
				return;
			}
			slime2->SetFaceFrameX(4);

			slime2->SetDirection(eDirection::DIR_LEFT);
			slime2->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(slime2);
			monsterList.push_back(slime2);
			//GAMESYS->AddMonster(slime2);

			Character* slime3 = new Monster(TEXT("CompilEerror1"), 0);
			slime3->SetTilePosition(13, 9);
			if (!slime3->Init(1))
			{
				return;
			}
			slime3->SetFaceFrameX(4);
			slime3->SetDirection(eDirection::DIR_LEFT);
			slime3->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(slime3);
			monsterList.push_back(slime3);
			//GAMESYS->AddMonster(slime3);

			//GAMESYS->SetMonsterList(monsterList);
		}
		break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		}
	}
	else if (type == eGameType::GT_BATTLE)
	{
		switch (qusetNumber)
		{
		case 1:
		{
			playerList[0]->SetTilePosition(0, 8);
			for (auto a : playerList)
			{
				a->Init();
				a->ChangeState(eStateType::ST_IDLE);
			}

		}
		break;
		case 2:
		{
			playerList[0]->SetTilePosition(0, 8);
			playerList[0]->Init(1);
			playerList[0]->SetTurn(true);
			playerList[0]->SetFaceFrameX(4);
			playerList[0]->ChangeState(eStateType::ST_IDLE);
			/*if (playerList.size() >= 2)
			{
				for (size_t i = 1; i < playerList.size(); i++)
				{
					playerList[i]->Init(1);

				}
				for (auto a : playerList)
				{
					a->Init(1);
					a->ChangeState(eStateType::ST_IDLE);
				}
			}*/
			

			//
			monsterList[0]->SetTilePosition(12, 8);
			monsterList[0]->Init(1);
			monsterList[0]->SetFaceFrameX(4);
			monsterList[0]->SetDirection(eDirection::DIR_LEFT);
			monsterList[0]->ChangeState(eStateType::ST_PATH_NAVI);

			monsterList[1]->SetTilePosition(13, 7);
			monsterList[1]->Init(1);
			monsterList[1]->SetFaceFrameX(4);
			monsterList[1]->SetDirection(eDirection::DIR_LEFT);
			monsterList[1]->ChangeState(eStateType::ST_PATH_NAVI);

			monsterList[2]->SetTilePosition(13, 9);
			monsterList[2]->Init(1);
			monsterList[2]->SetFaceFrameX(4);

			monsterList[2]->SetDirection(eDirection::DIR_LEFT);
			monsterList[2]->ChangeState(eStateType::ST_PATH_NAVI);


		
		}
		break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		}
	}
	

	
	EventData();
}

void EventSystem::UpdateEvent(Character* _player)
{
	switch (qusetNumber)
	{
	case 1:
	{
		if (_player->GetTilePosition().x >= 24)
		{
			isFadeOut = true;
			isFadeIn = false;
			_player->ChangeState(eStateType::ST_IDLE);
		}
	}
		break;
	case 2:
	{
		if (branch == eBranch::B_NONE)
		{
			isFadeOut = true;
			isFadeIn = false;

		}
	}
	}
}

void EventSystem::NextQusetNumber()
{
	qusetNumber += 1;
}

int EventSystem::GetPlayerCount()
{
	switch (qusetNumber)
	{
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 3;
		break;
	case 5:
		return 3;
		break;
	}
	return 0;
}

int EventSystem::GetNPCCount()
{
	switch (qusetNumber)
	{
	case 1:
		return 0;

		break;
	case 2:
		return 0;

		break;
	case 3:
		return 1;

		break;
	case 4:
		return 0;

		break;
	case 5:
		return 0;

		break;
	}
	return 0;
}

int EventSystem::GetMonsterCount()
{
	switch (qusetNumber)
	{
	case 1:
		return 1;

		break;
	case 2:
		return 3;

		break;
	case 3:
		return 3;

		break;
	case 4:
		return 5;

		break;
	case 5:
		return 7;

		break;
	}
	return 0;
}

void EventSystem::FadeIn(HDC hdc)
{
	fadeImg->AlphaRender(hdc, colorKey);
}

void EventSystem::FadeOut(HDC hdc)
{
	fadeImg->AlphaRender(hdc, colorKey);
}

std::string EventSystem::GetCharacterName()
{
	if (!characterList.empty())
	{
		return characterList[index]->GetName();
	}

	std::string str = TEXT("...");
	return str;
}

void EventSystem::AddCharacterList(Character * _character)
{
	characterList.push_back(_character);
}

void EventSystem::EventData()
{
	if (q_Data.empty())
	{
		return;
	}
	std::string strText = q_Data.front();
	
	TCHAR record[1000];
	TCHAR* token;
	std::string tempText;

	strcpy_s(record, strText.c_str());
	token = strtok(record, ",");
	iSceneNumber = atol(token);
	token = strtok(NULL, ",");
	branch = (eBranch)atoi(token);
	token = strtok(NULL, ",");
	charIndex = atol(token);
	token = strtok(NULL, ",");
	text = token;
	token = strtok(NULL, ",");
	fileName = token;
	token = strtok(NULL, ",");
	frameX = atol(token);
	token = strtok(NULL, ",");
	frameY = atol(token);

	//textIndex++;
	//if (textIndex <= tempText.size() - 1)
	//{
	//	textIndex = 0;
	//	//q_Data.pop();
	//	text = "";
	//}
}

void EventSystem::PopData()
{
	if(!q_Data.empty())
	{ 
		q_Data.pop(); 
	}

}

void EventSystem::ChangeScene()
{
	switch (qusetNumber)
	{
	case 1:
		PopData();
		SetNext(false);

		SCENEMANAGER->ChangeScene(TEXT("QusetScene"));
		SetEvent(true);
		SetGameType(eGameType::GT_EVENT);
		isFadeOut = false;
		isFadeIn = true;
		break;
	case 2:
		PopData();
		SetNext(false);
		SetGameType(eGameType::GT_BATTLE);
		SetEvent(false);
		isFadeOut = false;
		isFadeIn = true;
		SCENEMANAGER->ChangeScene(TEXT("BattleScene"));
		
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}

}

Image * EventSystem::FindFaceImg()
{
	Image* img = NULL;
	if (type == eGameType::GT_EVENT)
	{
		int number = characterList[charIndex]->GetFaceNumber();
		switch (number)
		{
		case 1:
			img = IMAGEMANAGER->FindImage(TEXT("Actor1_Face_B"));
			break;
		case 2:
			img = IMAGEMANAGER->FindImage(TEXT("Actor2_Face_B"));
			break;
		case 3:
			img = IMAGEMANAGER->FindImage(TEXT("Actor3_Face_B"));
			break;
		default:
			break;
		}
	}
	
	return img;
}
