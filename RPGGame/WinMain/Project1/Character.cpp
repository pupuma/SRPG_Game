#include "Game.h"
#include "Character.h"
#include "Action.h"

// State
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "DefenseState.h"	
#include "DeadState.h"

//
#include "Map.h"

Character::Character(std::string _name) 
	: Component(_name)
{
	type = eComponentType::CT_PLAYER;
	nextDirection = eDirection::DIR_LEFT;
	isMoving = false;

	iMaxMoving = 5;

}


Character::~Character()
{
}

bool Character::Init( )
{
	isLive = true;
	img = IMAGEMANAGER->FindImage("Actor1");
	img->SetX(48);
	img->SetY(48);
	img->SetFrameX(0);
	img->SetFrameY(0);

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	{
		if (NULL != map)
		{
			TilePoint tilePos;
			tilePos.x =15;
			tilePos.y = 15;
		

			tilePosition = tilePos;
			map->SetTileComponent(tilePosition, this);

		}
	}

	//act = new Action();
	//act->Init();

	//act->MoveTo(img, 50, 50, 10.0f);

	InitState();
	eType = eStateType::ST_IDLE;
	ChangeState(eType);

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
	//img->Render(hdc);
	state->Render(hdc);
	img->FrameRender(hdc, position.x, position.y);


#if defined(_DEBUG_TEST)
	
#endif // Text Render
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

void Character::UpdateAI()
{
	{
		//if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
		//{
		//	eType = eStateType::ST_MOVE;
		//	ChangeState(eType);
		//}
	}
	
	
}

void Character::MoveStart(TilePoint newTilePosition)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	if (NULL != map)
	{
		map->ResetTileComponent(tilePosition, this);
		tilePosition = newTilePosition;
		map->SetTileComponent(tilePosition, this);

		isMoving = true;
	}
}

void Character::MoveStop()
{
	isMoving = false;
}

bool Character::IsMoving()
{
	return isMoving;
}

bool Character::IsLive()
{
	return isLive;
}
