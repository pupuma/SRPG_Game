#include "Game.h"
#include "SkillState.h"

#include "Character.h"


SkillState::SkillState(Character* _character)
	: State(_character)
{
}


SkillState::~SkillState()
{
}

void SkillState::Start()
{
	State::Start();

	std::vector<Component*> targetList = GAMESYS->SkillListTarget(character->GetTargetList(), character);


	//bool isTarget = GAMESYS->TargetCheck(targetList, character);


	character->SetDirection(GAMESYS->LookAtCharacter(targetList, character));
	for (int i = 0; i < targetList.size(); i++)
	{
		// 적이면 공격
		sMessageParam param;
		param.sender = character;
		param.receiver = targetList[i];
		param.message = TEXT("Skill");
		param.attackPoint = character->GetAttackPoint();
		param.healPoint = character->GetHealPoint();
		ComponentSystem::GetInstance()->SendMsg(param);


	}
	for (size_t i = 0; i < targetList.size(); i++)
	{
		POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
		EFFECTMANAGER->Play(TEXT("Darkness1"), pt);

	}

	GAMESYS->SetSkilling(false);


	//if (isTarget)
	//{
	//	

	//}
	//else
	//{
	//	if (character->GetComponetType() == eComponentType::CT_PLAYER)
	//	{
	//		nextState = eStateType::ST_PATH_IDLE;
	//	}
	//}

}

void SkillState::Update()
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

}

void SkillState::Render(HDC hdc)
{
}

void SkillState::Release()
{
}

void SkillState::Reset()
{
}
