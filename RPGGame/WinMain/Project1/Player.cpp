#include "Game.h"
#include "Player.h"

#include "Map.h"	
#include "State.h"
#include "TileCell.h"
#include "SkillSystem.h"



Player::Player(std::string _name, float _deep)
	: Character(_name,_deep)
{
	//isTurn = true;
	name = _name;

}


Player::~Player()
{
}

bool Player::Init()
{
	{
		job = eJobClass::JOB_ARCHER;

		isLive = true;
		img = IMAGEMANAGER->FindImage(TEXT("Actor1"));
		img->SetX(48);
		img->SetY(48);
		img->SetFrameX(0);
		img->SetFrameY(0);
		
		InitState();
		eType = eStateType::ST_PATH_IDLE;
		ChangeState(eType);
		iMaxHp = 100;
		iHp = 100;
	}

	return true;
}

bool Player::Init(int _index)
{

	{
		job = eJobClass::JOB_WARRIOR;
		faceNumber = _index;
		isLive = true;
		img = GAMESYS->FindCharacterImage(_index,this);
		img->SetX(48);
		img->SetY(48);
		img->SetFrameX(0);
		img->SetFrameY(0);

		InitState();
		eType = eStateType::ST_PATH_IDLE;
		ChangeState(eType);
		iMaxHp = 100;
		iHp = 100;
		iMaxMp = 50;
		iMp = 50;
		attackPoint = 10;
	}

	return true;
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
					isMoving = true;
					//TilePoint pos = { 7,7 };
					//MoveStart(pos);
					eType = eStateType::ST_MOVE;
					ChangeState(eStateType::ST_MOVE);
				}
			}

		}

	}
}

void Player::AttackPattern()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	//TileInfo tileInfo;
	std::vector<TileInfo> attackList;

	int distance = 1;
	switch (job)
	{
	case eJobClass::JOB_WARRIOR:
	{
		for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
		{
			TilePoint currentTilePosition = this->GetTilePosition();
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
	}
		break;
	case eJobClass::JOB_ARCHER:
	{
		//1
		std::list<MoveInfo> maxMoveList = GAMESYS->MaxMoveFinder(this);
		//std::list<MoveInfo>::iterator it;
		for (auto a : maxMoveList)
		{
			if (a.distance == 1)
			{
				TileInfo tileInfo;
				tileInfo.distance = a.distance;
				tileInfo.tile = a.tileCell;
				tileInfo.tileImg = IMAGEMANAGER->FindImage(TEXT("AttackTile"));
				attackList.push_back(tileInfo);

			}
		}

		//2
	}
		break;
	case eJobClass::JOB_HEALER:
	{
		for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
		{
			TilePoint currentTilePosition = this->GetTilePosition();
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
	}
		break;
	case eJobClass::JOB_MAGIC:
	{
		for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
		{
			TilePoint currentTilePosition = this->GetTilePosition();
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
	}
		
	}
	
	//attackList.clear();
	//
	//attackList = GAMESYS->BoxSkillRange(this);
	map->SetAttackRange(attackList);

	attackList.clear();
}

void Player::SkillPattern(int _number)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));


	if (job == eJobClass::JOB_WARRIOR)
	{
		switch (_number)
		{
		case 1:
			skillList1 = SkillSystem::GetSingleton()->NomalSkillRange(this);
			map->SetSkillRange(skillList1);
			break;
		case 2:
			skillList2 = SkillSystem::GetSingleton()->NomalSkillRange(this);
			map->SetSkillRange(skillList2);

			break;
		case 3:
			skillList3 = SkillSystem::GetSingleton()->BoxSkillRange(this);
			map->SetSkillRange(skillList3);

			break;
		}
	}
	else if (job == eJobClass::JOB_ARCHER)
	{
		switch (_number)
		{
		case 1:
			skillList1 = SkillSystem::GetSingleton()->NomalSkillRange(this);
			map->SetSkillRange(skillList1);
			// Damage
			break;
		case 2:
			skillList2 = SkillSystem::GetSingleton()->BoxSkillRange(this);
			map->SetSkillRange(skillList2);

			break;
		case 3:
			skillList3 = SkillSystem::GetSingleton()->StraightAttackSkillRange(this);
			map->SetSkillRange(skillList3);

			break;
		}
	}
	else if (job == eJobClass::JOB_HEALER)
	{
		switch (_number)
		{
		case 1:
			skillList1 = SkillSystem::GetSingleton()->NomalSkillRange(this);
			map->SetSkillRange(skillList1);

			break;
		case 2:
			skillList2 = SkillSystem::GetSingleton()->BoxSkillRange(this);
			map->SetSkillRange(skillList2);

			break;
		case 3:
			skillList3 = SkillSystem::GetSingleton()->BuffSkillRange(this);
			map->SetSkillRange(skillList3);

			break;
		}
	}
	else if (job == eJobClass::JOB_MAGIC)
	{
		switch (_number)
		{
		case 1:
			skillList1 = SkillSystem::GetSingleton()->NomalSkillRange(this);
			map->SetSkillRange(skillList1);

			break;
		case 2:
			skillList2 = SkillSystem::GetSingleton()->BoxSkillRange(this);
			map->SetSkillRange(skillList2);

			break;
		case 3:
			skillList3 = SkillSystem::GetSingleton()->AllAttackSkillRange(this);
			map->SetSkillRange(skillList3);

			break;
		}
	}
	
}
