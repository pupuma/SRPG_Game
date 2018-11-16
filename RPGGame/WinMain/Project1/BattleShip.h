#pragma once
class BattleShip
{
private:
	Image*		image;
	RECT		rc;
	float		x, y;
	float		angle;
	float		speed;

public:
	BattleShip();
	~BattleShip();
public:
	bool Init(const std::string _imageName, int _x, int _y );
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void Draw(HDC hdc);
	void Input();
	void Move();

};

