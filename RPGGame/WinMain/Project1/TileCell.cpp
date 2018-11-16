#include "Game.h"
#include "TileCell.h"



TileCell::TileCell()
{
}


TileCell::~TileCell()
{
}

bool TileCell::Init(int _tileX, int _tileY)
{
	return false;
}

void TileCell::Update()
{
}

void TileCell::Render()
{
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
