#include "Game.h"
#include "Enemy.h"

#include "Animation.h"

#include "TextData.h"
Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

bool Enemy::Init()
{
	_enemy = IMAGEMANAGER->FindImage(TEXT("UFO"));
	assert(_enemy != NULL);

	std::vector<std::string> vPos;
	vPos = TEXTDATA->TextLoad(TEXT("../Resource/Text/EnemyData.txt"));


	//_pt.x = WINSIZEX / 2; 
	//_pt.y = 100;

	_pt.x = atoi(vPos[0].c_str());
	_pt.y = atoi(vPos[1].c_str());

	_rc = RectMakeCenter(_pt.x, _pt.y, _enemy->GetFrameWidth(), _enemy->GetFrameHeight());
	angle = PI;
	speed = 3;

	_ani = new Animation();
	_ani->Init(_enemy);
	_ani->SetDefPlayFrame(false, true);

	_ani->SetFPS(1);
	_ani->Start();
	
	return true;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	// 왔다리 갔다리 
	_pt.x += cosf(angle) * speed;
	_pt.y += -sinf(angle) * speed;

	if ((_pt.x - _enemy->GetFrameWidth() / 2) < 0)
	{
		angle = 0;
	}

	if ((_pt.x + _enemy->GetFrameWidth() / 2) > WINSIZEX)
	{
		angle = PI;
	}

	_rc = RectMakeCenter(_pt.x, _pt.y, _enemy->GetFrameWidth(), _enemy->GetFrameHeight());
	_ani->FrameUpdate(TIMEMANAGER->GetElapsedTime() * 10);
}

void Enemy::Render(HDC hdc)
{
	//_enemy->FrameRender(hdc, _rc.left, _rc.top);	
	_enemy->AniRender(hdc, _rc.left, _rc.top, _ani);
}

