#include "Game.h"

#include "NavigationState.h"
#include "Character.h"
#include "TileCell.h"
#include "Map.h"
#include "GameTurnManager.h"

NavigationState::NavigationState(Character* _character)
	: State(_character)
{
}


NavigationState::~NavigationState()
{
}

void NavigationState::Start()
{
	State::Start();
	isNavi = false;
	deltaTime = 1.f;

	

	if (GAMESYS->GetTargetTileCell() != NULL)
	{
		isNavi = true;
	}
	else
	{
		GAMESYS->AddProioritySelectList(character);
	}
	// 적을 탐색 한다. ( 우선순위로 하는 적 탐색 ) 
	
	// 이동 -> Move
}

void NavigationState::Update()
{
	State::Update();

	{
		if (eStateType::ST_NONE != nextState)
		{
			character->ChangeState(nextState);
#if defined(_DEBUG_TEST)
			character->SetStateType(nextState);
			GAMESYS->SetType(character->GetType());
#endif // 
			return;
		}
	}
	

	if (character->IsTurn() == false)
	{
		return;
	}



	deltaTime -= TIMEMANAGER->GetElapsedTime();

	if (deltaTime < 0)
	{
		deltaTime = 1.f;
		// 내 공격 범위 안에 적이 있을 경우 
		if (GAMESYS->AttackRangeCheck(character))
		{
			// Character에 자기의 타겟을 저장 시킨다. 
			// TileCell* tileCell = GAMESYS->GetTargetTileCell();
			TileCell* tileCell = character->GetTargetCharacterTileCell();
			Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
			if (NULL != tileCell)
			{
				tileCell->IsCharacter(true);
				std::vector<Component*> targetList = map->GetComponentList(tileCell);



				if (0 < targetList.size())
				{
					character->SetTarget(targetList);
					nextState = eStateType::ST_ATTACK;
				}
			}
		}
		else
		{
			// 공격 범위에 없다면... 이동 범위에 있는지 체크한다. 

			
			TileCell* targetMoveCell = GAMESYS->FindPriorityTarget(character);
			character->SetTargetTileCell(targetMoveCell);

			if (NULL != targetMoveCell)
			{
				Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

				TileCell* tileCell = map->FindTileCell(character->GetTilePosition());
				tileCell->IsCharacter(false);
				character->AttackPattern();
				nextState = eStateType::ST_PATHFINDING;
				GAMESYS->SetMove(true);
				targetMoveCell = NULL;
			}
			else
			{
				Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
				TileCell* tileCell = map->FindTileCell(character->GetTilePosition());
				tileCell->IsCharacter(false);
				nextState = eStateType::ST_IDLE;
			}
		}
	  
	}
}

void NavigationState::Render(HDC hdc)
{
}

void NavigationState::Release()
{
}

void NavigationState::Reset()
{
}
