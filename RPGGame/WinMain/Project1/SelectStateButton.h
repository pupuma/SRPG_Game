#pragma once
class SelectStateButton
{
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


private:
	RECT rcSelectAttackButton;
	RECT rcSelectSkillButton;
	RECT rcSelectItemButton;
	RECT rcSelectEndButton;


	Image* imgSelectAttackButton;
	Image* imgSelectSkillButton;
	Image* imgSelectItemButton;
	Image* imgSelectEndButton;

public:
	SelectStateButton();
	~SelectStateButton();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

