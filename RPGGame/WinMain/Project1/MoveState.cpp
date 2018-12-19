#include "Game.h"
#include "MoveState.h"

#include "Character.h"
#include "TileCell.h"
#include "Map.h"

MoveState::MoveState(Character* _character)
	: State(_character)
{
	
}


MoveState::~MoveState()
{
}

void MoveState::Start()
{
	State::Start();


	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	if (NULL != map)
	{

		TilePoint newTilePosition = character->GetTilePosition();
		//
		switch (character->GetNextDirection())
		{
		case eDirection::DIR_LEFT:
			newTilePosition.x--;
			break;
		case eDirection::DIR_RIGHT:
			newTilePosition.x++;
			break;
		case eDirection::DIR_UP:
			newTilePosition.y--;
			break;
		case eDirection::DIR_DOWN:
			newTilePosition.y++;
			break;
		}

		if (eDirection::DIR_NONE != character->GetNextDirection())
		{
			character->SetDirection(character->GetNextDirection());
		}

		if (newTilePosition.x != character->GetTilePosition().x || newTilePosition.y != character->GetTilePosition().y)
		{
			int width = PARSING->GetTileWidth();
			int height = PARSING->GetTIleHeight();

			if (newTilePosition.x < 0 || width <= newTilePosition.x ||
				newTilePosition.y < 0 || height <= newTilePosition.y)
			{
				nextState = eStateType::ST_IDLE;
				return;
			}
			if (map->FindTileCell(newTilePosition)->CanMove())
			{
				character->MoveStart(newTilePosition);
				nextState = eStateType::ST_IDLE;

			}
			else
			{
				nextState = eStateType::ST_IDLE;
			}
		}
		else
		{

			nextState = eStateType::ST_IDLE;
		}
	}
}

void MoveState::Stop()
{
	State::Stop();

	character->MoveStop();
}

void MoveState::Update()
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
	//UpdateMove();
}

void MoveState::UpdateMove()
{
	if (false == character->IsLive())
	{
		return;
	}

	if (false == character->IsMoving())
	{
		return;
	}
	
	nextState = eStateType::ST_IDLE;
}

