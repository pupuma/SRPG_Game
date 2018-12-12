#pragma once

class SelectStateButton;

class GameUI
{
private:
	SelectStateButton* selectStateButton;
private:
	bool isActive;
private:
	RECT rcTopTimer;
	RECT rcTest1;
	RECT rcTest2;
	RECT rcTest3;
	RECT rcTest4;
	RECT rcTest5;
	RECT rcTest6;
	RECT rcTest7;



	Image* imgTest1;
	Image* imgTest2;
	Image* imgTest3;
	Image* imgTest4;
	Image* imgTest5;
	Image* imgTest6;
	Image* imgTest7;


public:
	GameUI();
	~GameUI();
public:
	bool Init();
	void Update();
	void Render(HDC hdc);
};

