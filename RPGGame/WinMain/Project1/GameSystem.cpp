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
	isMove = false;

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

	// ����Ʈ �ȿ� �÷��̾ ������ �ȵȴ�. 
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
	// ĳ���Ϳ� ���� �� �ִ�.. 
	selectTargetList.clear();

	TileCell* tile = NULL;

	{
		AddProioritySelectList(_character);

		

		

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

		int _distance = _target->GetDistance();
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

		while (!prevPathfindingQueue.empty())
		{
			prevPathfindingQueue.pop();

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

	for (size_t i = 0; i < selectTargetList.size(); i++)    // ����� ������ŭ �ݺ�
	{
		for (size_t j = 0; j < selectTargetList.size() - 1; j++)   // ����� ���� - 1��ŭ �ݺ�
		{
			if (selectTargetList[j]->GetHp() > selectTargetList[j + 1]->GetHp())          // ���� ����� ���� ���� ����� ���� ���Ͽ�
			{                                 // ū ����
				temp = selectTargetList[j];
				selectTargetList[j] = selectTargetList[j + 1];
				selectTargetList[j + 1] = temp;            // ���� ��ҷ� ����
			}
		}
	}

	//
	TileCell* tileCell = NULL;


	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	targetTileCell = map->FindTileCell(selectTargetList[0]->GetTilePosition());
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
					if (a.tile->GetTilePosition() == (*it_move).tileCell->GetTilePosition())
					{
						if (a.tile->GetTilePosition() == searchTileCell->GetTilePosition())
						{
							tileCell = searchTileCell;
							return tileCell;
						}
					}
				}
			}
		}

		// 
		tileCell = CharacterSelectTileCell(_character);
	}
	
	return tileCell;
}

TileCell* GameSystem::CharacterSelectTileCell(Character* _character)
{
	// ĳ���� 
	//characterList[0];
	TileCell* tileCell = NULL;
	
	//
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	TileCell* target = map->FindTileCell(playerList[0]->GetTilePosition());

	
	_character->SetTargetCharacterTileCell(target);

	int distanceCount = 0;
	// ���� �� �� ���� ��Ȳ 
	for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
	{
		TilePoint currentTilePosition = _character->GetTilePosition();
		TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
		TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

		if (!searchTileCell->CanMove())
		{
			distanceCount++;
		}
	}

	if (distanceCount >= 4)
	{
		return NULL;
	}

	distanceCount = 0;
	for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
	{
		TilePoint currentTilePosition = _character->GetTargetCharacterTileCell()->GetTilePosition();
		TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
		TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

		if (!searchTileCell->CanMove())
		{
			distanceCount++;
		}
	}

	//�ٸ� Ÿ�� ���� 
	if (distanceCount >= 4)
	{
		return NULL;
	}


	// ���� 1 
	//tileCell = NaviGationSystem::GetSingleton()->AStarPathFinder(_character, characterList[0]);
	tileCell = NaviGationSystem::GetSingleton()->AStarPathFinder(_character, _character->GetTargetCharacterTileCell());

	return tileCell;
}

bool GameSystem::AttackRangeCheck(Character* _character)
{
	_character->AttackPattern();

	AddProioritySelectList(_character);
	
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	
	std::vector<TileInfo> attackList = map->GetAttackList();


	if(NULL == _character->GetTargetCharacterTileCell())
	{
		if (!selectTargetList.empty())
		{
			for (auto a : attackList)
			{
				if (a.tile->GetTilePosition() == selectTargetList[0]->GetTilePosition())
				{
					_character->SetTargetCharacterTileCell(map->FindTileCell(selectTargetList[0]->GetTilePosition()));
					return true;
				}
			}
		}
		else
		{
			
		}
		
	}
	else
	{
		_character->SetTargetCharacterTileCell(map->FindTileCell(playerList[0]->GetTilePosition()));

		for (auto a : attackList)
		{
			if (a.tile->GetTilePosition() == _character->GetTargetCharacterTileCell()->GetTilePosition())
			{
				//_character->SetCharacterTileCell(map->FindTileCell(selectTargetList[0]->GetTilePosition()));
				return true;
			}
		}
	}
	
	return false;
}

void GameSystem::AddProioritySelectList(Character* _character)
{
	std::list<MoveInfo> characterMoveList = MaxMoveFinder(_character);

	selectTargetList.clear();

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
}



