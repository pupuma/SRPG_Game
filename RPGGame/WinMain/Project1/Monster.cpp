#include "Game.h"


#include "Monster.h"

#include "Map.h"	
#include "TileCell.h"
#include "State.h"

Monster::Monster(std::string _name, float _deep)
	: Character(_name, _deep)
{
	type = CT_MONSTER;
	name = _name;

}


Monster::~Monster()
{
}

bool Monster::Init()
{
	{
		currentDirection = eDirection::DIR_DOWN;
		isLive = true;
		img = IMAGEMANAGER->FindImage("Evil");
		img->SetX(48);
		img->SetY(48);
		//img->SetFrameX(0);
		//mg->SetFrameY(0);

		//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
		//{
		//	if (NULL != map)
		//	{
		//		TilePoint tilePos;
		//		tilePos.x = 5;
		//		tilePos.y = 6;

		//		tilePosition = tilePos;
		//		map->SetTileComponent(tilePosition, this,true);
		//	}
		//}

		//act = new Action();
		//act->Init();

		//act->MoveTo(img, 50, 50, 10.0f);

		InitState();
		eType = eStateType::ST_PATH_NAVI;
		ChangeState(eType);

		//GAMESYS->SetMpBar();
	}
	return true;
}


bool Monster::Init(int _index)
{
	{
		currentDirection = eDirection::DIR_DOWN;
		faceNumber = _index;

		isLive = true;
		img = GAMESYS->FindCharacterImage(_index, this);
		img->SetX(48);
		img->SetY(48);
		img->SetFrameX(frameX);
		img->SetFrameY(frameY);

		InitState();
		eType = eStateType::ST_PATH_IDLE;
		ChangeState(eType);
		iMaxHp = 10;
		iHp = 10;
		iMp = 0;
		iMaxMp = 0;
	}

	return true;
}

void Monster::Render(HDC hdc)
{
	//img->Render(hdc);
	state->Render(hdc);

	if (eStateType::ST_DEAD != eType)
	{
		if (IsLive())
		{
			img->FrameRender(hdc, position.x - CAMERA->GetPosition()->x, position.y - CAMERA->GetPosition()->y,
				frameX, frameY);
		}

	}
		
}


void Monster::UpdateAI()
{
}



void Monster::AttackPattern()
{
	/*Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	map->SetAttackRange();*/

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	//TileInfo tileInfo;
	std::vector<TileInfo> attackList;


	int distance = 1;

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

	map->SetAttackRange(attackList);

	attackList.clear();

}

