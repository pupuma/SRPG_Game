#include "Game.h"
#include "Character.h"
#include "Action.h"

// State
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "DefenseState.h"	
#include "DeadState.h"

#include "PathfindingldeState.h"
#include "PathfindingImmedateState.h"
#include "PathfindingMoveState.h"

//
#include "Map.h"


Character::Character(std::string _name, float _deep)
	: Component(_name, _deep)
{
	type = eComponentType::CT_PLAYER;
	nextDirection = eDirection::DIR_LEFT; 
	isMoving = false;

	attackPoint = 5;
	iMaxMoving = 3;
	moveTime = (float)(rand() % 100 + 50) / 100.0f;
	SetCanMove(false);
}


Character::~Character()
{
}

bool Character::Init( )
{
	//{
	//	isLive = true;
	//	img = IMAGEMANAGER->FindImage("Actor1");
	//	img->SetX(48);
	//	img->SetY(48);
	//	img->SetFrameX(0);
	//	img->SetFrameY(0);

	//	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	//	{
	//		if (NULL != map)
	//		{
	//			TilePoint tilePos;
	//			tilePos.x = 4;
	//			tilePos.y = 5;


	//			tilePosition = tilePos;
	//			map->SetTileComponent(tilePosition, this);

	//		}
	//	}

	//	//act = new Action();
	//	//act->Init();

	//	//act->MoveTo(img, 50, 50, 10.0f);

	//	InitState();
	//	eType = eStateType::ST_PATH_IDLE;
	//	ChangeState(eType);
	//}

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
	img->FrameRender(hdc, position.x - CAMERA->GetPosition()->x, position.y - CAMERA->GetPosition()->y);


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

	//
	{
		State* state = new PathfindingImmedateState(this);
		stateMap[eStateType::ST_PATHFINDING] = state;
	}

	{
		State* state = new PathfindingldeState(this);
		stateMap[eStateType::ST_PATH_IDLE] = state;
	}
	
	{
		State* state = new PathfindingMoveState(this);
		stateMap[eStateType::ST_PATH_MOVE] = state;
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

void Character::AttackPattern(std::vector<Component*>* _list)
{
	//map->FindTileCell(this->GetTilePosition());
}

void Character::ReceiveMsg(const sMessageParam & param)
{
	if (TEXT("Attack") == param.message)
	{
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

TileCell * Character::GetTargetTileCell()
{
	return targetTileCell;

}

void Character::SetTargetTileCell(TileCell * _targetTileCell)
{
	{
		targetTileCell = _targetTileCell;
	}
}

void Character::PushPathfindingCell(TileCell* _tileCell)
{
	pathfindingCellStack.push(_tileCell);
}

TileCell* Character::PopPathfindingCell()
{
	TileCell* tileCell = pathfindingCellStack.top();
	pathfindingCellStack.pop();
	return tileCell;

}

float Character::GetMoveTime()
{
	return moveTime;
}

bool Character::IsEmptyPathfindingStack()
{
	if (0 != pathfindingCellStack.size())
	{
		return false;
	}
	return true;
}

void Character::SetDirection(eDirection _direction)
{
	currentDirection = _direction;
}

std::vector<Component*> Character::GetTargetList()
{
	return targetList;
}

void Character::AddTarget(Component* _target)
{
	targetList.push_back(_target);
}
