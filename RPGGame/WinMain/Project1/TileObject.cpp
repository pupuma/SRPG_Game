#include "Game.h"
#include "TileObject.h"



TileObject::TileObject(std::string _name)
	: Component(_name)
{
}


TileObject::~TileObject()
{
}

bool TileObject::Init()
{
	return false;
}

void TileObject::Deinit()
{
}

void TileObject::Update()
{
}

void TileObject::Render(HDC hdc)
{
}

void TileObject::Release()
{
}

void TileObject::Reset()
{
}
