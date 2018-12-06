#include "Game.h"
#include "State.h"

#include "Character.h"

State::State(Character* _character)
	: character(_character)
{
	//distSize = 0;
	nextState = eStateType::ST_NONE;
	isMove = false;
}


State::~State()
{
}

void State::Start()
{
	nextState = eStateType::ST_NONE;
	//distSize = character->GetMaxMoving();
	// 

	Direction();
}

void State::Update()
{
	//character->SetDirection(character->GetDirection());

	
	Direction();

	/*if (character->GetDirection() != character->GetNextDirection())
	{
		eDirection nextDir = character->GetNextDirection();
		character->SetDirection(nextDir);
	}*/
}

void State::Render(HDC hdc)
{
	
}

void State::Release()
{
}

void State::Reset()
{
}

void State::Direction()
{
	eDirection dir = character->GetDirection();

	switch (dir)
	{
	case eDirection::DIR_LEFT:
		character->SetImgFrame(1, 1);
		break;
	case eDirection::DIR_RIGHT:
		character->SetImgFrame(1, 2);

		break;
	case eDirection::DIR_UP:
		character->SetImgFrame(1, 3);

		break;
	case eDirection::DIR_DOWN:
		character->SetImgFrame(1, 0);

		break;
	}


	//if (character->GetDirection() == eDirection::DIR_LEFT)

}





