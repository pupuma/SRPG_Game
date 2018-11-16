#include "Game.h"
#include "TimeManager.h"
#include "Timer.h"

TimeManager::TimeManager()
	: _timer(NULL)
{
}

TimeManager::~TimeManager()
{
}

bool TimeManager::Init()
{
	_timer = new Timer;
	_timer->Init();

	return true;
}

void TimeManager::Release()
{
	SAFE_DELETE(_timer);
	GetSingleton()->ReleaseSingleton();
}

void TimeManager::Update(float lock)
{
	if (_timer != NULL)
	{
		_timer->Tick(lock);
	}
}

void TimeManager::Render(HDC hdc)
{
	TCHAR str[256] = { 0, };

	std::string	frameRate;
	SetBkMode(hdc, TRANSPARENT);

#if defined(_DEBUG)
	{
		_stprintf(str, TEXT("Frame Per Sec : %d"), _timer->GetFrameRate());
		TextOut(hdc, 0, 0, str, _tcslen(str));

		_stprintf(str, TEXT("World Time : %f"), _timer->GetWorldTime());
		TextOut(hdc, 0, 20, str, _tcslen(str));

		_stprintf(str, TEXT("Elapsed Time : %f"), _timer->GetElapsedTime());
		TextOut(hdc, 0, 40, str, _tcslen(str));
	}
#else
	_stprintf(str, TEXT("Frame Per Sec : %d"), _timer->getFrameRate());
	TextOut(hdc, 0, 0, str, _tcslen(str));
#endif // #if defined(_DEBUG)
}

float TimeManager::GetElapsedTime() const
{
	return _timer->GetElapsedTime();
}

float TimeManager::GetWorldTime() const
{
	return _timer->GetWorldTime();
}
