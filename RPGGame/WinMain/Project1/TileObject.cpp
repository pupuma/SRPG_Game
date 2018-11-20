#include "Game.h"
#include "TileObject.h"


TileObject::TileObject(std::string _name, Image * _image, int _tileX, int _tileY) 
	: Component(_name)
{
	image = _image;
	tilePosition.x = _tileX;
	tilePosition.y = _tileY;
	
}

TileObject::~TileObject()
{
}

bool TileObject::Init()
{
	return true;
}

void TileObject::Deinit()
{
}

void TileObject::Update()
{
}

void TileObject::Render(HDC hdc)
{
	image->FrameRender(hdc, position.x, position.y);
}

void TileObject::Release()
{
}

void TileObject::Reset()
{
}
