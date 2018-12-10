#include "Game.h"


#include "Monster.h"

#include "Map.h"	


Monster::Monster(std::string _name, float _deep)
	: Character(_name, _deep)
{
	type = CT_MONSTER;

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

	}
	return true;
}

void Monster::UpdateAI()
{
}



void Monster::AttackPattern()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

	map->SetAttackRange();
}

