#include "Game.h"
#include "DefenseState.h"
#include "Character.h"



DefenseState::DefenseState(Character* _character)
	: State(_character)
{
}


DefenseState::~DefenseState()
{
}

void DefenseState::Start()
{
	State::Start();

	// Damage
	
	//HEAL
	if (true == character->IsLive())
	{
		if (GAMESYS->IsHeal())
		{
			int healPoint = character->GetHealPoint();
			character->InCreaseHP(healPoint);
			GAMESYS->SetHeal(false);
		}
		else
		{
			int damagePoint = character->GetDamagePoint();
			character->DecreaseHP(damagePoint);
		}
	}

	
	if (false == character->IsLive())
	{
		character->SetCanMove(true);
		character->MoveStop();
		ChangeState(eStateType::ST_DEAD);
		GAMESYS->DeleteCharacter(character);
	}
	else
	{
		ChangeState(eStateType::ST_IDLE);
	}

}

void DefenseState::Update()
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
}
