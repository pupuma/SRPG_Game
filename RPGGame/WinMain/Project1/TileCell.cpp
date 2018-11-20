#include "Game.h"
#include "TileCell.h"



TileCell::TileCell()
{
	position = { 0,0 };
}


TileCell::~TileCell()
{
}

bool TileCell::Init(int _tileX, int _tileY)
{
	tilePostion.x = _tileX;
	tilePostion.y = _tileY;
	return true;
}

void TileCell::Update()
{
}

void TileCell::Render(HDC hdc)
{
	std::list<Component*>::iterator it;

	for (it = componentList.begin(); it != componentList.end(); it++)
	{
		(*it)->SetPosition(position);
		(*it)->Render(hdc);
	}
}

void TileCell::Release()
{
}

void TileCell::Reset()
{
}

void TileCell::AddComponent(Component * _component)
{
	componentList.push_back(_component);
}

void TileCell::RemoveComponent(Component * _component)
{
	componentList.remove(_component);

}
