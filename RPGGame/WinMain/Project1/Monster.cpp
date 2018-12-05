#include "Game.h"


#include "Monster.h"

#include "Map.h"	


Monster::Monster(std::string _name, float _deep)
	: Character(_name, _deep)
{

}


Monster::~Monster()
{
}

bool Monster::Init()
{
	{
		isLive = true;
		img = IMAGEMANAGER->FindImage("Evil");
		img->SetX(48);
		img->SetY(48);
		img->SetFrameX(0);
		img->SetFrameY(0);

		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
		{
			if (NULL != map)
			{
				TilePoint tilePos;
				tilePos.x = 5;
				tilePos.y = 6;


				tilePosition = tilePos;
				map->SetTileComponent(tilePosition, this,true);

			}
		}

		//act = new Action();
		//act->Init();

		//act->MoveTo(img, 50, 50, 10.0f);

		InitState();
		eType = eStateType::ST_IDLE;
		ChangeState(eType);

	}
	return true;
}

void Monster::UpdateAI()
{
}
