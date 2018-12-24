#include "Game.h"

#include "GameTurnManager.h"

#include "Character.h"
#include "Player.h"
#include "Map.h"
#include "ComponentSystem.h"


GameTurnManager::GameTurnManager()
{
}


GameTurnManager::~GameTurnManager()
{
}

void GameTurnManager::Init()
{
	// Character index Init
	characterIndex = 0;
}

void GameTurnManager::NextTurn()
{
	std::vector<Character*> characterList = GAMESYS->GetCharacterList();

	Character* turnCharacter = NULL;

	int index = 0;
	if (!characterList.empty())
	{
		for (size_t i = 0; i < characterList.size(); i++,index++)
		{
			if (characterList[index]->IsTurn())
			{
				if (characterList[index]->IsLive())
				{
					characterList[index]->SetTurn(false);
					if (index + 1 == characterList.size())
					{

						index = 0;
						characterList[index]->SetTurn(true);
						turnCharacter = characterList[index];
						characterIndex = 0;
					}
					else
					{
						characterList[index + 1]->SetTurn(true);
						turnCharacter = characterList[index + 1];
						characterIndex = index + 1;
					}

					break;
				}
				
			}
		}
	}

	
	//
	eComponentType type = turnCharacter->GetComponetType();
	
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	map->ResetAttackList();
	map->SetViewer(turnCharacter);

	switch (type)
	{
	case eComponentType::CT_PLAYER:
		turnCharacter->ChangeState(eStateType::ST_PATH_IDLE);
		break;
	case eComponentType::CT_MONSTER:
		turnCharacter->ChangeState(eStateType::ST_PATH_NAVI);
		break;
	case eComponentType::CT_NPC:
		break;
	}

	GAMESYS->SetMove(false);


	//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	//map->OpenListClear();
}

void GameTurnManager::AttackAction()
{
	std::vector<Character*> characterList = GAMESYS->GetCharacterList();


	Character* turnCharacter = NULL;

	int index = 0;
	if (!characterList.empty())
	{
		for (size_t i = 0; i < characterList.size(); i++, index++)
		{
			if (characterList[index]->IsTurn() && characterList[i]->GetComponetType() == eComponentType::CT_PLAYER)
			{
				characterList[index]->AttackPattern();
				break;
			}
		}
	}


}

bool GameTurnManager::PlayerTrun()
{
	std::vector<Character*> characterList = GAMESYS->GetCharacterList();

	if (characterList[characterIndex]->GetComponetType() == eComponentType::CT_PLAYER)
	{
		if (characterList[characterIndex]->GetType() == eStateType::ST_NONE || characterList[characterIndex]->GetType() == eStateType::ST_PATH_IDLE)
		{
			return true;
		}
	}
	return false;

}

bool GameTurnManager::MyTurn(TilePoint _pos)
{
	std::vector<Character*> characterList = GAMESYS->GetCharacterList();
	if (characterList[characterIndex]->GetTilePosition() == _pos)
	{
		return true;
	}
	return false;
}

void GameTurnManager::SkillAction(int _number)
{
	std::vector<Character*> characterList = GAMESYS->GetCharacterList();


	Character* turnCharacter = NULL;

	int index = 0;
	if (!characterList.empty())
	{
		for (size_t i = 0; i < characterList.size(); i++, index++)
		{
			if (characterList[index]->IsTurn() && characterList[i]->GetComponetType() == eComponentType::CT_PLAYER)
			{
				characterList[index]->SkillPattern(_number);
				break;
			}
		}
	}
}

Character * GameTurnManager::GetTurn()
{
	turnCharacter = NULL;
	std::vector<Character*> characterList = GAMESYS->GetCharacterList();
	for (auto a : characterList)
	{
		if (a->IsTurn())
		{
			turnCharacter = a;
			break;
		}
	}
	return turnCharacter;
}

Image * GameTurnManager::GetFaceImg()
{
	Image* img = NULL;
	if (turnCharacter != NULL)
	{
		if (turnCharacter->GetComponetType() == eComponentType::CT_PLAYER)
		{
			int number = turnCharacter->GetFaceNumber();
			switch (number)
			{
			case 1:
				img = IMAGEMANAGER->FindImage(TEXT("Actor1_Face"));
				break;
			case 2:
				img = IMAGEMANAGER->FindImage(TEXT("Actor2_Face"));
				break;
			case 3:
				img = IMAGEMANAGER->FindImage(TEXT("Actor3_Face"));
				break;
	
			}
		}
		else if (turnCharacter->GetComponetType() == eComponentType::CT_MONSTER)
		{
			int number = turnCharacter->GetFaceNumber();
			switch (number)
			{
			case 1:
				img = IMAGEMANAGER->FindImage(TEXT("Monster_Face"));

				break;
			case 2:
				img = IMAGEMANAGER->FindImage(TEXT("Monster_Face"));

				break;
			case 3:
				img = IMAGEMANAGER->FindImage(TEXT("Monster_Face"));
				break;

			}
		}
		else if (turnCharacter->GetComponetType() == eComponentType::CT_NPC)
		{
			int number = turnCharacter->GetFaceNumber();
			switch (number)
			{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;

			}
		}

	}
	return img;
}

Image * GameTurnManager::FindFaceImg(Character * _click)
{
	Image* img = NULL;
	if (_click != NULL)
	{
		if (_click->GetComponetType() == eComponentType::CT_PLAYER)
		{
			int number = _click->GetFaceNumber();
			switch (number)
			{
			case 1:
				img = IMAGEMANAGER->FindImage(TEXT("Actor1_Face"));
				break;
			case 2:
				img = IMAGEMANAGER->FindImage(TEXT("Actor2_Face"));
				break;
			case 3:
				img = IMAGEMANAGER->FindImage(TEXT("Actor3_Face"));
				break;

			}
		}
		else if (_click->GetComponetType() == eComponentType::CT_MONSTER)
		{
			int number = _click->GetFaceNumber();
			switch (number)
			{
			case 1:
				img = IMAGEMANAGER->FindImage(TEXT("Monster_Face"));

				break;
			case 2:
				img = IMAGEMANAGER->FindImage(TEXT("Monster_Face"));

				break;
			case 3:
				img = IMAGEMANAGER->FindImage(TEXT("Monster_Face"));
				break;

			}
		}
		else if (_click->GetComponetType() == eComponentType::CT_NPC)
		{
			int number = _click->GetFaceNumber();
			switch (number)
			{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;

			}
		}

	}
	return img;
}

std::string GameTurnManager::SkillText(int _index)
{
	Player* player = (Player*)GetTurn();
	std::map<int, SkillInfo> skillMap = GAMESYS->GetSkillMap();
	std::string str;
	for (auto a : skillMap)
	{
		if (a.second.jobs == player->GetJobs())
		{
			if (a.second.number == _index)
			{
				str = a.second.text;
				break;
			}
		}
	}

	return str;
}
