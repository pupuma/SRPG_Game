#pragma once

class MpBar
{
private:
	RECT _frontGauge;
	RECT _backGauge;
	int _r, _g;
	float width;
	float fMaxWidth;
	int index;
	float _mp;
	float fMp;
public:
	MpBar();
	~MpBar();
public:
	void Init(int _index, float mp);
	void Update();
	void Render(HDC hdc);
	void GaugeControl(HDC hdc);
	void DecreaseHpBar(float attackPoint);
	void ResetBar(float mp);

};
