#include "Game.h"

#include "PathfindingState.h"
#include "Character.h"

#include "Map.h"
#include "TileCell.h"

PathfindingState::PathfindingState(Character* _character)
	: State(_character)
{
}


PathfindingState::~PathfindingState()
{
}

void PathfindingState::Start()
{
	State::Start();

	// PathFinding
	{
		map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
		map->ResetPahtfinding();
	}

	targetTileCell = character->GetTargetTileCell();

	TileCell* startTileCell = map->FindTileCell(character->GetTilePosition());

	sPathCommand command;
	command.tileCell = startTileCell;
	command.heuristic = 0.0f;
	pathfindingQueue.push(command);

	updateState = eUpdateState::PATHFINDING;

}

void PathfindingState::Stop()
{
	State::Stop();

	while (0 != pathfindingQueue.size())
	{
		pathfindingQueue.pop();
	}
}

void PathfindingState::Update()
{
	State::Update();
	
	if (eStateType::ST_NONE != nextState)
	{
		character->ChangeState(nextState);
		return;
	}

	switch (updateState)
	{
	case eUpdateState::PATHFINDING:
		UpdatePathfinding();
		break;
	case eUpdateState::BUILD_PATH:
		UpdateBuildPath();
		break;
	}
}

void PathfindingState::UpdatePathfinding()
{
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
			if (command.tileCell->GetTilePosition().x == targetTileCell->GetTilePosition().x &&
				command.tileCell->GetTilePosition().y == targetTileCell->GetTilePosition().y)
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
					if(false == searchTileCell->IsSearchPathfinding() &&
						true == searchTileCell->CanMove() ||
						((searchTileCell->GetTilePosition().x == targetTileCell->GetTilePosition().x &&
							searchTileCell->GetTilePosition().y == targetTileCell->GetTilePosition().y)))
					{
						float distanceFromStart = command.tileCell->GetDistanceFromStart() + 1;

						float heuristic = 0.0f;

						float distance = 0.0f;
						int distanceW = searchTileCell->GetTilePosition().x - targetTileCell->GetTilePosition().x;
						int distanceH = searchTileCell->GetTilePosition().y - targetTileCell->GetTilePosition().y;
						distanceW = distanceW * distanceW;
						distanceH = distanceH * distanceH;
						distance = sqrtf(distanceW + distanceH);

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
						//heuristic = CalcAStarHeuristic(distanceFromStart, searchTileCell, _targetTileCell);

						heuristic = distanceFromStart;

						if (NULL == searchTileCell->GetPrevTileCell())
						{
							// 큐에 넣는다.
							searchTileCell->SetPrevTileCell(command.tileCell);
							searchTileCell->SetDistanceFromStart(distanceFromStart);

							sPathCommand newCommand;
							newCommand.tileCell = searchTileCell;
							newCommand.heuristic = heuristic;
							pathfindingQueue.push(newCommand);

							//CheckTestMark(searchTileCell);
						}
					}
				}
				
			}
		}
	}
}

void PathfindingState::UpdateBuildPath()
{
	{
		// 목표 지점까지 경로 구축
		// 거꾸로 돌아가면서 길을 도출
		if (NULL != reverseTileCell)
		{
			character->PushPathfindingCell(reverseTileCell);
			reverseTileCell = reverseTileCell->GetPrevTileCell();
		}
		else
		{
			nextState = eStateType::ST_PATH_MOVE;
		}
	}
}

TilePoint PathfindingState::GetSearchTilePositionByDirection(TilePoint _tilePosition, eDirection _direction)
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
