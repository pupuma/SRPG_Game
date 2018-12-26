#include "Game.h"
#include "SkillState.h"

#include "Character.h"
#include "GameTurnManager.h"

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
	int index = GameTurnManager::GetSingleton()->GetSkillIndex();
	int dcMp;
	switch (index)
	{
	case 1:
		dcMp = 10;
		break;
	case 2:
		dcMp = 20;
		break;
	case 3:
		dcMp = 30;
		break;
	default:
		dcMp = 0;
		break;
	}
	character->DecreaseMp(dcMp);
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
		if (character->GetHealPoint() > 0)
		{
			param.healPoint = character->GetHealPoint();
			param.attackPoint = 0;
		}
		else
		{
			param.healPoint = 0;
			param.attackPoint = character->GetSkillDamgePoint();
		}
		ComponentSystem::GetInstance()->SendMsg(param);


	}

	character->SetHealPoint(0);

	if (character->GetJobs() == eJobClass::JOB_WARRIOR)
	{
		if (GameTurnManager::GetSingleton()->GetSkillIndex() == 1)
		{
			for (size_t i = 0; i < targetList.size(); i++)
			{
				POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
				EFFECTMANAGER->Play(TEXT("Darkness1"), pt);
			}
		}
		else if (GameTurnManager::GetSingleton()->GetSkillIndex() == 2)
		{
			for (size_t i = 0; i < targetList.size(); i++)
			{
				POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
				EFFECTMANAGER->Play(TEXT("Darkness2"), pt);
			}
		}
		else if (GameTurnManager::GetSingleton()->GetSkillIndex() == 3)
		{
			for (size_t i = 0; i < targetList.size(); i++)
			{
				POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
				EFFECTMANAGER->Play(TEXT("Darkness3"), pt);
			}
		}
		
	}
	else if (character->GetJobs() == eJobClass::JOB_ARCHER)
	{
		if (GameTurnManager::GetSingleton()->GetSkillIndex() == 1)
		{
			for (size_t i = 0; i < targetList.size(); i++)
			{
				POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
				EFFECTMANAGER->Play(TEXT("Fire1"), pt);
			}
		}
		else if (GameTurnManager::GetSingleton()->GetSkillIndex() == 2)
		{
			for (size_t i = 0; i < targetList.size(); i++)
			{
				POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
				EFFECTMANAGER->Play(TEXT("Fire1"), pt);
			}
		}
		else if (GameTurnManager::GetSingleton()->GetSkillIndex() == 3)
		{
			for (size_t i = 0; i < targetList.size(); i++)
			{
				POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
				EFFECTMANAGER->Play(TEXT("Fire1"), pt);
			}
		}
	}
	else if (character->GetJobs() == eJobClass::JOB_HEALER)
	{
		if (GameTurnManager::GetSingleton()->GetSkillIndex() == 1)
		{
			for (size_t i = 0; i < targetList.size(); i++)
			{
				POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
				EFFECTMANAGER->Play(TEXT("Holy1"), pt);
			}
		}
		else if (GameTurnManager::GetSingleton()->GetSkillIndex() == 2)
		{
			for (size_t i = 0; i < targetList.size(); i++)
			{
				POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
				EFFECTMANAGER->Play(TEXT("Holy2"), pt);
			}
		}
		else if (GameTurnManager::GetSingleton()->GetSkillIndex() == 3)
		{
			for (size_t i = 0; i < targetList.size(); i++)
			{
				POINT pt = { (targetList[i]->GetPosition().x + 48 / 2),(targetList[i]->GetPosition().y + 48 / 2) };
				EFFECTMANAGER->Play(TEXT("Holy3"), pt);
			}
		}
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
