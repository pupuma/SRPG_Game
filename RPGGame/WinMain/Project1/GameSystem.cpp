#include "Game.h"
#include "GameSystem.h"

#include "Map.h"
#include "TileCell.h"
#include "Character.h"
#include "GameSystem.h"

#include "NaviGationSystem.h"



GameSystem::GameSystem()
{

}


GameSystem::~GameSystem()
{
}

void GameSystem::Init()
{
	isAction = false;
	isAttacking = false;
	round = 1;
	currentCharacterIndex = 0;


}
void GameSystem::SetMousePosition(LPARAM lParam)
{
	_ptMouse.x = LOWORD(lParam);
	_ptMouse.y = HIWORD(lParam);
}


POINT GameSystem::GetMousePosition()
{
	return _ptMouse;
}
void GameSystem::ResetTarget()
{
	g_Map->ResetViewer();
}
void GameSystem::SetMap(Map * _map)
{
	g_Map = _map;
}
bool GameSystem::TargetCheck(std::vector<Component*> _list, Character* _character)
{
	// AttackRange
	std::vector<TileInfo> tileAttackList = g_Map->GetAttackList();

	// 리스트 안에 플레이어가 있으면 안된다. 
	eComponentType characterType = _character->GetComponetType();
	for (auto a : _list)
	{
		eComponentType type = a->GetComponetType();
		if (type == characterType)
		{
			return false;
		}
	}

	// target 
	for (auto a : _list)
	{
		for (auto b : tileAttackList)
		{
			temp = b.tile->GetTilePosition();
			if (temp == a->GetTilePosition())
			{
				return true;
			}
		}
	}


	return false;
}
void GameSystem::AddCharacterList(Character * _character)
{
	switch (_character->GetComponetType())
	{
	case eComponentType::CT_PLAYER:
		playerList.push_back(_character);
		break;
	case eComponentType::CT_MONSTER:
		monsterList.push_back(_character);
		break;
	case eComponentType::CT_NPC:
		npcList.push_back(_character);
		break;
	}

	characterList.push_back(_character);
}
	
void GameSystem::GameTurn()
{
	/*unsigned int characterSize = characterList.size();

	characterList[currentCharacterIndex]->SetTurn(true);
	currentCharacterIndex++;
	round++;

	if (currentCharacterIndex >= characterSize)
	{
		currentCharacterIndex = 0;
	}*/

	characterList[0]->SetTurn(true);
	characterList[1]->SetTurn(false);

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	g_Map->ResetViewer();
	g_Map->SetViewer((Component*)characterList[0]);


}
eDirection GameSystem::LookAtCharacter(std::vector<Component*> _list, Character* _character)
{
	eDirection dir =  eDirection::DIR_LEFT;
	std::vector<Component*>::iterator it = _list.begin();

	if ((*it)->GetTilePosition().x < _character->GetTilePosition().x)
	{
		dir = eDirection::DIR_LEFT;
	}
	else if ((*it)->GetTilePosition().x > _character->GetTilePosition().x)
	{
		dir = eDirection::DIR_RIGHT;
	}


	if ((*it)->GetTilePosition().y < _character->GetTilePosition().y)
	{
		dir = eDirection::DIR_DOWN;
	}

	if ((*it)->GetTilePosition().y < _character->GetTilePosition().y)
	{
		dir = eDirection::DIR_UP;
	}
	return dir;
}
TileCell * GameSystem::FindPriorityTarget(Character* _character)
{
	// 
	// 캐릭터와 적일 수 있다.. 

	TileCell* tile = NULL;
	
	std::list<MoveInfo> characterMoveList = MaxMoveFinder(_character);

	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

		std::list<MoveInfo>::iterator it_move;

		for (it_move = characterMoveList.begin(); it_move != characterMoveList.end(); it_move++)
		{
			for (size_t i = 0; i < playerList.size(); i++)
			{
				if ((*it_move).tileCell->GetTilePosition() == playerList[i]->GetTilePosition())
				{
					selectTargetList.push_back(playerList[i]);
				}
			}

			for (size_t i = 0; i < npcList.size(); i++)
			{
				if ((*it_move).tileCell->GetTilePosition() == npcList[i]->GetTilePosition())
				{
					selectTargetList.push_back(npcList[i]);
				}
			}
		}

		if (!selectTargetList.empty())
		{
			tile = CharacterPrioritySort(_character);
		}
		else
		{
			tile = CharacterSelectTileCell(_character);
		}

	}
	return tile;
}

std::list<GameSystem::MoveInfo> GameSystem::MaxMoveFinder(Character* _target)
{
	{
		width = PARSING->GetTileWidth();
		height = PARSING->GetTIleHeight();

		int _distance = _target->GetDirection();
		TilePoint startPos = _target->GetTilePosition();
		
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
		map->MapSearchClear();
		TileCell* targetTileCell = map->FindTileCell(startPos);
		ResetMovefinding();
		// first
		for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
		{
			TilePoint currentTilePosition = targetTileCell->GetTilePosition();
			TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
			TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

			if (searchTilePosision.x < 0 || searchTilePosision.x > width ||
				searchTilePosision.y < 0 || searchTilePosision.y > height)
			{
				continue;
			}

			if (searchTilePosision.x == startPos.x && searchTilePosision.y == startPos.y ||
				map->FindTileCell(searchTilePosision)->IsSearchPathfinding() == true )
			{
				continue;
			}

			searchTileCell->SetSearchPathfinding(true);

			moveInfo.tileCell = searchTileCell;
			moveInfo.distance = _distance;
			moveList.push_back(moveInfo);

			std::pair<TileCell*, int> p_data;

			pathfindingQueue.push(searchTileCell);

		}
		_distance -= 1;
		// second 

		//
		//std::priority_queue<TileCell*> prevPathfindingQueue;
		std::queue<TileCell*> prevPathfindingQueue;

		while (_distance > 0)
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

					if (searchTilePosision.x == startPos.x && searchTilePosision.y == startPos.y ||
						map->FindTileCell(searchTilePosision)->IsSearchPathfinding() == true )
					{
						continue;
					}

					searchTileCell->SetSearchPathfinding(true);

					moveInfo.tileCell = searchTileCell;
					moveInfo.distance = _distance;
					moveList.push_back(moveInfo);

					std::pair<TileCell*, int> p_data;
					prevPathfindingQueue.push(searchTileCell);
				}
			}

			if (pathfindingQueue.empty())
			{
				_distance -= 1;
				pathfindingQueue = prevPathfindingQueue;
				for (size_t i = 0; i < prevPathfindingQueue.size(); i++)
				{
					prevPathfindingQueue.pop();
				}
			}

		}
	}

	{
		while (!pathfindingQueue.empty())
		{
			pathfindingQueue.pop();
		}
	}
		
	return moveList;
}

void GameSystem::ResetMovefinding()
{
	moveList.clear();
}

TileCell* GameSystem::CharacterPrioritySort(Character * _character)
{

	Character* temp = NULL;
	for (size_t i = 0; i < selectTargetList.size(); i++)    // 요소의 개수만큼 반복
	{
		for (size_t j = 0; j < selectTargetList.size() - 1; j++)   // 요소의 개수 - 1만큼 반복
		{
			if (selectTargetList[j]->GetHp() > selectTargetList[j + 1]->GetHp())          // 현재 요소의 값과 다음 요소의 값을 비교하여
			{                                 // 큰 값을
				temp = selectTargetList[j];
				selectTargetList[j] = selectTargetList[j + 1];
				selectTargetList[j + 1] = temp;            // 다음 요소로 보냄
			}
		}
	}


	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	
	targetTileCell = map->FindTileCell(selectTargetList[0]->GetTilePosition());
	TileCell* tileCell = NULL;
	std::list<TileInfo> finderList = map->GetOpenTileCellList();

	map->MapSearchClear();

	{
		std::list<MoveInfo>::iterator it_move;
		for (it_move = moveList.begin(); it_move != moveList.end(); it_move++)
		{
			
				for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
				{
					TilePoint currentTilePosition = selectTargetList[0]->GetTilePosition();
					TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
					TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

					for (auto a : finderList)
					{
						if ((*it_move).tileCell->GetTilePosition() == searchTileCell->GetTilePosition() &&
							a.tile->GetTilePosition() == (*it_move).tileCell->GetTilePosition())
						{
							tileCell = searchTileCell;
							return tileCell;
						}
					}
				}
		}
	}

	
	
	return tileCell;
}

TileCell* GameSystem::CharacterSelectTileCell(Character* _character)
{
	// 캐릭터 
	//characterList[0];
	TileCell* tileCell = NULL;
	tileCell = NaviGationSystem::GetSingleton()->AStarPathFinder(_character, characterList[0]);
	return tileCell;
}


