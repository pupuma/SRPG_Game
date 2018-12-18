#include "Game.h"

#include "GameTurnManager.h"

#include "Character.h"
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
