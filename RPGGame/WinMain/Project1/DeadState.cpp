#include "Game.h"
#include "DeadState.h"



DeadState::DeadState(Character* _character)
	: State(_character)
{
}


DeadState::~DeadState()
{
}

void DeadState::Start()
{
}

void DeadState::Update()
{
}
