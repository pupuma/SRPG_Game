#include "Game.h"
#include "IdleState.h"

#include "Character.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "TileCell.h"
#include "GameTurnManager.h"
#include "EventSystem.h"

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
	deltaTime = 1.5f;
	// PathFinding
	{
		//PathFindingIdle();
		GAMESYS->SetAction(false);
		GAMESYS->SetAttacking(false);

		
	}

}

void IdleState::Update()
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
		else
		{
#if defined(_DEBUG_TEST)
			character->SetStateType(nextState);
			GAMESYS->SetType(character->GetType());

#endif // 
		}
	}


	if (EVENTSYS->GetGameType() == eGameType::GT_EVENT)
	{
		character->UpdateAI();

	}

	if (EVENTSYS->GetGameType() == eGameType::GT_BATTLE)
	{
		deltaTime -= TIMEMANAGER->GetElapsedTime();

		if (deltaTime < 0)
		{
			deltaTime = 1.5f;
			if (character->IsTurn())
			{
				GameTurnManager::GetSingleton()->NextTurn();

			}
		}
	}


	
	

	//character->UpdateAI();
}

void IdleState::Render(HDC hdc)
{
	State::Render(hdc);

	// 

}