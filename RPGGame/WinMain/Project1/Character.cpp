#include "Game.h"
#include "Character.h"

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
#include "Animation.h"



Character::Character(std::string _name, float _deep)
	: Component(_name, _deep)
{
	type = eComponentType::CT_PLAYER;
	nextDirection = eDirection::DIR_NONE;
	currentDirection = eDirection::DIR_LEFT;
	isMoving = false;

	attackPoint = 1;
	iMaxMoving = 3;
	isTurn = false;
	moveTime = (float)(rand() % 100 + 50) / 100.0f;
	SetCanMove(false);


	frameX = 0;
	frameY = 0;

	//
	damagePoint = 0;
	iHp = 5;
}


Character::~Character()
{
}

bool Character::Init( )
{

	return true;
}

void Character::Deinit()
{
}

void Character::Update()
{
	//act->Update();
	state->Update();

	if (KEYMANAGER->IsOnceKeyDown(VK_F1))
	{
		GAMESYS->GameTurn();
	}
}

void Character::Render(HDC hdc)
{
	//img->Render(hdc);
	state->Render(hdc);

	img->FrameRender(hdc, position.x - CAMERA->GetPosition()->x, position.y - CAMERA->GetPosition()->y,
		frameX, frameY);


#if defined(_DEBUG_TEST)
	// HP
	TCHAR str[256];
	_stprintf(str, TEXT("HP : %d "), iHp);
	TextOut(hdc, position.x, position.y, str, _tcslen(str));

	memset(str, 0, sizeof(TCHAR) * 256);

	//
	std::string testStr;
	switch (currentDirection)
	{
	case eDirection::DIR_LEFT:
		testStr = TEXT("State : LEFT");
		break;
	case eDirection::DIR_RIGHT:
		testStr = TEXT("State : RIGHT");
		break;
	case eDirection::DIR_UP:
		testStr = TEXT("State : UP");
		break;
	case eDirection::DIR_DOWN:
		testStr = TEXT("State : DOWN");
		break;
	case eDirection::DIR_NONE:
		testStr = TEXT("State : NONE");
		break;
	}

	TextOut(hdc, position.x - 15, position.y -15, testStr.c_str(), testStr.length());

	testStr.clear();

	//
	eStateType eType = GetType();
	switch (eType)
	{
	case eStateType::ST_NONE:
		testStr = TEXT("State : STATE_NONE");
		break;
	case eStateType::ST_IDLE:
		testStr = TEXT("State : STATE_IDLE");
		break;
	case eStateType::ST_MOVE:
		testStr = TEXT("State : STATE_MOVE");
		break;
	case eStateType::ST_ATTACK:
		testStr = TEXT("State : STATE_ATTACK");
		break;
	case eStateType::ST_DEFENSE:
		testStr = TEXT("State : STATE_DEFFENSE");
		break;
	case eStateType::ST_DEAD:
		testStr = TEXT("State : STATE_DEAD");
	case eStateType::ST_PATHFINDING:
		testStr = TEXT("State : PATHFINDING");
		break;
	case eStateType::ST_PATH_IDLE:
		testStr = TEXT("State : PATH_IDLE");
		break;
	case eStateType::ST_PATH_MOVE:
		testStr = TEXT("State : PATH_MOVE");
		break;
	}

	TextOut(hdc, position.x - 30, position.y - 30, testStr.c_str(), testStr.length());

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

void Character::AttackPattern()
{
	//map->FindTileCell(this->GetTilePosition());
}

void Character::ReceiveMsg(const sMessageParam & param)
{
	if (TEXT("Attack") == param.message)
	{
		damagePoint = param.attackPoint;
		state->ChangeState(eStateType::ST_DEFENSE);
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

void Character::SetNextDirection(eDirection _direction)
{
	nextDirection = _direction;
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

void Character::ResetTarget()
{
	{
		targetList.clear();
	}
}

void Character::DecreaseHP(int _damagePoint)
{
	iHp -= _damagePoint;
	if (iHp < 0)
	{
		isLive = false;
		iHp = 0;
	}
}

void Character::SetTilePosition(int _tilePosX, int _tilePosY)
{
	TilePoint tilePos;

	
	tilePos.x = _tilePosX;
	tilePos.y = _tilePosY;

	tilePosition = tilePos;

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	map->SetTileComponent(tilePosition, this, true);

}

void Character::SetImgFrame(int _frameX, int _frameY)
{
	//img->SetFrameX(_frameX);
	//img->SetFrameY(_frameY);
	frameX = _frameX;
	frameY = _frameY;
	

}

void Character::SetTurn(bool _isTurn)
{
	isTurn = _isTurn;
	//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	//map->ResetViewer();
	//map->SetViewer((Component*)this);

}
