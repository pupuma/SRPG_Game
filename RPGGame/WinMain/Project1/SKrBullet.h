#pragma once
class SKrBullet
{
private:
	float x, y;
	float speed;
	float angle;
	int radius;
	bool isFire;
public:
	SKrBullet();
	~SKrBullet();
public:
	void Init(float _radius, float  _speed, bool isFIre);
public:
	bool IsFire() { return isFire; }
	void SetFire(bool _isFire) { isFire = _isFire; }
	void SetPosX(float _x) { x = _x; }
	void SetPosY(float _y) { y = _y; }
	void SetAngle(float _angle) { angle = _angle; }
	float GetAngle() { return angle; }
	float GetPosX() { return x; }
	float GetPosY() { return y; }
	float GetSpeed() { return speed; }
	float GetDiameter() { return radius * 2; }
	float GetRadius() { return radius; }

};

