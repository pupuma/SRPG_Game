#pragma once
class Action
{
private:
	Image * image;
	
	float startX, startY;
	float endX, endY;

	float angle;

	float travelRange;
	float worldTimeCount;
	float time;

	bool isMoving;

public:
	Action();
	~Action();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

public:
	void MoveTo(Image* _image, float _endX, float _endY, float _time);
	void Moving();
public:
	bool GetIsMoving() { return isMoving; }
};

