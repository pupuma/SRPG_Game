#pragma once


class ProgressBar;

class SpaceShip
{
private:
	RECT				rc;
	POINT				pt;
	Image*				image;
	ProgressBar*		hpBar;

	int					speed;
	float				curHp;
	float				maxHp;
public:
	SpaceShip();
	~SpaceShip();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
};

