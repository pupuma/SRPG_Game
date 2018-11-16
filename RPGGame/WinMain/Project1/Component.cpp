#include "Game.h"
#include "Component.h"



Component::Component(std::string _name)
{
	type = eComponentType::CT_DEFAULT;

	name = _name;
	COMSYS->AddComponent(name, this);
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
