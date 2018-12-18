#pragma once

enum eButtonActive
{
	BA_ATTACK,
	BA_SKILL,
	BA_ITEM,
	BA_END,
	BA_NONE,
};


class ButtonManager
	: public SingletonBase<ButtonManager>
{
private:
	eButtonActive bAcitve;
	bool isActive;
	bool isAttack;
public:
	ButtonManager();
	~ButtonManager();
public:
	void Init();
	void Update();

public:
	void SetSelectActive(bool _isActive);
	void SetSelectActive(bool _isActive,eButtonActive _bAcitve);
public:
	bool GetSelectActive() { return isActive; }
	bool GetButtonActive() { return bAcitve; }
	bool IsAttackActive() { return isAttack; }
	eButtonActive GetButtonTypeActive() { return bAcitve; }
};

