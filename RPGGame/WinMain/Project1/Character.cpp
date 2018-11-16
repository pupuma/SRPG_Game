#include "Game.h"
#include "Character.h"
#include "Action.h"

// State
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "DefenseState.h"	
#include "DeadState.h"

Character::Character(std::string _name) 
	: Component(_name)
{
	type = eComponentType::CT_PLAYER;
}


Character::~Character()
{
}

bool Character::Init()
{
	img = IMAGEMANAGER->FindImage("Player");
	img->SetX(WINSIZEX / 2);
	img->SetY(WINSIZEX / 2);

	act = new Action();
	act->Init();

	act->MoveTo(img, 50, 50, 10.0f);

	InitState();
	ChangeState(eStateType::ST_MOVE);

	return true;
}

void Character::Deinit()
{
}

void Character::Update()
{
	//act->Update();
	state->Update();
}

void Character::Render(HDC hdc)
{
	img->Render(hdc);
	
}

void Character::Release()
{
}

void Character::Reset()
{
}

void Character::InitState()
{
	// IDLE
	{
		State* state = new IdleState(this);
		stateMap[eStateType::ST_IDLE] = state;
	}

	// MOVE
	{
		State* state = new MoveState(this);
		stateMap[eStateType::ST_MOVE] = state;
	}

	// ATTACK
	{
		State* state = new AttackState(this);
		stateMap[eStateType::ST_ATTACK] = state;
	}

	// DEFENSE
	{
		State* state = new DefenseState(this);
		stateMap[eStateType::ST_DEFENSE] = state;
	}

	// DEAD
	{
		State* state = new DeadState(this);
		stateMap[eStateType::ST_DEAD] = state;
	}
}

void Character::ChangeState(eStateType stateType)
{
	if (NULL != state)
	{
		state->Stop();
	}

	state = stateMap[stateType];
	state->Start();
}