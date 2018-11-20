#include "Game.h"
#include "State.h"
#include "Character.h"

#include "Map.h"
#include "TileCell.h"

State::State(Character* _character)
	: character(_character)
{
	distSize = 0;
	nextState = eStateType::ST_NONE;
}


State::~State()
{
}

void State::Start()
{
	nextState = eStateType::ST_NONE;
	distSize = character->GetMaxMoving();
}

void State::Update()
{

}

void State::Render(HDC hdc)
{
	std::list<TileInfo>::iterator it;
	for (it = tileCellOpenList.begin(); it != tileCellOpenList.end(); it++)
	{
		(*it).tileImg->Render(hdc, (*it).tile->GetPosition().x, (*it).tile->GetPosition().y);
		//(*it).tile->Render(hdc);
		//Image* img = new Image();
		//img->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);
		//img->SetX((*it)->GetPosition().x);
		//img->SetY((*it)->GetPosition().y);

		//int posX = img->GetX();
		//int posY = img->GetY();
		//img->AlphaRender(hdc, 50);
		//img->Render(hdc, posX, posY);
	}
}

void State::Release()
{
}

void State::Reset()
{
}

void State::PathFindingIdle()
{
	TilePoint startPos = character->GetTilePosition();

	MovingAbleTile(distSize, startPos);


}

void State::PathFindingMove()
{
}

void State::MovingAbleTile(int _distSize, TilePoint _prevPos)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	std::vector<std::vector<TileCell*>> tileArray = map->GetTileArray();

	
	if (_distSize <= 0)
	{
		return;
	}

	{
		TilePoint upTile = { _prevPos.x , _prevPos.y - 1 };
		TilePoint downTile = { _prevPos.x , _prevPos.y + 1 };
		TilePoint leftTile = { _prevPos.x - 1, _prevPos.y };
		TilePoint rightTile = { _prevPos.x + 1,_prevPos.y };

		if (tileArray[upTile.y][upTile.x] != NULL && upTile.y > 0)
		{
			tileInfo.tile = tileArray[upTile.y][upTile.x];
			tileInfo.tileImg = new Image();
			tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

			tileInfo.tileImg->SetX(tileArray[upTile.y][upTile.x]->GetPosition().x);
			tileInfo.tileImg->SetY(tileArray[upTile.y][upTile.x]->GetPosition().y);

			tileCellOpenList.push_back(tileInfo);
			
			MovingAbleTile(_distSize - 1, upTile);
		}

		if (tileArray[downTile.y][downTile.x] != NULL && downTile.y < 33)
		{
			tileInfo.tile = tileArray[downTile.y][downTile.x];
			tileInfo.tileImg = new Image();
			tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

			tileInfo.tileImg->SetX(tileArray[downTile.y][downTile.x]->GetPosition().x);
			tileInfo.tileImg->SetY(tileArray[downTile.y][downTile.x]->GetPosition().y);

			tileCellOpenList.push_back(tileInfo);

			MovingAbleTile(_distSize - 1, downTile);
		}

		if (tileArray[leftTile.y][leftTile.x] != NULL && leftTile.x > 0)
		{
			tileInfo.tile = tileArray[leftTile.y][leftTile.x];
			tileInfo.tileImg = new Image();
			tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

			tileInfo.tileImg->SetX(tileArray[leftTile.y][leftTile.x]->GetPosition().x);
			tileInfo.tileImg->SetY(tileArray[leftTile.y][leftTile.x]->GetPosition().y);

			tileCellOpenList.push_back(tileInfo);

			MovingAbleTile(_distSize - 1, leftTile);
		}

		if (tileArray[rightTile.y][rightTile.x] != NULL && rightTile.x  < 33)
		{
			tileInfo.tile = tileArray[rightTile.y][rightTile.x];
			tileInfo.tileImg = new Image();
			tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

			tileInfo.tileImg->SetX(tileArray[rightTile.y][rightTile.x]->GetPosition().x);
			tileInfo.tileImg->SetY(tileArray[rightTile.y][rightTile.x]->GetPosition().y);

			tileCellOpenList.push_back(tileInfo);

			MovingAbleTile(_distSize - 1, rightTile);
		}

	}
}
