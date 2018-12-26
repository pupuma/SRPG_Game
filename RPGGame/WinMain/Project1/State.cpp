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
	int frameX = character->GetFrameX();
	int frameY = character->GetFrameY();
	
	switch (dir)
	{
	case eDirection::DIR_LEFT:
		if (frameY <= 3)
		{
			character->SetImgFrame(frameX, 1);

		}
		else
		{
			character->SetImgFrame(frameX, 5);

		}
		break;
	case eDirection::DIR_RIGHT:
		if (frameY <= 3)
		{
			character->SetImgFrame(frameX, 2);

		}
		else
		{
			character->SetImgFrame(frameX, 6);

		}
		break;
	case eDirection::DIR_UP:
		if (frameY <= 3)
		{
			character->SetImgFrame(frameX, 3);

		}
		else
		{
			character->SetImgFrame(frameX, 7);

		}
		break;
	case eDirection::DIR_DOWN:
		if (frameY <= 3)
		{
			character->SetImgFrame(frameX, 0);
		}
		else
		{
			character->SetImgFrame(frameX, 4);

		}
		break;
	}


	//if (character->GetDirection() == eDirection::DIR_LEFT)

}





