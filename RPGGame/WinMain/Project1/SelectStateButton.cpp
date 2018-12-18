#include "Game.h"
#include "SelectStateButton.h"
#include "GameTurnManager.h"
#include "ButtonManager.h"
#include "FontManager.h"


SelectStateButton::SelectStateButton()
{
}


SelectStateButton::~SelectStateButton()
{
}

bool SelectStateButton::Init()
{
	{
		//isAttack = false;
		characterSkillList = GAMESYS->GetCharacterSkillList();
	}
	//
	direction = BUTTTONDIR::BUTTONDIR_NONE;
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

	//RectMakeRectMake(498, 549, 383, 220);
	rcSkill1 = RectMake(515, 565, 48, 48);
	rcSkill2 = RectMake(515, 635, 48, 48);
	rcSkill3 = RectMake(515, 705, 48, 48);

	return true;
}

void SelectStateButton::Release()
{
}

void SelectStateButton::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	// ATTACK
	if (PtInRect(&rcSelectAttackButton, _ptMouse))
	{
		iSkillFrameX = 0;
		iEndFrameX = 0;
		if (GameTurnManager::GetSingleton()->PlayerTrun())
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				ButtonManager::GetSingleton()->SetSelectActive(false);

				iAttackFrameX = 1;
				direction = BUTTTONDIR::BUTTONDIR_DOWN;

			}

			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				iAttackFrameX = 1;
				direction = BUTTTONDIR::BUTTONDIR_DOWN;

			}
			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTTONDIR::BUTTONDIR_DOWN)
			{
				direction = BUTTTONDIR::BUTTONDIR_UP;
				iAttackFrameX = 0;
				bActive = eButtonActive::BA_ATTACK;
				ButtonManager::GetSingleton()->SetSelectActive(true, bActive);
				GAMESYS->SetSkilling(false);
			}


		}
	}
	else if (PtInRect(&rcSelectSkillButton, _ptMouse))
	{
		iAttackFrameX = 0;
		iEndFrameX = 0;
		if (GameTurnManager::GetSingleton()->PlayerTrun())
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				iSkillFrameX = 1;
				direction = BUTTTONDIR::BUTTONDIR_DOWN;

			}

			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				iSkillFrameX = 1;
				direction = BUTTTONDIR::BUTTONDIR_DOWN;

			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTTONDIR::BUTTONDIR_DOWN)
			{
				direction = BUTTTONDIR::BUTTONDIR_UP;
				iSkillFrameX = 0;
				bActive = eButtonActive::BA_SKILL;
				GAMESYS->SetAttacking(false);
				ButtonManager::GetSingleton()->SetSelectActive(false, bActive);

			}

		}

	}
	else if (PtInRect(&rcSelectEndButton, _ptMouse))
	{
		iAttackFrameX = 0;
		iSkillFrameX = 0;
		if (GameTurnManager::GetSingleton()->PlayerTrun())
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				iEndFrameX = 1;
				direction = BUTTTONDIR::BUTTONDIR_DOWN;

			}

			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				iEndFrameX = 1;
				direction = BUTTTONDIR::BUTTONDIR_DOWN;

			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTTONDIR::BUTTONDIR_DOWN)
			{
				direction = BUTTTONDIR::BUTTONDIR_UP;
				iEndFrameX = 0;
				GameTurnManager::GetSingleton()->NextTurn();
			}

		}


	}
	else if (bActive == eButtonActive::BA_SKILL)
	{
		if (PtInRect(&rcSkill1, _ptMouse))
		{
			if (GameTurnManager::GetSingleton()->PlayerTrun())
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					direction = BUTTTONDIR::BUTTONDIR_DOWN;

				}

				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					direction = BUTTTONDIR::BUTTONDIR_DOWN;
				}

				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTTONDIR::BUTTONDIR_DOWN)
				{
					direction = BUTTTONDIR::BUTTONDIR_UP;
					GameTurnManager::GetSingleton()->SkillAction(1);
					bActive = eButtonActive::BA_SKILL;
					ButtonManager::GetSingleton()->SetSelectActive(true, bActive);
					GAMESYS->SetSkilling(true);
				}
			}
			
		}
		else if (PtInRect(&rcSkill2, _ptMouse))
		{
			if (GameTurnManager::GetSingleton()->PlayerTrun())
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					direction = BUTTTONDIR::BUTTONDIR_DOWN;

				}

				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					direction = BUTTTONDIR::BUTTONDIR_DOWN;
				}

				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTTONDIR::BUTTONDIR_DOWN)
				{
					direction = BUTTTONDIR::BUTTONDIR_UP;
					GameTurnManager::GetSingleton()->SkillAction(2);
					bActive = eButtonActive::BA_SKILL;
					ButtonManager::GetSingleton()->SetSelectActive(true, bActive);
					GAMESYS->SetSkilling(true);
				}
			}
		
		}
		else if (PtInRect(&rcSkill3, _ptMouse))
		{
			if (GameTurnManager::GetSingleton()->PlayerTrun())
			{
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					direction = BUTTTONDIR::BUTTONDIR_DOWN;

				}

				if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
				{
					direction = BUTTTONDIR::BUTTONDIR_DOWN;
				}

				if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTTONDIR::BUTTONDIR_DOWN)
				{
					direction = BUTTTONDIR::BUTTONDIR_UP;
					GameTurnManager::GetSingleton()->SkillAction(3);
					bActive = eButtonActive::BA_SKILL;
					ButtonManager::GetSingleton()->SetSelectActive(true, bActive);
					GAMESYS->SetSkilling(true);
				}
			}
			
		}
	}
	else
	{
		direction = BUTTTONDIR::BUTTONDIR_NONE;
		iAttackFrameX = 0;
		iSkillFrameX = 0;
		iEndFrameX = 0;
	}

	
}

void SelectStateButton::Render(HDC hdc)
{

	DrawObject(hdc, rcSelectAttackButton, 1, RGB(25, 125, 25), RECTANGLE);
	DrawObject(hdc, rcSelectSkillButton, 1, RGB(125, 125, 25), RECTANGLE);
	DrawObject(hdc, rcSelectItemButton, 1, RGB(225, 125, 25), RECTANGLE);
	DrawObject(hdc, rcSelectEndButton, 1, RGB(225, 125, 225), RECTANGLE);



	imgSelectAttackButton->FrameRender(hdc, rcSelectAttackButton.left, rcSelectAttackButton.top, iAttackFrameX, iAttackFrameY);
	imgSelectSkillButton->FrameRender(hdc, rcSelectSkillButton.left, rcSelectSkillButton.top, iSkillFrameX, iSkillFrameY);
	//imgSelectItemButton->FrameRender(hdc, rcSelectItemButton.left, rcSelectItemButton.top, 0, 2);
	imgSelectEndButton->FrameRender(hdc, rcSelectEndButton.left, rcSelectEndButton.top, iEndFrameX, iEndFrameY);

	if (bActive == eButtonActive::BA_SKILL)
	{
		POINT pt = { 598, 575 };
		FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG"), TEXT("테스트입니다."), &pt, COLOR_M);

#if defined(_DEBUG_TEST)
		DrawObject(hdc, rcSkill1, 1, RGB(25, 125, 25), RECTANGLE);
		DrawObject(hdc, rcSkill2, 1, RGB(125, 25, 25), RECTANGLE);
		DrawObject(hdc, rcSkill3, 1, RGB(25, 25, 125), RECTANGLE);

		//
		
#endif
	}


}
