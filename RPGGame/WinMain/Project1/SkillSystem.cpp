#include "Game.h"
#include "SkillSystem.h"

#include "Map.h"
#include "ComponentSystem.h"
#include "Character.h"
#include "TileCell.h"



SkillSystem::SkillSystem()
{
}


SkillSystem::~SkillSystem()
{
}

void SkillSystem::Init()
{
	width = PARSING->GetTileWidth();
	height = PARSING->GetTIleHeight();
}

std::vector<TileInfo> SkillSystem::NomalSkillRange(Character * _character)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	std::vector<TileInfo> attackList;
	int distance = 1;


	for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
	{
		TilePoint currentTilePosition = _character->GetTilePosition();
		TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
		TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

		if (searchTilePosision.x < 0 || searchTilePosision.x >= map->GetWidth() ||
			searchTilePosision.y < 0 || searchTilePosision.y >= map->GetHeight())
		{
			continue;
		}
		TileInfo tileInfo;
		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
		tileInfo.distance = distance;
		attackList.push_back(tileInfo);
	}

	return attackList;
}

std::vector<TileInfo> SkillSystem::BoxSkillRange(Character * _character)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	std::vector<TileInfo> skillRangeList;

	int distance = _character->GetDistance();
	float heuristic = 0;
	float tempHeuristic = 0;
	//
	map->ResetPahtfinding();
	while (!pathfindingQueue.empty())
	{
		pathfindingQueue.pop();
	}

	// first
	for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
	{
		TilePoint currentTilePosition = _character->GetTilePosition();
		TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
		TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

		if (searchTilePosision.x < 0 || searchTilePosision.x > 32 ||
			searchTilePosision.y < 0 || searchTilePosision.y > 32)
		{
			continue;
		}

		if (searchTilePosision == _character->GetTilePosition() ||
			map->FindTileCell(searchTilePosision)->IsSearchPathfinding() == true)
		{
			continue;
		}

		searchTileCell->SetSearchPathfinding(true);

		TileInfo tileInfo;
		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
		tileInfo.distance = distance;
		skillRangeList.push_back(tileInfo);

		std::pair<TileCell*, int> p_data;
		pathfindingQueue.push(searchTileCell);
	}

	distance -= 1;
	// second 

	//
	//std::priority_queue<TileCell*> prevPathfindingQueue;
	std::queue<TileCell*> prevPathfindingQueue;
	TileCell* prevTileCell = NULL;
	while (distance > 0)
	{
		if (!pathfindingQueue.empty())
		{
			targetTileCell = pathfindingQueue.front();
			pathfindingQueue.pop();

			for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
			{
				TilePoint currentTilePosition = targetTileCell->GetTilePosition();
				TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
				TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

				if (searchTilePosision.x < 0 || searchTilePosision.x >= width ||
					searchTilePosision.y < 0 || searchTilePosision.y >= height)
				{
					continue;
				}
				heuristic = UTIL::GetDistance(searchTilePosision.x, searchTilePosision.y, _character->GetTilePosition().x, _character->GetTilePosition().y);

				if (searchTilePosision == targetTileCell->GetTilePosition() ||
					map->FindTileCell(searchTilePosision)->IsSearchPathfinding() == true 
					|| heuristic >= 2)
				{
					continue;
				}

				searchTileCell->SetSearchPathfinding(true);

				TileInfo tileInfo;
				tileInfo.tile = searchTileCell;
				tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
				tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
				tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

				tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
				tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
				tileInfo.distance = distance;

				skillRangeList.push_back(tileInfo);

				std::pair<TileCell*, int> p_data;
				prevPathfindingQueue.push(searchTileCell);
			}
		}

		if (pathfindingQueue.empty())
		{
			distance -= 1;
			pathfindingQueue = prevPathfindingQueue;
			for (size_t i = 0; i < prevPathfindingQueue.size(); i++)
			{
				prevPathfindingQueue.pop();
			}
		}
	}

	while (!pathfindingQueue.empty())
	{
		pathfindingQueue.pop();
	}

	return skillRangeList;
}

std::vector<TileInfo> SkillSystem::AllAttackSkillRange(Character * _character)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	std::vector<TileInfo> skillRangeList;

	{
		std::list<MoveInfo> maxMoveList = GAMESYS->MaxMoveFinder(_character);

		for (auto a : maxMoveList)
		{
			TileInfo tileInfo;
			tileInfo.tile = a.tileCell;
			tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
			tileInfo.tileImg->SetX(a.tileCell->GetPosition().x);
			tileInfo.tileImg->SetY(a.tileCell->GetPosition().y);
			tileInfo.distance = a.distance;
			skillRangeList.push_back(tileInfo);
		}
	}

	return skillRangeList;
}

std::vector<TileInfo> SkillSystem::StraightAttackSkillRange(Character * _character)
{

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	std::vector<TileInfo> attackList;
	int distance = 1;

	TilePoint tilePosition = _character->GetTilePosition();

	int count = _character->GetDistance();
	while (count != 0)
	{
		TilePoint currentTilePosition = tilePosition;
		TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection::DIR_LEFT));
		TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

		if (searchTilePosision.x < 0 || searchTilePosision.x >= map->GetWidth() ||
			searchTilePosision.y < 0 || searchTilePosision.y >= map->GetHeight())
		{
			continue;
		}
		TileInfo tileInfo;
		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
		tileInfo.distance = distance;
		attackList.push_back(tileInfo);

		count--;
		distance++;
		tilePosition = searchTilePosision;
	}

	count = _character->GetDistance();
	distance = 1;

	tilePosition = _character->GetTilePosition();

	while (count != 0)
	{
		TilePoint currentTilePosition = tilePosition;
		TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection::DIR_DOWN));
		TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

		if (searchTilePosision.x < 0 || searchTilePosision.x >= map->GetWidth() ||
			searchTilePosision.y < 0 || searchTilePosision.y >= map->GetHeight())
		{
			continue;
		}
		TileInfo tileInfo;
		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
		tileInfo.distance = distance;
		attackList.push_back(tileInfo);

		count--;
		distance++;
		tilePosition = searchTilePosision;
	}

	count = _character->GetDistance();
	distance = 1;
	tilePosition = _character->GetTilePosition();
	while (count != 0)
	{
		TilePoint currentTilePosition = tilePosition;
		TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection::DIR_RIGHT));
		TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

		if (searchTilePosision.x < 0 || searchTilePosision.x >= map->GetWidth() ||
			searchTilePosision.y < 0 || searchTilePosision.y >= map->GetHeight())
		{
			continue;
		}
		TileInfo tileInfo;
		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
		tileInfo.distance = distance;
		attackList.push_back(tileInfo);

		count--;
		distance++;
		tilePosition = searchTilePosision;
	}

	count = _character->GetDistance();
	distance = 1;
	tilePosition = _character->GetTilePosition();
	while (count != 0)
	{
		TilePoint currentTilePosition = tilePosition;
		TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection::DIR_UP));
		TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

		if (searchTilePosision.x < 0 || searchTilePosision.x >= map->GetWidth() ||
			searchTilePosision.y < 0 || searchTilePosision.y >= map->GetHeight())
		{
			continue;
		}
		TileInfo tileInfo;
		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
		tileInfo.distance = distance;
		attackList.push_back(tileInfo);

		count--;
		distance++;
		tilePosition = searchTilePosision;
	}

	count = _character->GetDistance();
	distance = 1;

	return attackList;
}

std::vector<TileInfo> SkillSystem::BuffSkillRange(Character * _character)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	std::vector<TileInfo> skillRangeList;

	{
		std::list<MoveInfo> maxMoveList = GAMESYS->MaxMoveFinder(_character);

		for (auto a : maxMoveList)
		{
			TileInfo tileInfo;
			tileInfo.tile = a.tileCell;
			tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
			tileInfo.tileImg->SetX(a.tileCell->GetPosition().x);
			tileInfo.tileImg->SetY(a.tileCell->GetPosition().y);
			tileInfo.distance = a.distance;
			skillRangeList.push_back(tileInfo);
		}
	}

	return skillRangeList;
}
