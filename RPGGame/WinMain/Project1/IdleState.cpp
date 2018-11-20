#include "Game.h"
#include "IdleState.h"

#include "Character.h"
#include "TileCell.h"

IdleState::IdleState(Character* _character)
	: State(_character)
{
}


IdleState::~IdleState()
{
}

void IdleState::Start()
{
	State::Start();

	// PathFinding
	{
		PathFindingIdle();
	}

}

void IdleState::Update()
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
	character->UpdateAI();
}

void IdleState::Render(HDC hdc)
{
	State::Render(hdc);
	
}