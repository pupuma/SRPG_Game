#include "Game.h"
#include "Player.h"

#include "Map.h"	


Player::Player(std::string _name)
	: Character(_name)
{
}


Player::~Player()
{
}

void Player::UpdateAI()
{
	{
		if (false == isMoving)
		{
			Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
			if (NULL != map)
			{
				nextDirection = eDirection::DIR_NONE;

				if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
				{
					nextDirection = eDirection::DIR_LEFT;
				}

				if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
				{
					nextDirection = eDirection::DIR_RIGHT;
				}

				if (KEYMANAGER->IsOnceKeyDown(VK_UP))
				{
					nextDirection = eDirection::DIR_UP;
				}

				if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
				{
					nextDirection = eDirection::DIR_DOWN;
				}

				if (nextDirection != eDirection::DIR_NONE)
				{
					//isMoving = true;
					//TilePoint pos = { 3,3 };
					//MoveStart(pos);
					eType = eStateType::ST_MOVE;
					ChangeState(eStateType::ST_MOVE);
				}
			}

		}

	}
}
