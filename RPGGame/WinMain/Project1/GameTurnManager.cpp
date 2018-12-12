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
				}
				else
				{
					characterList[index + 1]->SetTurn(true);
					turnCharacter = characterList[index + 1];

				}


				break;
			}
		}
	}

	
	//
	eComponentType type = turnCharacter->GetComponetType();
	
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
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

}
