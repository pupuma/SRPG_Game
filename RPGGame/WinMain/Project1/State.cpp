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

	
}

void State::Update()
{

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





