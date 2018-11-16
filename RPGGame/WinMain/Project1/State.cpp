#include "Game.h"
#include "State.h"



State::State(Character* _character)
	: character(_character)
{
}


State::~State()
{
}

void State::Start()
{
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
