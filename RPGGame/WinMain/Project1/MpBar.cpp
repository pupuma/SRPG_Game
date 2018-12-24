#include "Game.h"
#include "MpBar.h"



MpBar::MpBar()
{
	_r = 0;
	_g = 255;
}


MpBar::~MpBar()
{
}

void MpBar::Init(int _index, float mp)
{
	switch (_index)
	{
	case 0:
	{
		_backGauge = RectMake(20, 50, 300, 30);
		_frontGauge = RectMake(20, 50, 0, 30);
		width = (_backGauge.right - _backGauge.left);


	}
	break;
	case 1:
	{
		_backGauge = RectMake(WINSIZEX - 320, 50, 300, 30);
		_frontGauge = RectMake(WINSIZEX - 320, 50, 0, 30);
		width = (_backGauge.right - _backGauge.left);

	}
	break;
	}

	index = _index;
	fMaxWidth = width;
	_mp = mp;
	fMp = _mp;
}

void MpBar::Update()
{
	switch (index)
	{
	case 0:
	{
		_backGauge = RectMake(20, 50, 300, 30);
		_frontGauge = RectMake(20, _frontGauge.top, width, 30);

	}
	break;
	case 1:
	{
		_backGauge = RectMake(WINSIZEX - 320, 50, 300, 30);
		_frontGauge = RectMake(WINSIZEX - 320, _frontGauge.top, width, 30);

	}
	break;
	}
}

void MpBar::Render(HDC hdc)
{
	GaugeControl(hdc);
}

void MpBar::GaugeControl(HDC hdc)
{
	if (_frontGauge.left >= _frontGauge.right)
	{
		_frontGauge.left = _backGauge.right;
	}

	RectangleMake(hdc, _backGauge.left, _backGauge.top, (_backGauge.right - _backGauge.left), ((_backGauge.bottom) - (_backGauge.top)));


	HBRUSH brush = CreateSolidBrush(RGB(_r, _g, 0));
	FillRect(hdc, &_frontGauge, brush);
	DeleteObject(brush);


	if (width >= fMaxWidth)
	{
		_g = 250;
		_r = 0;
	}
	else if (width >= fMaxWidth / 4 && width <= (fMaxWidth - fMaxWidth / 4))
	{
		_r = 250;
		_g = 250;
	}
	else if (width >= fMaxWidth / 5 && width <= fMaxWidth / 4)
	{
		_r = 250;
		_g = 0;
	}





}


void MpBar::DecreaseHpBar(float attackPoint)
{
	float fMaxMp = _mp;
	float fCurrentHp = _mp - attackPoint;
	float fRate = (fCurrentHp / fMaxMp) * 100;
	float fTemp = (fMaxWidth * fRate) / 100;
	fMp -= attackPoint;
	width = width - (fMaxWidth - fTemp);

	if (width <= 0)
	{
		width = (_backGauge.right - _backGauge.left);

	}

}


void MpBar::ResetBar(float mp)
{
	width = (_backGauge.right - _backGauge.left);
	_mp = mp;
	_r = 0;
	_g = 255;
}