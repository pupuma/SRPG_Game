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
		}
	  
	}

	//if (deltaTime < 0)
	//{
	//	deltaTime = 1.f;
	//	if (!isNavi)
	//	{
	//		if (GAMESYS->AttackRangeCheck(character))
	//		{
	//			TileCell* tileCell = GAMESYS->GetTargetTileCell();

	//			Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	//			std::vector<Component*> targetList = map->GetComponentList(tileCell);


	//			if (0 < targetList.size())
	//			{
	//				character->SetTarget(targetList);
	//				nextState = eStateType::ST_ATTACK;
	//			}
	//		}
	//		else
	//		{
	//			TileCell* targetCell = GAMESYS->FindPriorityTarget(character);
	//			// 선택시 
	//			// character->SetTargetTileCell();
	//			//TileCell* targetTileCell = character->GetTargetTileCell();
	//			character->SetTargetTileCell(targetCell);
	//			if (NULL != targetCell)
	//			{
	//				Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	//				TileCell* tileCell = map->FindTileCell(character->GetTilePosition());
	//				tileCell->IsCharacter(false);

	//				nextState = eStateType::ST_PATHFINDING;
	//				GAMESYS->SetMove(true);
	//				character->AttackPattern();
	//				isNavi = true;
	//			}
	//			else
	//			{
	//				GameTurnManager::GetSingleton()->NextTurn();
	//			}
	//		}

	//	}
	//	else
	//	{

	//		if (NULL != GAMESYS->GetTargetTileCell())
	//		{
	//			TileCell* tileCell = GAMESYS->GetTargetTileCell();

	//			Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	//			std::vector<Component*> targetList = map->GetComponentList(tileCell);


	//			if (0 < targetList.size())
	//			{
	//				
	//				character->SetTarget(targetList);
	//				nextState = eStateType::ST_ATTACK;
	//				
	//			}
	//		}


	//	}
	//}
	//
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
