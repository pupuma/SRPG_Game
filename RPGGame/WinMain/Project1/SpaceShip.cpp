#include "Game.h"
#include "SpaceShip.h"
#include "ProgressBar.h"

SpaceShip::SpaceShip()
{

}


SpaceShip::~SpaceShip()
{

}

bool SpaceShip::Init()
{
	image = IMAGEMANAGER->FindImage(TEXT("Player"));
	
	pt.x = WINSIZEX / 2;
	pt.y = WINSIZEY - 100;

	image->SetX(pt.x);
	image->SetY(pt.y);

	speed = 5;

	rc = RectMakeCenter(pt.x, pt.y, image->GetWidth(), image->GetHeight());

	curHp = maxHp = 100;

	hpBar = new ProgressBar();
	hpBar->Init(image->GetX(), image->GetY() - 20, 52, 10);
	hpBar->SetGauge(curHp, maxHp);

	return true;
}

void SpaceShip::Release()
{
	hpBar->Release();
}

void SpaceShip::Update()
{
	// MOVE
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		pt.x -= speed;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		pt.x += speed;
	}

	rc = RectMakeCenter(pt.x, pt.y, image->GetWidth(), image->GetHeight());

	// HP Bar
	hpBar->SetX(rc.left);
	hpBar->SetY(rc.top - 20);
	hpBar->SetGauge(curHp, maxHp);
	hpBar->Update();
}

void SpaceShip::Render(HDC hdc)
{
	image->Render(hdc, rc.left, rc.top);
	hpBar->Render(hdc);
}
