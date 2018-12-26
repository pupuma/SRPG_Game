#include "Game.h"
#include "GameSystem.h"

#include "Map.h"
#include "TileCell.h"
#include "Character.h"
#include "GameSystem.h"

#include "NaviGationSystem.h"
#include "Player.h"
#include "GameTurnManager.h"
#include "Component.h"


GameSystem::GameSystem()
{

}


GameSystem::~GameSystem()
{
}

void GameSystem::Init()
{
	hpDrinkCount = 0;
	mpDrinkCount = 0;
	isAction = false;
	isAttacking = false;
	round = 1;
	index = 0;
	currentCharacterIndex = 0;
	isMove = false;
	isHeal = false;
	isClickCharacter = false;
	isItem = false;
	{

		std::vector<std::string> recordList = RESOURCEMANAGER->FindScript(TEXT("SkillInfo"));

		TCHAR record[1000];
		TCHAR* token;
		eJobClass job;
		int skillNumber;
		int skillDamage;
		std::string text;
		int frameX;
		int frameY;
		int iLine = 1;

		while (iLine <= recordList.size() - 1)
		{
			strcpy_s(record, recordList[iLine].c_str());

			token = strtok(record, ",");
			job = (eJobClass)atoi(token);

			token = strtok(NULL, ",");
			skillNumber = atoi(token);

			token = strtok(NULL, ",");
			skillDamage = atoi(token);

			token = strtok(NULL, ",");
			text = token;

			token = strtok(NULL, ",");
			frameX = atoi(token);


			token = strtok(NULL, ",");
			frameY = atoi(token);



			skillInfo.jobs = job;
			skillInfo.number = skillNumber;
			skillInfo.damage = skillDamage;
			skillInfo.text = text;
			skillInfo.frameX = frameX;
			skillInfo.frameY = frameY;
			
			m_Skill[iLine] = skillInfo;
			iLine++;

		}
	}
}
void GameSystem::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

		TileCell* tile = map->FindTileCellByMousePosition(_ptMouse.x, _ptMouse.y);
		if (tile != NULL)
		{
			saveClickTile = tile;
			std::list<Component*>::iterator it;
			std::list<Component*> comList = tile->GetTileComponentList();

			for (it = comList.begin(); it != comList.end(); it++)
			{
				if (comList.size() >= 2)
				{
					if ((*it)->GetComponetType() == eComponentType::CT_PLAYER ||
						(*it)->GetComponetType() == eComponentType::CT_MONSTER ||
						(*it)->GetComponetType() == eComponentType::CT_NPC)
					{
						//saveClickMousePos = _ptMouse;

						isClickCharacter = true;
						return;
					}
				}
			}
		}
	}
	
	// 저장된 정보를 출력
	// 이미지 정보 및 체력, MP, AP 정보 출력 
}
void GameSystem::Reset()
{
	for (auto a : playerList)
	{
		//a->Release();
	}
	playerList.clear();

	for (auto a :npcList)
	{
	//	a->Release();
	}
	npcList.clear();

	for (auto a : monsterList)
	{
		//a->Release();
	}
	monsterList.clear();

	characterList.clear();
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

std::list<MoveInfo> GameSystem::MaxMoveFinder(Character* _target)
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


	std::vector<int> dataList;
	int data = 0;
	for (auto a : selectTargetList)
	{
		data = UTIL::GetDistance(_character->GetTilePosition().x, _character->GetTilePosition().y,
			a->GetTilePosition().x, a->GetTilePosition().y);
		dataList.push_back(data);
	}

	int count = 0;
	Character* temp2 = 0;
	for (size_t i = 0; i < dataList.size(); i++)
	{
		for (size_t j = 0; j < dataList.size() - 1; j++)
		{
			if (dataList[i] < dataList[j])
			{
				temp2 = selectTargetList[j];
				selectTargetList[j] = selectTargetList[j + 1];
				selectTargetList[j + 1] = temp2;            // 다음 요소로 보냄
			}
		}
	}

	//
	TileCell* tileCell = NULL;


	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	targetTileCell = map->FindTileCell(selectTargetList[index]->GetTilePosition());
	std::list<TileInfo> finderList = map->GetOpenTileCellList();

	map->MapSearchClear();

	{
		std::list<MoveInfo>::iterator it_move;
		for (it_move = moveList.begin(); it_move != moveList.end(); it_move++)
		{
			for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
			{
				TilePoint currentTilePosition = selectTargetList[index]->GetTilePosition();
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
	// 캐릭터 
	//characterList[0];
	TileCell* tileCell = NULL;
	
	//
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	std::vector<int> dataList;
	int data = 0;
	for (auto a : playerList)
	{
		data = UTIL::GetDistance(_character->GetTilePosition().x, _character->GetTilePosition().y,
			a->GetTilePosition().x, a->GetTilePosition().y);
		dataList.push_back(data);
	}

	int count = 0;
	Character* temp2 = 0;
	for (size_t i = 0; i < dataList.size(); i++)
	{
		for (size_t j = 0; j < dataList.size() - 1; j++)
		{
			if (dataList[i] < dataList[j])
			{
				temp2 = playerList[j];
				playerList[j] = playerList[j + 1];
				playerList[j + 1] = temp2;            // 다음 요소로 보냄
			}
		}
	}

	TileCell* target;
	if (temp2 != NULL)
	{
		target = map->FindTileCell(temp2->GetTilePosition());

	}
	else
	{
		target = map->FindTileCell(playerList[0]->GetTilePosition());

	}
	_character->SetTargetCharacterTileCell(target);


	int distanceCount = 0;
	// 내가 갈 수 없는 상황 
	for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
	{
		TilePoint currentTilePosition = _character->GetTilePosition();
		TilePoint searchTilePosision = map->GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
		TileCell*  searchTileCell = map->FindTileCell(searchTilePosision);

		if (searchTilePosision.x < 0 || searchTilePosision.x >= width ||
			searchTilePosision.y < 0 || searchTilePosision.y >= height)
		{
			distanceCount++;
			continue;
		}


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

		if (searchTilePosision.x < 0 || searchTilePosision.x >= width ||
			searchTilePosision.y < 0 || searchTilePosision.y >= height)
		{
			distanceCount++;

			continue;
		}


		if (!searchTileCell->CanMove())
		{
			distanceCount++;
		}
	}

	//다른 타겟 공격 
	if (distanceCount >= 4)
	{
		return NULL;
	}


	// 수정 1 
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

	std::vector<int> dataList;
	int data = 0;
	for (auto a : selectTargetList)
	{
		data = UTIL::GetDistance(_character->GetTilePosition().x, _character->GetTilePosition().y,
			a->GetTilePosition().x, a->GetTilePosition().y);
		dataList.push_back(data);
	}

	int count = 0;
	Character* temp = 0;
	for (size_t i = 0; i < dataList.size(); i++)
	{
		for (size_t j = 0; j < dataList.size() - 1; j++)
		{
			if (dataList[i] > dataList[j])
			{
				temp = selectTargetList[j];
				selectTargetList[j] = selectTargetList[j + 1];
				selectTargetList[j + 1] = temp;            // 다음 요소로 보냄
			}
		}
	}

	if(NULL == _character->GetTargetCharacterTileCell())
	{
		if (!selectTargetList.empty())
		{
			for (auto a : attackList)
			{
				if (a.tile->GetTilePosition() == selectTargetList[index]->GetTilePosition())
				{
					_character->SetTargetCharacterTileCell(map->FindTileCell(selectTargetList[index]->GetTilePosition()));
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
		if (!selectTargetList.empty())
		{
			for (auto a : attackList)
			{
				if (a.tile->GetTilePosition() == selectTargetList[index]->GetTilePosition())
				{
					_character->SetTargetCharacterTileCell(map->FindTileCell(selectTargetList[index]->GetTilePosition()));
					break;
				}
			}
		}
		//_character->SetTargetCharacterTileCell(map->FindTileCell(playerList[0]->GetTilePosition()));

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
			if ((*it_move).tileCell->GetTilePosition() == playerList[i]->GetTilePosition() && playerList[i]->IsLive())
			{
				selectTargetList.push_back(playerList[i]);
			}
		}

		for (size_t i = 0; i < npcList.size(); i++)
		{
			if ((*it_move).tileCell->GetTilePosition() == npcList[i]->GetTilePosition() || npcList[i]->IsLive())
			{
				selectTargetList.push_back(npcList[i]);
			}
		}
	}
}

void GameSystem::SkillActivation()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	TileCell* tileCell = NULL;
	std::vector<Character*> characterList = GAMESYS->GetCharacterList();
	Character* turnCharacter = NULL;
	
	//

	std::vector<Component*> targetList;
	std::vector<TileInfo> skillList = map->GetSkillList();



	for (auto a : skillList)
	{
		std::list<Component*> tileComponentList = a.tile->GetTileComponentList();
		for (auto it : tileComponentList)
		{
			targetList.push_back(it);
		}

	}



	//
	int index = 0;
	if (!characterList.empty())
	{
		for (size_t i = 0; i < characterList.size(); i++, index++)
		{
			if (characterList[index]->IsTurn() && characterList[i]->GetComponetType() == eComponentType::CT_PLAYER)
			{
				characterList[index]->SetTarget(targetList);
				characterList[index]->ChangeState(eStateType::ST_SKILL);
				GAMESYS->SetMove(false);
				break;
			}
		}
	}

	targetList.clear();

}

std::vector<Component*> GameSystem::SkillListTarget(std::vector<Component*> _list, Character* _character)
{
	std::vector<Component*> targetList;

	for (auto a : _list)
	{
		if (!IsHeal())
		{
			if (a->GetComponetType() != _character->GetComponetType())
			{
				targetList.push_back(a);
			}
		}
		else
		{
			if (a->GetComponetType() == _character->GetComponetType())
			{
				targetList.push_back(a);
			}
		}
		
	}


	return targetList;
}

bool GameSystem::GameOver()
{
	if (!playerList.empty())
	{
		int iCount = playerList.size();
		for (auto a : playerList)
		{
			if (!a->IsLive())
			{
				iCount--;
			}
		}

		if (iCount <= 0)
		{
			return true;
		}
	}
	
	return false;
}

bool GameSystem::GameClear()
{
	if (!monsterList.empty())
	{
		int iCount = monsterList.size();
		for (auto a : monsterList)
		{
			if (!a->IsLive())
			{
				iCount--;
			}
		}
		
		if (iCount <= 0)
		{
			return true;
		}
	}

	return false;
}

Image* GameSystem::FindCharacterImage(int _index, Character* _character)
{
	Image* img = NULL;
	if (_character->GetComponetType() == eComponentType::CT_PLAYER)
	{
		switch (_index)
		{
		case 1:
			img = IMAGEMANAGER->FindImage(TEXT("Actor1"));
			break;
		case 2:
			img = IMAGEMANAGER->FindImage(TEXT("Actor2"));
			break;
		case 3:
			img = IMAGEMANAGER->FindImage(TEXT("Actor3"));
			break;
		}
	}
	else if (_character->GetComponetType() == eComponentType::CT_MONSTER)
	{
		switch (_index)
		{
		case 1:
			img = IMAGEMANAGER->FindImage(TEXT("Monster"));
			break;
		case 2:
			img = IMAGEMANAGER->FindImage(TEXT("Evil"));
			break;
		case 3:
			img = IMAGEMANAGER->FindImage(TEXT("Evil"));
			break;
		}
	}
	else if (_character->GetComponetType() == eComponentType::CT_NPC)
	{
		switch (_index)
		{
		case 1:
			img = IMAGEMANAGER->FindImage(TEXT("Actor2"));
			break;
		case 2:
			img = IMAGEMANAGER->FindImage(TEXT("Actor2"));
			break;
		case 3:
			img = IMAGEMANAGER->FindImage(TEXT("Actor2"));
			break;
		}
	}
	return img;

}

void GameSystem::DeleteCharacter(Character * _character)
{
	std::vector<Character*>::iterator it;
	for (it = characterList.begin(); it != characterList.end();it++ )
	{
		if ((*it) == _character)
		{
			it = characterList.erase(it++);
			break;
		}
	}
}

bool GameSystem::SkillCheck(int _index)
{
	Character* character = GameTurnManager::GetSingleton()->GetTurn();

	switch (_index)
	{
	case 1:
		if (character->GetMp() >= 10)
		{
			return true;
		}
		break;
	case 2:
		if (character->GetMp() >= 20)
		{
			return true;
		}
		break;
	case 3:
		if (character->GetMp() >= 30)
		{
			return true;
		}
		break;
	}
	return false;
}

