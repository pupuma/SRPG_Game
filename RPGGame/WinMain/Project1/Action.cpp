#include "Game.h"
#include "Action.h"



Action::Action()
{
}


Action::~Action()
{
}

bool Action::Init()
{
	worldTimeCount = 0.f;
	isMoving = false;

	return true;
}

void Action::Release()
{
}

void Action::Update()
{
	Moving();
}

void Action::Render(HDC hdc)
{
	image->Render(hdc);
}

void Action::MoveTo(Image * _image, float _endX, float _endY, float _time)
{
	if (!isMoving)
	{
		image = _image;

		endX = _endX;
		endY = _endY;

		startX = image->GetX();
		startY = image->GetY();

		travelRange = UTIL::GetDistance(startX, startY, endX, endY);

		angle = UTIL::GetAngle(startX, startY, endX, endY);

		worldTimeCount = TIMEMANAGER->GetWorldTime();

		time = _time;

		isMoving = true;

	}
}

void Action::Moving()
{
	if (!isMoving)
	{
		return;
	}

	float elapsedTime = TIMEMANAGER->GetElapsedTime();

	float moveSpeed = (elapsedTime / time) * travelRange;

	image->SetX(image->GetX() + cosf(angle) * moveSpeed);
	image->SetY(image->GetY() + -sinf(angle) * moveSpeed);

	if (time + worldTimeCount <= TIMEMANAGER->GetWorldTime())
	{
		worldTimeCount += TIMEMANAGER->GetWorldTime();
	
		image->SetX(endX);
		image->SetY(endY);
	
		isMoving = false;
	}

}
