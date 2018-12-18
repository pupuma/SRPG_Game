#pragma once
class GameYesNoButton
{
private:
	BUTTTONDIR		direction;

	RECT rcBox;
	RECT rcYesButton;
	RECT rcNoButton;

	Image* imgBox;
	Image* imgYesButton;
	Image* imgNoButton;
private:
	bool isAttack;
private:
	int yesButtonFrameX;
	int yesButtonFrameY;

	int noButtonFrameX;
	int noButtonFrameY;

public:
	GameYesNoButton();
	~GameYesNoButton();
public:
	bool Init();
	void Update();
	void Render(HDC hdc);
};

