#include "Game.h"
#include "NaviGationSystem.h"


#include "Map.h"
#include "ComponentSystem.h"
#include "Character.h"
#include "TileCell.h"


NaviGationSystem::NaviGationSystem()
{
}


NaviGationSystem::~NaviGationSystem()
{
}

TileCell* NaviGationSystem::AStarPathFinder(Character * _startCharacter, Character * _endCharacter)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	map->ResetPahtfinding();

	Reset();
	TileCell* tileCell = NULL;
	startTileCell = map->FindTileCell(_startCharacter->GetTilePosition());
	endTileCell = map->FindTileCell(_endCharacter->GetTilePosition());
	sPathCommand command;
	command.tileCell = startTileCell;
	command.heuristic = 0.0f;
	pathfindingQueue.push(command);

	updateState = eUpdateState::PATHFINDING;

	while (0 != pathfindingQueue.size())
	{
		if (eUpdateState::BUILD_PATH == updateState)
		{
			break;
		}
		UpdatePathfinding();
	}

	UpdateBuildPath();

	if (!q_Close.empty())
	{
		std::list<TileInfo> moveList = map->GetOpenTileCellList();
		tileCell = DistanceTileCell(moveList);

	}
	//pathfindingQueue;
	return tileCell;
}

void NaviGationSystem::UpdatePathfinding()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));


	// 길찾기 업데이트 시작
	if (0 != pathfindingQueue.size())	// 큐에 무언가가 들어있으면 맨 앞에 원소를 빼서 검사
	{
		sPathCommand command = pathfindingQueue.top();	// 맨 앞에 있는 원소를 빼냄
		pathfindingQueue.pop();	// 빼낸 후 큐에서 제거

		if (false == command.tileCell->IsSearchPathfinding())
		{
			// 아직 검사하지 않은 타일 셀이면
			command.tileCell->SearchPathfind();	// 검사 했다고 체크

												// 목표에 도달 했는가?
			if (command.tileCell->GetTilePosition().x == endTileCell->GetTilePosition().x &&
				command.tileCell->GetTilePosition().y == endTileCell->GetTilePosition().y)
			{
				reverseTileCell = command.tileCell;
				updateState = eUpdateState::BUILD_PATH;
				return;
			}

			for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
			{
				TilePoint currentTilePosition = command.tileCell->GetTilePosition();
				TilePoint searchTilePosision = GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
				TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);


				if (NULL != searchTileCell)
				{
					if (false == searchTileCell->IsSearchPathfinding() &&
						true == searchTileCell->CanMove() ||
						((searchTileCell->GetTilePosition().x == endTileCell->GetTilePosition().x &&
							searchTileCell->GetTilePosition().y == endTileCell->GetTilePosition().y)))
					{
						float distanceFromStart = command.tileCell->GetDistanceFromStart() + 1;

						float heuristic = 0.0f;

						float distance = 0.0f;
						int distanceW = searchTileCell->GetTilePosition().x - endTileCell->GetTilePosition().x;
						int distanceH = searchTileCell->GetTilePosition().y - endTileCell->GetTilePosition().y;
						distanceW = distanceW * distanceW;
						distanceH = distanceH * distanceH;
						distance = sqrtf(distanceW + distanceH);


						/*if (distance < 10)
						{
							heuristic = CalcAStarHeuristic(distanceFromStart, searchTileCell, endTileCell);
						}*/

						/*
						if (distance < 10)
						{
							heuristic = CalcAStarHeuristic(distanceFromStart, searchTileCell, _targetTileCell);
						}
						else if (distance < 10)
						{
							heuristic = CalcComplexHeuristic(searchTileCell, _targetTileCell);
						}
						else if (distance < 20)
						{
							heuristic = CalcSimpleHeuristic(command.tileCell, searchTileCell, _targetTileCell);
						}
						else
						{
							heuristic = distanceFromStart;
						}
						*/
						heuristic = CalcAStarHeuristic(distanceFromStart, searchTileCell, endTileCell);

						//heuristic = distanceFromStart;

						if (NULL == searchTileCell->GetPrevTileCell())
						{
							// 큐에 넣는다.
							searchTileCell->SetPrevTileCell(command.tileCell);
							searchTileCell->SetDistanceFromStart(distanceFromStart);

							sPathCommand newCommand;
							newCommand.tileCell = searchTileCell;
							newCommand.heuristic = heuristic;
							pathfindingQueue.push(newCommand);

						}
					}
				}

			}
		}
	}
}

TilePoint NaviGationSystem::GetSearchTilePositionByDirection(TilePoint _tilePosition, eDirection _direction)
{
	TilePoint searchTilePosition = _tilePosition;
	switch (_direction)
	{
	case eDirection::DIR_LEFT:
		searchTilePosition.x--;
		break;
	case eDirection::DIR_RIGHT:
		searchTilePosition.x++;
		break;
	case eDirection::DIR_UP:
		searchTilePosition.y--;
		break;
	case eDirection::DIR_DOWN:
		searchTilePosition.y++;
		break;
	}
	return searchTilePosition;
}


void NaviGationSystem::UpdateBuildPath()
{
	// 목표 지점까지 경로 구축
	// 거꾸로 돌아가면서 길을 도출
	while (1)
	{
		if (NULL != reverseTileCell)
		{
			q_Close.push(reverseTileCell);
			//closeList.push_back(reverseTileCell);
			reverseTileCell = reverseTileCell->GetPrevTileCell();
		}
		else
		{
			break;
		}
	}
	
}
float NaviGationSystem::CalcComplexHeuristic(TileCell* search, TileCell* goal)
{
	int distanceW = search->GetTilePosition().x - goal->GetTilePosition().x;
	int distanceH = search->GetTilePosition().y - goal->GetTilePosition().y;

	distanceW = distanceW * distanceW;
	distanceH = distanceH * distanceH;

	return (float)(distanceW + distanceH);
}


float NaviGationSystem::CalcAStarHeuristic(float distanceFromStart, TileCell * search, TileCell * goal)
{
	return distanceFromStart + CalcComplexHeuristic(search, goal);

}

TileCell * NaviGationSystem::DistanceTileCell(std::list<TileInfo> _list)
{
	std::list<TileInfo>::iterator it;
	TileCell* tileCell;
	q_Close.pop();
	while (!q_Close.empty())
	{
		for (it = _list.begin(); it != _list.end(); it++)
		{
			if (q_Close.front()->GetTilePosition() == (*it).tile->GetTilePosition())
			{
				tileCell = q_Close.front();
				return tileCell;
			}
		}
		q_Close.pop();
	}
	
	return NULL;
}

void NaviGationSystem::Reset()
{
	while (!q_Close.empty())
	{
		q_Close.pop();
	}

	while (!pathfindingQueue.empty())
	{
		pathfindingQueue.pop();
	}
}
