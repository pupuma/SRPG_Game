#pragma once

//class Character;
class HpBar
{
private:
	RECT _frontGauge;
	RECT _backGauge;
	int _r, _g;
	float width;
	float fMaxWidth;
	int index;
	float _hp;
	float fHp;
public:
	HpBar();
	~HpBar();
public:
	void Init(int _index, float hp);
	void Init(float hp);
	void Update();
	void Render(HDC hdc);
	void GaugeControl(HDC hdc);
	void DecreaseHpBar(float attackPoint);
	void ResetBar(float hp);

};
