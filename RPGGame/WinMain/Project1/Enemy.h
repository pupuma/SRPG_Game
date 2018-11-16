#pragma once
class Enemy
{
private:
	Image*		_enemy;
	Animation*	_ani;
	
	RECT		_rc;
	POINT		_pt;

	int			speed;
	float		angle;

public:
	Enemy();
	~Enemy();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
};

