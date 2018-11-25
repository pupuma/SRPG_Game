#include "Game.h"

#include "PathfindingldeState.h"


#include "Character.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "TileCell.h"

PathfindingldeState::PathfindingldeState(Character* _character)
	: State(_character)
{
}


PathfindingldeState::~PathfindingldeState()
{
}

void PathfindingldeState::Start()
{
	State::Start();
	GAMESYS->SetAction(false);
}

void PathfindingldeState::Update()
{
	State::Update();

	{
		if (eStateType::ST_NONE != nextState)
		{
			character->ChangeState(nextState);
#if defined(_DEBUG_TEST)
			character->SetStateType(nextState);
#endif // 
			return;
		}
	}
	//

	{
		if (false ==GetMove())
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				GetCursorPos(&_ptMouse);
				ScreenToClient(_hWnd, &(_ptMouse));
				Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

				int mouseX = (int)_ptMouse.x;
				int mouseY = (int)_ptMouse.y;

				TileCell* tileCell = map->FindTileCellByMousePosition(mouseX, mouseY);

				// 
				std::list<TileInfo> openList = map->GetOpenTileCellList();
				std::list<TileInfo>::iterator it;

				if (!openList.empty())
				{
					for (it = openList.begin(); it != openList.end(); it++)
					{
						if (tileCell == (*it).tile)
						{
							if (NULL != tileCell)
							{
								character->SetTargetTileCell(tileCell);
							}
							break;
						}
					}
				}


				//

			}
			TileCell* targetTileCell = character->GetTargetTileCell();
			if (NULL != targetTileCell)
			{
				nextState = eStateType::ST_PATHFINDING;
				SetMove(true);
			}
		}
		else
		{
			GAMESYS->SetAttacking(true);
			character->AttackPattern(&attackList);


			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{

			}
		}

	}


}
