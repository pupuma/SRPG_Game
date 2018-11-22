#include "Game.h"
#include "Component.h"



Component::Component(std::string _name)
{
	type = eComponentType::CT_DEFAULT;

	name = _name;
	COMSYS->AddComponent(name, this);
	tilePosition = { 0,0 };
	iMaxMoving = 0;

}


Component::~Component()
{
}

void Component::ReceiveMsg(const sMessageParam & _param)
{
	if (TEXT("Collision") == _param.message)
	{
		// 충돌처리
	}
}

void Component::SetPosition(POINT _pos)
{
	position = _pos; 
	//int rcPosX = _pos.x + (((_pos.x + 48) - _pos.x) / 2);
	//int rcPosY = _pos.y + (((_pos.y + 48) - _pos.y) / 2);


}
