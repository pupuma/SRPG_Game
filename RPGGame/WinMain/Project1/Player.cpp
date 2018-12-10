#include "Game.h"
#include "Player.h"

#include "Map.h"	
#include "State.h"

Player::Player(std::string _name, float _deep)
	: Character(_name,_deep)
{
	//isTurn = true;

}


Player::~Player()
{
}

bool Player::Init()
{
	{
		isLive = true;
		img = IMAGEMANAGER->FindImage("Actor1");
		img->SetX(48);
		img->SetY(48);
		img->SetFrameX(0);
		img->SetFrameY(0);
		
		//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
		//{
			//if (NULL != map)
			//{
				//TilePoint tilePos;
				//tilePos.x = 6;
				//tilePos.y = 6;


				//tilePosition = tilePos;
				//map->SetTileComponent(tilePosition, this , true);

			//}
		//}

		//act = new Action();
		//act->Init();

		//act->MoveTo(img, 50, 50, 10.0f);

		InitState();
		eType = eStateType::ST_IDLE;
		ChangeState(eType);

	}

	// Attack List
	{

	}
	return true;
}

//void Player::Render(HDC hdc)
//{
//	
//}

void Player::UpdateAI()
{
	{
		//if (false == isMoving)
		//{
		//	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
		//	if (NULL != map)
		//	{
		//		nextDirection = eDirection::DIR_NONE;

		//		if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
		//		{
		//			nextDirection = eDirection::DIR_LEFT;
		//		}

		//		if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
		//		{
		//			nextDirection = eDirection::DIR_RIGHT;
		//		}

		//		if (KEYMANAGER->IsOnceKeyDown(VK_UP))
		//		{
		//			nextDirection = eDirection::DIR_UP;
		//		}

		//		if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
		//		{
		//			nextDirection = eDirection::DIR_DOWN;
		//		}

		//		if (nextDirection != eDirection::DIR_NONE)
		//		{
		//			isMoving = true;
		//			//TilePoint pos = { 7,7 };
		//			//MoveStart(pos);
		//			eType = eStateType::ST_MOVE;
		//			ChangeState(eStateType::ST_MOVE);
		//		}
		//	}

		//}

	}
}

void Player::AttackPattern()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	map->SetAttackRange();
}
