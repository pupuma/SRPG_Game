#include "Game.h"
#include "SKrBullet.h"



SKrBullet::SKrBullet()
{
}


SKrBullet::~SKrBullet()
{
}

void SKrBullet::Init(float _radius, float _speed, bool _isFire)
{
	radius = _radius;
	speed = _speed;
	isFire = _isFire;
}
