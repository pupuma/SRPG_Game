#include "Game.h"
#include "GameUI.h"

#include "SelectStateButton.h"
#include "GameYesNoButton.h"
GameUI::GameUI()
{
}


GameUI::~GameUI()
{
}

bool GameUI::Init()
{
	{
		selectYNButton = new GameYesNoButton();
		selectYNButton->Init();
	}
	{
		selectStateButton = new SelectStateButton();
		selectStateButton->Init();
		isActive = false;

		rcTopTimer = RectMake(552, 0, 96, 96);
		rcTest1 = RectMake(11, 407, 252, 123);
		rcTest2 = RectMake(31, 533, 253, 253);
		rcTest3 = RectMake(320, 549, 140, 220);
		rcTest4 = RectMake(498, 549, 383, 220);
		//rcTest5 = RectMake(535, 465, 130, 75);
		rcTest6 = RectMake(917, 533, 253, 253);
		rcTest7 = RectMake(937, 407, 252, 123);

		imgTest1 = IMAGEMANAGER->FindImage(TEXT("UI1"));
		imgTest2 = IMAGEMANAGER->FindImage(TEXT("UI2"));
		imgTest3 = IMAGEMANAGER->FindImage(TEXT("UI3"));
		imgTest4 = IMAGEMANAGER->FindImage(TEXT("UI4"));
		//imgTest5 = IMAGEMANAGER->FindImage(TEXT("UI5"));
		imgTest6 = IMAGEMANAGER->FindImage(TEXT("UI2"));
		imgTest7 = IMAGEMANAGER->FindImage(TEXT("UI1"));


		



	}
	return false;
}

void GameUI::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('3'))
	{
		isActive = true;
	}
	if (KEYMANAGER->IsOnceKeyDown('4'))
	{
		isActive = false;
	}

	if (isActive)
	{
		selectStateButton->Update();
		selectYNButton->Update();

	}
}

void GameUI::Render(HDC hdc)
{
	if (isActive)
	{
		DrawObject(hdc, rcTopTimer, 1, RGB(255, 0, 0), RECTANGLE);
		DrawObject(hdc, rcTest1, 1, RGB(125, 0, 125), RECTANGLE);
		DrawObject(hdc, rcTest2, 1, RGB(125, 255, 125), RECTANGLE);
		DrawObject(hdc, rcTest3, 1, RGB(125, 125, 125), RECTANGLE);
		DrawObject(hdc, rcTest4, 1, RGB(125, 125, 125), RECTANGLE);
		//DrawObject(hdc, rcTest5, 1, RGB(255, 255, 125), RECTANGLE);
		DrawObject(hdc, rcTest6, 1, RGB(125, 255, 125), RECTANGLE);
		DrawObject(hdc, rcTest7, 1, RGB(125, 0, 125), RECTANGLE);


		//

		imgTest1->Render(hdc, rcTest1.left, rcTest1.top);
		imgTest2->Render(hdc, rcTest2.left, rcTest2.top);
		imgTest3->Render(hdc, rcTest3.left, rcTest3.top);
		imgTest4->Render(hdc, rcTest4.left, rcTest4.top);
		//imgTest5->Render(hdc, rcTest5.left, rcTest5.top);
		imgTest6->Render(hdc, rcTest6.left, rcTest6.top);
		imgTest7->Render(hdc, rcTest7.left, rcTest7.top);

		//
		
		selectStateButton->Render(hdc);
		selectYNButton->Render(hdc);

	}
}
