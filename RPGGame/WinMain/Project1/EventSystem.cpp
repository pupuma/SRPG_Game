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
	qusetNumber =0;
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

void EventSystem::Reset()
{
	//characterList.clear();
	//playerList.clear();
	monsterList.clear();
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
		PARSING->MapDataParsing(TEXT("Map_3"));
		break;
	case 4:
		PARSING->MapDataParsing(TEXT("Map_4"));
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
			playerList.clear();
			monsterList.clear();
			characterList.clear();

			Character* player = new Player(TEXT("취준생"), 0);
			player->SetTilePosition(6, 8);
			player->SetFrameX(0);
			player->SetFrameY(0);
			player->SetFaceFrameX(0);
			player->SetFaceFrameY(0);

			if (!player->Init(1))
			{
				return;
			}
			player->ChangeState(eStateType::ST_PATH_IDLE);
			AddCharacterList(player);
			playerList.push_back(player);
		}
		break;
		case 2:
		{
			playerList.clear();
			characterList.clear();
			monsterList.clear();
			Character* player = new Player(TEXT("취준생"), 0);
			player->SetTilePosition(0, 8);
			player->SetTurn(true);
			player->SetFrameX(1);
			player->SetFrameY(0);
			player->SetFaceFrameX(0);
			player->SetFaceFrameY(0);
			if (!player->Init(1))
			{
				return;
			}
			player->SetDirection(eDirection::DIR_RIGHT);
			player->ChangeState(eStateType::ST_PATH_IDLE);
			AddCharacterList(player);
			playerList.push_back(player);

			//GAMESYS->SetPlayerList(playerList);
			//GAMESYS->AddPlayer(player);
			//
			Character* slime1 = new Monster(TEXT("CompilEerror1"), 0);
			slime1->SetTilePosition(12, 8);
			slime1->SetFrameX(4);
			slime1->SetFrameY(0);
			if (!slime1->Init(1))
			{
				return;
			}
			

			slime1->SetFaceFrameX(1);
			slime1->SetAttackPoint(1000);
			slime1->SetDirection(eDirection::DIR_LEFT);
			slime1->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(slime1);
			monsterList.push_back(slime1);
			//GAMESYS->AddMonster(slime1);

			Character* slime2 = new Monster(TEXT("CompilEerror1"), 0);
			slime2->SetTilePosition(13, 7);
			slime2->SetFrameX(4);
			slime2->SetFrameY(0);
			if (!slime2->Init(1))
			{
				return;
			}
			
			slime2->SetAttackPoint(1000);

			slime2->SetFaceFrameX(1);

			slime2->SetDirection(eDirection::DIR_LEFT);
			slime2->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(slime2);
			monsterList.push_back(slime2);
			//GAMESYS->AddMonster(slime2);

			Character* slime3 = new Monster(TEXT("CompilEerror1"), 0);
			slime3->SetTilePosition(13, 9);
			slime3->SetFrameX(4);
			slime3->SetFrameY(0);
			if (!slime3->Init(1))
			{
				return;
			}
			slime3->SetFaceFrameX(1);
			slime3->SetDirection(eDirection::DIR_LEFT);
			slime3->ChangeState(eStateType::ST_PATH_NAVI);
		
			AddCharacterList(slime3);
			monsterList.push_back(slime3);
			//GAMESYS->AddMonster(slime3);

			//GAMESYS->SetMonsterList(monsterList);
		}
		break;
		case 3:
		{
			playerList.clear();
			characterList.clear();
			monsterList.clear();
			Character* player = new Player(TEXT("취준생"), 0);
			player->SetTilePosition(0, 5);
			player->SetTurn(true);
			player->SetFrameX(1);
			player->SetFrameY(0);
			player->SetFaceFrameX(0);
			player->SetFaceFrameY(0);

			if (!player->Init(1))
			{
				return;
			}
			player->SetDirection(eDirection::DIR_RIGHT);
			player->ChangeState(eStateType::ST_PATH_IDLE);
			AddCharacterList(player);
			playerList.push_back(player);


			Character* archer = new Player(TEXT("기획자"), 0);
			archer->SetTilePosition(4, 5);
			archer->SetTurn(false);
			archer->SetFrameX(7);
			archer->SetFrameY(4);
			archer->SetFaceFrameX(2);
			archer->SetFaceFrameY(1);

			if (!archer->Init(1))
			{
				return;
			}
			archer->SetJobs(eJobClass::JOB_ARCHER);
			archer->SetDirection(eDirection::DIR_RIGHT);
			archer->ChangeState(eStateType::ST_IDLE);
			AddCharacterList(archer);
			playerList.push_back(archer);


			Character* healer = new Player(TEXT("아티스트"), 0);
			healer->SetTilePosition(4, 4);
			healer->SetTurn(false);
			healer->SetFrameX(10);
			healer->SetFrameY(0);
			healer->SetFaceFrameX(3);
			healer->SetFaceFrameY(0);

			if (!healer->Init(1))
			{
				return;
			}
			healer->SetJobs(eJobClass::JOB_HEALER);
			healer->SetDirection(eDirection::DIR_RIGHT);
			healer->ChangeState(eStateType::ST_IDLE);
			AddCharacterList(healer);
			playerList.push_back(healer);
			
			//
			Character* oke1 = new Monster(TEXT("RunTimeError"), 0);
			oke1->SetTilePosition(17, 12);
			if (!oke1->Init(1))
			{
				return;
			}
			oke1->SetMaxHp(20);
			oke1->SetHp(20);

			oke1->SetDamagePoint(5);
			oke1->SetFrameX(7);
			oke1->SetFrameY(0);
			oke1->SetFaceFrameX(2);
			oke1->SetDirection(eDirection::DIR_LEFT);
			oke1->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke1);
			monsterList.push_back(oke1);
			//GAMESYS->AddMonster(slime1);

			Character* oke2 = new Monster(TEXT("RunTimeError"), 0);
			oke2->SetTilePosition(18, 12);
			if (!oke2->Init(1))
			{
				return;
			}
			oke2->SetHp(20);
			oke2->SetMaxHp(20);
			oke2->SetDamagePoint(5);
			oke2->SetFaceFrameX(2);
			oke2->SetFrameX(7);
			oke2->SetFrameY(0);
			oke2->SetDirection(eDirection::DIR_LEFT);
			oke2->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke2);
			monsterList.push_back(oke2);
			//GAMESYS->AddMonster(slime2);

			Character* oke3 = new Monster(TEXT("RunTimeError"), 0);
			oke3->SetTilePosition(18, 5);
			if (!oke3->Init(1))
			{
				return;
			}
			oke3->SetHp(20);
			oke3->SetMaxHp(20);
			oke3->SetDamagePoint(5);
			oke3->SetFaceFrameX(2);
			oke3->SetDirection(eDirection::DIR_LEFT);
			oke3->ChangeState(eStateType::ST_PATH_NAVI);
			oke3->SetFrameX(7);
			oke3->SetFrameY(0);
			AddCharacterList(oke3);
			monsterList.push_back(oke3);

			Character* oke4 = new Monster(TEXT("RunTimeError"), 0);
			oke4->SetTilePosition(18, 6);
			if (!oke4->Init(1))
			{
				return;
			}
			oke4->SetHp(20);
			oke4->SetMaxHp(20);
			oke4->SetDamagePoint(5);

			oke4->SetFaceFrameX(2);
			oke4->SetFrameX(7);
			oke4->SetFrameY(0);

			oke4->SetDirection(eDirection::DIR_LEFT);
			oke4->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke4);
			monsterList.push_back(oke4);

			Character* bat1 = new Monster(TEXT("C2065"), 0);
			bat1->SetTilePosition(18, 15);
			if (!bat1->Init(1))
			{
				return;
			}
			bat1->SetFaceFrameX(0);
			bat1->SetDirection(eDirection::DIR_LEFT);
			bat1->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(bat1);
			monsterList.push_back(bat1);

			Character* bat2 = new Monster(TEXT("C2065"), 0);
			bat2->SetTilePosition(18, 16);
			if (!bat2->Init(1))
			{
				return;
			}
			bat2->SetFrameX(1);
			bat2->SetFrameY(0);
			bat2->SetFaceFrameX(0);
			bat2->SetDirection(eDirection::DIR_LEFT);
			bat2->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(bat2);
			monsterList.push_back(bat2);

			
		}
			break;
		case 4:
		{
		

			playerList.clear();
			monsterList.clear();
			characterList.clear();

			Character* player = new Player(TEXT("취준생"), 0);
			player->SetTilePosition(3, 8);
			player->SetTurn(true);
			player->SetFrameX(1);
			player->SetFrameY(0);
			player->SetFaceFrameX(0);
			player->SetFaceFrameY(0);

			if (!player->Init(1))
			{
				return;
			}
			player->SetDirection(eDirection::DIR_RIGHT);
			player->ChangeState(eStateType::ST_PATH_IDLE);
			AddCharacterList(player);
			playerList.push_back(player);


			Character* archer = new Player(TEXT("기획자"), 0);
			archer->SetTilePosition(3, 9);
			archer->SetTurn(false);
			archer->SetFrameX(7);
			archer->SetFrameY(4);
			archer->SetFaceFrameX(2);
			archer->SetFaceFrameY(1);

			if (!archer->Init(1))
			{
				return;
			}
			archer->SetJobs(eJobClass::JOB_ARCHER);
			archer->SetDirection(eDirection::DIR_RIGHT);
			archer->ChangeState(eStateType::ST_IDLE);
			AddCharacterList(archer);
			playerList.push_back(archer);


			Character* healer = new Player(TEXT("아티스트"), 0);
			healer->SetTilePosition(3, 10);
			healer->SetTurn(false);
			healer->SetFrameX(10);
			healer->SetFrameY(0);
			healer->SetFaceFrameX(3);
			healer->SetFaceFrameY(0);

			if (!healer->Init(1))
			{
				return;
			}
			healer->SetJobs(eJobClass::JOB_HEALER);
			healer->SetDirection(eDirection::DIR_RIGHT);
			healer->ChangeState(eStateType::ST_IDLE);
			AddCharacterList(healer);
			playerList.push_back(healer);

			//
			Character* oke1 = new Monster(TEXT("LogicalError"), 0);
			oke1->SetTilePosition(12,7);
			if (!oke1->Init(1))
			{
				return;
			}
			oke1->SetMaxHp(20);
			oke1->SetHp(20);

			oke1->SetDamagePoint(5);
			oke1->SetFrameX(7);
			oke1->SetFrameY(0);
			oke1->SetFaceFrameX(2);
			oke1->SetDirection(eDirection::DIR_LEFT);
			oke1->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke1);
			monsterList.push_back(oke1);
			//GAMESYS->AddMonster(slime1);

			Character* oke2 = new Monster(TEXT("LogicalError"), 0);
			oke2->SetTilePosition(12, 8);
			if (!oke2->Init(1))
			{
				return;
			}
			oke2->SetHp(20);
			oke2->SetMaxHp(20);
			oke2->SetDamagePoint(5);
			oke2->SetFaceFrameX(2);
			oke2->SetFrameX(7);
			oke2->SetFrameY(0);
			oke2->SetDirection(eDirection::DIR_LEFT);
			oke2->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke2);
			monsterList.push_back(oke2);
			//GAMESYS->AddMonster(slime2);

			Character* oke3 = new Monster(TEXT("LogicalError"), 0);
			oke3->SetTilePosition(12, 9);
			if (!oke3->Init(1))
			{
				return;
			}
			oke3->SetHp(20);
			oke3->SetMaxHp(20);
			oke3->SetDamagePoint(5);
			oke3->SetFaceFrameX(2);
			oke3->SetDirection(eDirection::DIR_LEFT);
			oke3->ChangeState(eStateType::ST_PATH_NAVI);
			oke3->SetFrameX(7);
			oke3->SetFrameY(0);
			AddCharacterList(oke3);
			monsterList.push_back(oke3);

			Character* oke4 = new Monster(TEXT("LogicalError"), 0);
			oke4->SetTilePosition(12, 10);
			if (!oke4->Init(1))
			{
				return;
			}
			oke4->SetHp(20);
			oke4->SetMaxHp(20);
			oke4->SetDamagePoint(5);

			oke4->SetFaceFrameX(2);
			oke4->SetFrameX(7);
			oke4->SetFrameY(0);

			oke4->SetDirection(eDirection::DIR_LEFT);
			oke4->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke4);
			monsterList.push_back(oke4);


			Character* oke5 = new Monster(TEXT("LogicalError"), 0);
			oke5->SetTilePosition(7, 13);
			if (!oke5->Init(1))
			{
				return;
			}
			oke5->SetHp(20);
			oke5->SetMaxHp(20);
			oke5->SetDamagePoint(5);

			oke5->SetFaceFrameX(2);
			oke5->SetFrameX(7);
			oke5->SetFrameY(0);

			oke5->SetDirection(eDirection::DIR_LEFT);
			oke5->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke5);
			monsterList.push_back(oke5);

			Character* oke6 = new Monster(TEXT("LogicalError"), 0);
			oke6->SetTilePosition(8, 13);
			if (!oke6->Init(1))
			{
				return;
			}
			oke6->SetHp(20);
			oke6->SetMaxHp(20);
			oke6->SetDamagePoint(5);
			
			oke6->SetFaceFrameX(2);
			oke6->SetFrameX(7);
			oke6->SetFrameY(0);

			oke6->SetDirection(eDirection::DIR_LEFT);
			oke6->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke6);
			monsterList.push_back(oke6);

			Character* oke7 = new Monster(TEXT("LogicalError"), 0);
			oke7->SetTilePosition(9, 13);
			if (!oke7->Init(1))
			{
				return;
			}
			oke7->SetHp(20);
			oke7->SetMaxHp(20);
			oke7->SetDamagePoint(5);

			oke7->SetFaceFrameX(2);
			oke7->SetFrameX(7);
			oke7->SetFrameY(0);

			oke7->SetDirection(eDirection::DIR_LEFT);
			oke7->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke7);
			monsterList.push_back(oke7);

			Character* oke8 = new Monster(TEXT("LogicalError"), 0);
			oke8->SetTilePosition(10, 13);
			if (!oke8->Init(1))
			{
				return;
			}
			oke8->SetHp(20);
			oke8->SetMaxHp(20);
			oke8->SetDamagePoint(5);

			oke8->SetFaceFrameX(2);
			oke8->SetFrameX(7);
			oke8->SetFrameY(0);

			oke8->SetDirection(eDirection::DIR_LEFT);
			oke8->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke8);
			monsterList.push_back(oke8);

			Character* oke9 = new Monster(TEXT("LogicalError"), 0);
			oke9->SetTilePosition(8,4);
			if (!oke9->Init(1))
			{
				return;
			}
			oke9->SetHp(20);
			oke9->SetMaxHp(20);
			oke9->SetDamagePoint(5);

			oke9->SetFaceFrameX(2);
			oke9->SetFrameX(7);
			oke9->SetFrameY(0);

			oke9->SetDirection(eDirection::DIR_LEFT);
			oke9->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke9);
			monsterList.push_back(oke9);

			Character* oke10 = new Monster(TEXT("LogicalError"), 0);
			oke10->SetTilePosition(9, 4);
			if (!oke10->Init(1))
			{
				return;
			}
			oke10->SetHp(20);
			oke10->SetMaxHp(20);
			oke10->SetDamagePoint(5);

			oke10->SetFaceFrameX(2);
			oke10->SetFrameX(7);
			oke10->SetFrameY(0);

			oke10->SetDirection(eDirection::DIR_LEFT);
			oke10->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke10);
			monsterList.push_back(oke10);

			Character* oke11 = new Monster(TEXT("LogicalError"), 0);
			oke11->SetTilePosition(10, 4);
			if (!oke11->Init(1))
			{
				return;
			}
			oke11->SetHp(20);
			oke11->SetMaxHp(20);
			oke11->SetDamagePoint(5);

			oke11->SetFaceFrameX(2);
			oke11->SetFrameX(7);
			oke11->SetFrameY(0);

			oke11->SetDirection(eDirection::DIR_LEFT);
			oke11->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke11);
			monsterList.push_back(oke11);

			Character* oke12 = new Monster(TEXT("LogicalError"), 0);
			oke12->SetTilePosition(11, 4);
			if (!oke12->Init(1))
			{
				return;
			}
			oke12->SetHp(20);
			oke12->SetMaxHp(20);
			oke12->SetDamagePoint(5);

			oke12->SetFaceFrameX(2);
			oke12->SetFrameX(7);
			oke12->SetFrameY(0);

			oke12->SetDirection(eDirection::DIR_LEFT);
			oke12->ChangeState(eStateType::ST_PATH_NAVI);
			AddCharacterList(oke12);
			monsterList.push_back(oke12);

		}

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
			playerList[0]->ChangeState(eStateType::ST_PATH_IDLE);

			
		}
		break;
		case 2:
		{
			playerList[0]->SetTilePosition(0, 8);
			playerList[0]->ChangeState(eStateType::ST_PATH_IDLE);

			monsterList[0]->SetTilePosition(12, 8);

			monsterList[1]->SetTilePosition(13, 7);

			monsterList[2]->SetTilePosition(13, 9);
		
		}
		break;
		case 3:
			playerList[0]->SetTilePosition(0, 5);
			playerList[0]->ChangeState(eStateType::ST_PATH_IDLE);

			playerList[1]->SetTilePosition(4, 5);
			playerList[1]->SetDamagePoint(8);
			playerList[1]->SetMaxHp(80);
			playerList[1]->SetHp(80);

			playerList[2]->SetTilePosition(4,4);
			playerList[2]->SetDamagePoint(5);
			playerList[2]->SetMaxHp(50);
			playerList[2]->SetHp(50);

			monsterList[0]->SetTilePosition(17, 12);
			monsterList[1]->SetTilePosition(18, 12);
			monsterList[2]->SetTilePosition(18, 5);
			monsterList[3]->SetTilePosition(18, 6);
			monsterList[4]->SetTilePosition(18, 15);
			monsterList[5]->SetTilePosition(18, 16);

			break;
		case 4:
			playerList[0]->SetTilePosition(3, 8);
			playerList[0]->ChangeState(eStateType::ST_PATH_IDLE);

			playerList[1]->SetTilePosition(3,9);
			playerList[1]->SetDamagePoint(8);
			playerList[1]->SetMaxHp(80);
			playerList[1]->SetHp(80);

			playerList[2]->SetTilePosition(3, 10);
			playerList[2]->SetDamagePoint(5);
			playerList[2]->SetMaxHp(50);
			playerList[2]->SetHp(50);

			monsterList[0]->SetTilePosition(12, 7);
			monsterList[0]->SetDamagePoint(10);

			monsterList[1]->SetTilePosition(12, 8);
			monsterList[1]->SetDamagePoint(10);

			monsterList[2]->SetTilePosition(12, 9);
			monsterList[2]->SetDamagePoint(10);
			monsterList[3]->SetTilePosition(12, 10);
			monsterList[3]->SetDamagePoint(10);

			monsterList[4]->SetTilePosition(7, 13);
			monsterList[4]->SetDamagePoint(10);
			monsterList[5]->SetTilePosition(8, 13);
			monsterList[5]->SetDamagePoint(10);
			monsterList[6]->SetTilePosition(9, 13);
			monsterList[6]->SetDamagePoint(10);
			monsterList[7]->SetTilePosition(10, 13);
			monsterList[7]->SetDamagePoint(10);



			monsterList[8]->SetTilePosition(8, 4);
			monsterList[8]->SetDamagePoint(10);
			monsterList[9]->SetTilePosition(9, 4);
			monsterList[9]->SetDamagePoint(10);
			monsterList[10]->SetTilePosition(10, 4);
			monsterList[10]->SetDamagePoint(10);
			monsterList[11]->SetTilePosition(11, 4);
			monsterList[11]->SetDamagePoint(10);


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
	break;
	case 3:
	{
		if (branch == eBranch::B_NONE)
		{
			isFadeOut = true;
			isFadeIn = false;
		}
	}
	break;
	case 4:
	{
		if (branch == eBranch::B_NONE)
		{
			isFadeOut = true;
			isFadeIn = false;
		}
	}
	break;
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
		return characterList[charIndex]->GetName();
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
	charIndex = atoi(token);
	token = strtok(NULL, ",");
	text = token;
	token = strtok(NULL, ",");
	fileName = token;
	token = strtok(NULL, ",");
	frameX = atoi(token);
	token = strtok(NULL, ",");
	frameY = atoi(token);

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
		PopData();
		SetNext(false);
		SetGameType(eGameType::GT_BATTLE);
		SetEvent(false);
		isFadeOut = false;
		isFadeIn = true;
		SCENEMANAGER->ChangeScene(TEXT("BattleScene"));
		break;
	case 4:
		PopData();
		SetNext(false);
		SetGameType(eGameType::GT_BATTLE);
		SetEvent(false);
		isFadeOut = false;
		isFadeIn = true;

		SCENEMANAGER->ChangeScene(TEXT("BattleScene"));
		GAMESYS->SetItem(true);
		GAMESYS->SetMpDrinkCount(2);
		GAMESYS->SetHpDrinkCount(2);
		break;
	case 5:
		PopData();
		SetNext(false);
		SetGameType(eGameType::GT_NONE);
		SetEvent(false);
		isFadeOut = false;
		isFadeIn = true;

		SCENEMANAGER->ChangeScene(TEXT("EndScene"));
		
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
