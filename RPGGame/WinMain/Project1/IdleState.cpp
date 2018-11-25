#include "Game.h"
#include "IdleState.h"

#include "Character.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "TileCell.h"

IdleState::IdleState(Character* _character)
	: State(_character)
{
}


IdleState::~IdleState()
{
}

void IdleState::Start()
{
	//State::Start();

	// PathFinding
	{
		//PathFindingIdle();
	}

}

void IdleState::Update()
{
	State::Update();
	//character->UpdateAI();
}

void IdleState::Render(HDC hdc)
{
	State::Render(hdc);

	// 

}