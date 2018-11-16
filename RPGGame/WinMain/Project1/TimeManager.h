#pragma once
#include "SingletonBase.h"

class Timer;

class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer*	_timer;

public:
	TimeManager();
	~TimeManager();
public:
	bool Init();
	void Release();
	void Update(float lock = 0.0f);
	void Render(HDC hdc);
public:
	float GetElapsedTime() const;
	float GetWorldTime() const;
};

