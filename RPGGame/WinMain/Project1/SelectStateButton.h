#pragma once


enum eButtonActive;


class SelectStateButton
{
private:
	int iHp;
	int iMp;
	int iAttackPoint;
	int iMaxHp;
	int iMaxMp;
	int skillIndex;
private:
	int index;
	int iAttackFrameX;
	int iAttackFrameY;

	int iSkillFrameX;
	int iSkillFrameY;

	int iItemFrameX;
	int iItemFrameY;

	int iEndFrameX;
	int iEndFrameY;
private:
	BUTTTONDIR		direction;
	eButtonActive bActive;
	//bool isAttack;
	
private:
	RECT rcSelectAttackButton;
	RECT rcSelectSkillButton;
	RECT rcSelectItemButton;
	RECT rcSelectEndButton;


	Image* imgSelectAttackButton;
	Image* imgSelectSkillButton;
	Image* imgSelectItemButton;
	Image* imgSelectEndButton;
private:
	// Skill
	RECT rcSkill1;
	RECT rcSkill2;
	RECT rcSkill3;
private:

private:
	std::vector<Image*> characterSkillList;
public:
	SelectStateButton();
	~SelectStateButton();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

