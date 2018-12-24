#include "Game.h"
#include "HpBar.h"

#include "Character.h"


HpBar::HpBar()
{
	_r = 0;
	_g = 255;
}


HpBar::~HpBar()
{
}

void HpBar::Init(int _index, float hp)
{
	switch (_index)
	{
	case 0:
	{
		_backGauge = RectMake(70, 450, 170, 15);
		_frontGauge = RectMake(70, 450, 0, 15);
		width = (_backGauge.right - _backGauge.left);


	}
	break;
	case 1:
	{
		_backGauge = RectMake(WINSIZEX - 450, 50, 170, 15);
		_frontGauge = RectMake(WINSIZEX - 450, 50, 0, 15);
		width = (_backGauge.right - _backGauge.left);

	}
	break;
	}

	index = _index;
	fMaxWidth = width;
	_hp = hp;
	fHp = _hp;
}

void HpBar::Init(float hp)
{

}

void HpBar::Update()
{
	switch (index)
	{
	case 0:
	{
		_backGauge = RectMake(70, 450, 170, 15);
		_frontGauge = RectMake(70, _frontGauge.top, width, 15);

	}
	break;
	case 1:
	{
		_backGauge = RectMake(WINSIZEX - 320, 450, 170, 15);
		_frontGauge = RectMake(WINSIZEX - 320, _frontGauge.top, width, 15);

	}
	break;
	}
}

void HpBar::Render(HDC hdc)
{
	GaugeControl(hdc);
}

void HpBar::GaugeControl(HDC hdc)
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


void HpBar::DecreaseHpBar(float attackPoint)
{
	float fMaxHp = _hp;
	float fCurrentHp = _hp - attackPoint;
	float fRate = (fCurrentHp / fMaxHp) * 100;
	float fTemp = (fMaxWidth * fRate) / 100;
	fHp -= attackPoint;
	width = width - (fMaxWidth - fTemp);

	if (width <= 0)
	{
		width = (_backGauge.right - _backGauge.left);

	}

}


void HpBar::ResetBar(float hp)
{
	width = (_backGauge.right - _backGauge.left);
	_hp = hp;
	_r = 0;
	_g = 255;
}