#include "Game.h"
#include "BattleShip.h"



BattleShip::BattleShip()
{
}


BattleShip::~BattleShip()
{
}

bool BattleShip::Init(const std::string _imageName, int _x, int _y)
{
	image = IMAGEMANAGER->FindImage(_imageName);

	if (NULL == image)
	{
		return false;
	}

	this->x = _x;
	this->y = _y;

	angle = 0.0f;
	speed = 1.0f;

	rc = RectMakeCenter(x, y, image->GetFrameWidth(), image->GetFrameHeight());

	return true;
}

void BattleShip::Release()
{

}

void BattleShip::Update()
{
	Input();
	Move();
}

void BattleShip::Render(HDC hdc)
{
	Draw(hdc);
}

void BattleShip::Draw(HDC hdc)
{
	image->FrameRender(hdc, rc.left, rc.top);

#if defined(_DEBUG)
	TCHAR szTemp[128] = { 0, };
	_stprintf(szTemp, TEXT("Angle : %d, Speed $ %3.2f"), int(angle * 180 / PI), speed);
	TextOut(hdc, rc.left, rc.top - 15, szTemp, _tcslen(szTemp));

#endif // 
}

void BattleShip::Input()
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		if (angle >= PI2)
		{
			angle -= PI2;
		}

		angle += 0.05f;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		if (angle <= 0)
		{
			angle += PI2;
		}
		angle -= 0.05f;
	}
}

void BattleShip::Move()
{
	int			frame;
	//float		_angle;

	//_angle = angle + (PI / 16.f);

	if (angle > PI2)
	{
		angle -= PI2;
	}
	else if (angle <= 0)
	{
		angle += PI2;
	}

	//frame = int(_angle / (PI2 / 16.f));
	frame = int(angle / (PI2 / 16.f));

	image->SetFrameX(frame);
	
	float elapsedTime = TIMEMANAGER->GetElapsedTime();
	float moveSpeed = elapsedTime * 100;
	
	x += cosf(angle) * speed * moveSpeed;
	y += -sinf(angle) * speed * moveSpeed;

	rc = RectMakeCenter(x, y, image->GetFrameWidth(), image->GetFrameHeight());

}
