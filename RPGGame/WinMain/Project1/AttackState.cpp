#include "Game.h"
#include "AttackState.h"

#include "Character.h"
AttackState::AttackState(Character* _character)
	: State(_character)
{
}


AttackState::~AttackState()
{
}

void AttackState::Start()
{
	//GAMESYS->SetAttacking(true);
	State::Start();


	std::vector<Component*> targetList = character->GetTargetList();

	bool isTarget = GAMESYS->TargetCheck(targetList, character);

	
	if (isTarget)
	{
		character->SetDirection(GAMESYS->LookAtCharacter(targetList, character));
		for (int i = 0; i < targetList.size(); i++)
		{
			// 적이면 공격
			sMessageParam param;
			param.sender = character;
			param.receiver = targetList[i];
			param.message = TEXT("Attack");
			param.attackPoint = character->GetAttackPoint();
			ComponentSystem::GetInstance()->SendMsg(param);

			
		}
		POINT pt = { (targetList[0]->GetPosition().x + 48 / 2),(targetList[0]->GetPosition().y + 48 / 2) };
		EFFECTMANAGER->Play(TEXT("Absorb"), pt);

		GAMESYS->SetAttacking(false);


	}
	else
	{
		if (character->GetComponetType() == eComponentType::CT_PLAYER)
		{
			nextState = eStateType::ST_PATH_IDLE;
		}
	}

}

void AttackState::Update()
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

	character->ResetTarget();
	nextState = eStateType::ST_IDLE;

	//character->ResetTarget();
}

void AttackState::Render(HDC hdc)
{
}
