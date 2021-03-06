#include "Game.h"

#include "PathfindingMoveState.h"

#include "Character.h"
#include "TileCell.h"
#include "Map.h"

PathfindingMoveState::PathfindingMoveState(Character* _character)
	: State(_character)
{
}


PathfindingMoveState::~PathfindingMoveState()
{
}

void PathfindingMoveState::Start()
{
	State::Start();
	GAMESYS->SetAction(true);
	movingDuration = character->GetMoveTime();
	TileCell* tileCell = character->PopPathfindingCell();
	
}

void PathfindingMoveState::Stop()
{
	State::Stop();

	character->MoveStop();
}

void PathfindingMoveState::Update()
{
	State::Update();

	//
	if (eStateType::ST_NONE != nextState)
	{
		character->ChangeState(nextState);
#if defined(_DEBUG_TEST)
		character->SetStateType(nextState);
		GAMESYS->SetType(character->GetType());

#endif // 
		return;
	}

	{
		if (false == character->IsEmptyPathfindingStack())
		{
			if (character->GetMoveTime() <= movingDuration)
			{
				movingDuration = 0.0f;
				TileCell* tileCell = character->PopPathfindingCell();

				TilePoint toPosition = tileCell->GetTilePosition();
				TilePoint fromPosition = character->GetTilePosition();
				eDirection direction = GetDirection(toPosition, fromPosition);
				if (eDirection::DIR_NONE != direction)
				{
					character->SetDirection(direction);
				}

				character->MoveStart(toPosition);
			}
		}
		else
		{
			Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
			GAMESYS->SetMove(true);
			if (character->GetComponetType() == eComponentType::CT_MONSTER)
			{

				TileCell* tileCell = map->FindTileCell(character->GetTilePosition());
				tileCell->IsCharacter(true);

				if (GAMESYS->AttackRangeCheck(character))
				{
					//TileCell* tileCell = GAMESYS->GetTargetTileCell();
					TileCell* tileCell = character->GetTargetCharacterTileCell();

					std::vector<Component*> targetList = map->GetComponentList(tileCell);


					if (0 < targetList.size())
					{
						character->SetTarget(targetList);
						nextState = eStateType::ST_ATTACK;
					}
				}
				else
				{
					nextState = eStateType::ST_IDLE;
				}
				//
			}
			else
			{
				map->FindTileCell(character->GetTilePosition())->IsCharacter(true);
				nextState = eStateType::ST_PATH_IDLE;
			}
			GAMESYS->ResetTarget();
			character->SetTargetTileCell(NULL);
		
		}

		movingDuration += TIMEMANAGER->GetElapsedTime();
	}
	//UpdateMove();
}

eDirection PathfindingMoveState::GetDirection(TilePoint to, TilePoint from)
{
	if (from.x < to.x)
	{
		return eDirection::DIR_RIGHT;
	}
	if (to.x < from.x)
	{
		return eDirection::DIR_LEFT;
	}
	if (from.y < to.y)
	{
		return eDirection::DIR_DOWN;
	}
	if (to.y < from.y)
	{
		return eDirection::DIR_UP;
	}
	return eDirection::DIR_NONE;
}
