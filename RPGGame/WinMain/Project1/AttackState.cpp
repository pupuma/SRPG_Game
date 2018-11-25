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
	
	character->AttackPattern(&attackList);
	std::vector<Component*> targetList = character->GetTargetList();
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

}

void AttackState::Update()
{
}

void AttackState::Render(HDC hdc)
{
}
