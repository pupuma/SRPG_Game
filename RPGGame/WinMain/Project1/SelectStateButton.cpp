#include "Game.h"
#include "SelectStateButton.h"
#include "GameTurnManager.h"


SelectStateButton::SelectStateButton()
{
}


SelectStateButton::~SelectStateButton()
{
}

bool SelectStateButton::Init()
{
	//
	direction = BUTTONDIR_NONE;

	iAttackFrameX = 0;
	iAttackFrameY =0;

	iSkillFrameX = 0;
	iSkillFrameY = 1;

	iItemFrameX = 0;
	iItemFrameY =2;

	iEndFrameX = 0 ;
	iEndFrameY = 3;
	//
	rcSelectAttackButton = RectMake(326, 563, 131, 48);
	rcSelectSkillButton = RectMake(326, 611, 131, 48);
	rcSelectItemButton = RectMake(326, 659, 131, 48);
	rcSelectEndButton = RectMake(326, 707, 131, 48);

	imgSelectAttackButton = IMAGEMANAGER->FindImage(TEXT("SelectButton"));
	imgSelectSkillButton = IMAGEMANAGER->FindImage(TEXT("SelectButton"));
	imgSelectItemButton = IMAGEMANAGER->FindImage(TEXT("SelectButton"));
	imgSelectEndButton = IMAGEMANAGER->FindImage(TEXT("SelectButton"));

	return true;
}

void SelectStateButton::Release()
{
}

void SelectStateButton::Update()
{

	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (PtInRect(&rcSelectAttackButton, _ptMouse))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			iAttackFrameX = 1;
			direction = BUTTONDIR_DOWN;
			
		}
		
		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTONDIR_DOWN)
		{
			direction = BUTTONDIR_UP;
			iAttackFrameX = 0;
		}
	

	}
	else
	{
		direction = BUTTONDIR_NONE;
		iAttackFrameX = 0;

	}

	//
	//
	//

	if (PtInRect(&rcSelectEndButton, _ptMouse))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			iEndFrameX = 1;
			direction = BUTTONDIR_DOWN;
			GameTurnManager::GetSingleton()->NextTurn();

		}

		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTONDIR_DOWN)
		{
			direction = BUTTONDIR_UP;
			iEndFrameX = 0;
		}


	}
	else
	{
		direction = BUTTONDIR_NONE;
		iEndFrameX = 0;

	}



	//if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	//{
	//	GetCursorPos(&_ptMouse);
	//	ScreenToClient(_hWnd, &(_ptMouse));


	//	if (PtInRect(&rcSelectAttackButton, _ptMouse))
	//	{
	//	}

	//	if (PtInRect(&rcSelectSkillButton, _ptMouse))
	//	{
	//		imgSelectSkillButton->SetFrameY(1);

	//	}

	//	if (PtInRect(&rcSelectItemButton, _ptMouse))
	//	{
	//		imgSelectItemButton->SetFrameY(1);

	//	}

	//	if (PtInRect(&rcSelectEndButton, _ptMouse))
	//	{
	//		imgSelectEndButton->SetFrameY(1);

	//	}
	//}

	/*if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{

	}

	if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
	{

	}*/

	//KEYMANAGER->Reset();
}

void SelectStateButton::Render(HDC hdc)
{

	DrawObject(hdc, rcSelectAttackButton, 1, RGB(25, 125, 25), RECTANGLE);
	DrawObject(hdc, rcSelectSkillButton, 1, RGB(125, 125, 25), RECTANGLE);
	DrawObject(hdc, rcSelectItemButton, 1, RGB(225, 125, 25), RECTANGLE);
	DrawObject(hdc, rcSelectEndButton, 1, RGB(225, 125, 225), RECTANGLE);



	imgSelectAttackButton->FrameRender(hdc, rcSelectAttackButton.left, rcSelectAttackButton.top, iAttackFrameX, iAttackFrameY);
	//imgSelectSkillButton->FrameRender(hdc, rcSelectSkillButton.left, rcSelectSkillButton.top, 0, 1);
	//imgSelectItemButton->FrameRender(hdc, rcSelectItemButton.left, rcSelectItemButton.top, 0, 2);
	imgSelectEndButton->FrameRender(hdc, rcSelectEndButton.left, rcSelectEndButton.top, iEndFrameX, iEndFrameY);
}
