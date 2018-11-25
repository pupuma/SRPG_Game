#include "Game.h"
#include "MoveState.h"

#include "Character.h"
#include "TileCell.h"

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

