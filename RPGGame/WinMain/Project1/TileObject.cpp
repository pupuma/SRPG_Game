#include "Game.h"
#include "TileObject.h"


TileObject::TileObject(std::string _name, Image * _image, int _tileX, int _tileY, float _deep) 
	: Component(_name, _deep)
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
	image->FrameRender(hdc, position.x - CAMERA->GetPosition()->x, position.y - CAMERA->GetPosition()->y);
}

void TileObject::Release()
{
}

void TileObject::Reset()
{
}
