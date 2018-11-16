#include "Game.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
}


ProgressBar::~ProgressBar()
{
}

bool ProgressBar::Init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	

	_rcProgress = RectMake(_x, _y, width, height);


	_progressBarTop = IMAGEMANAGER->AddImage(TEXT("FrontBar"), TEXT("../Resource/SpaceShip/hpBarTop.bmp"),
		_x, _y, width, height, true, COLOR_M);

	_progressBarBottom = IMAGEMANAGER->AddImage(TEXT("BackBar"), TEXT("../Resource/SpaceShip/hpBarBottom.bmp"),
		_x, _y, width, height, true, COLOR_M);

	_width = _progressBarTop->GetWidth();


	return true;
}

bool ProgressBar::Init(std::string strTop, std::string strBack, int x, int y, int width, int height)
{

	_x = x;
	_y = y;


	_rcProgress = RectMake(_x, _y, width, height);


	_progressBarTop = IMAGEMANAGER->FindImage(strTop);
	assert(_progressBarTop != NULL);

	_progressBarBottom = IMAGEMANAGER->FindImage(strBack);
	assert(_progressBarBottom != NULL);


	_width = _progressBarTop->GetWidth();


	return true;
}

void ProgressBar::Release()
{

}

void ProgressBar::Update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->GetWidth(), _progressBarTop->GetHeight());
}

void ProgressBar::Render(HDC hdc)
{
	//_progressBarTop
	_progressBarBottom->Render(hdc, _rcProgress.left + _progressBarBottom->GetWidth() / 2,
		_y + _progressBarBottom->GetHeight() / 2, 
		0, 0, _progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());

	_progressBarTop->Render(hdc, _rcProgress.left + _progressBarTop->GetWidth() / 2,
		_y + _progressBarTop->GetHeight() / 2,
		 0, 0, _width, _progressBarTop->GetHeight());
}

void ProgressBar::Render(HDC hdc, const POINT * _pt)
{
	_progressBarBottom->Render(hdc, _rcProgress.left + _progressBarBottom->GetWidth() / 2 - _pt->x,
		_y + _progressBarBottom->GetHeight() / 2 - _pt->y,
		0, 0, _progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());

	_progressBarTop->Render(hdc, _rcProgress.left + _progressBarTop->GetWidth() / 2 - _pt->x,
		_y + _progressBarTop->GetHeight() / 2 - _pt->y,
		0, 0, _width, _progressBarTop->GetHeight());
}

void ProgressBar::SetGauge(float currentGauge, float maxGaguge)
{
	_width = (currentGauge / maxGaguge) * _progressBarBottom->GetWidth();

}
