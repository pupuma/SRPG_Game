#include "Game.h"
#include "TileObject.h"


TileObject::TileObject(std::string _name, Image * _image, int _tileX, int _tileY, float _deep) 
	: Component(_name, _deep)
{
	image = _image;
	tilePosition.x = _tileX;
	tilePosition.y = _tileY;
	
	frameX = 0;
	frameY = 0;
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
	image->FrameRender(hdc, position.x - CAMERA->GetPosition()->x, position.y - CAMERA->GetPosition()->y,frameX, frameY);
}

void TileObject::Release()
{
	image = NULL;
}

void TileObject::Reset()
{
}

void TileObject::SetFramePos(int _frameX, int _frameY)
{
	frameX = _frameX;
	frameY = _frameY;
	image->SetFrameX(_frameX);
	image->SetFrameY(_frameY);

}
