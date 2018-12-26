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
	rcItem1 = rcSkill1;
	rcItem2 = rcSkill2;

	skillIndex = 0;

	imgSkill1 = IMAGEMANAGER->FindImage(TEXT("IconSet"));
	imgSkill2 = IMAGEMANAGER->FindImage(TEXT("IconSet"));
	imgSkill3 = IMAGEMANAGER->FindImage(TEXT("IconSet"));

	imgItem1 = IMAGEMANAGER->FindImage(TEXT("IconSet"));
	imgItem2 = IMAGEMANAGER->FindImage(TEXT("IconSet"));

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
		iItemFrameX = 0;
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
	else if (PtInRect(&rcSelectItemButton, _ptMouse))
	{
		iAttackFrameX = 0;
		iSkillFrameX = 0;
		if (GameTurnManager::GetSingleton()->PlayerTrun())
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				iItemFrameX = 1;
				direction = BUTTTONDIR::BUTTONDIR_DOWN;

			}

			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				iItemFrameX = 1;
				direction = BUTTTONDIR::BUTTONDIR_DOWN;

			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTTONDIR::BUTTONDIR_DOWN)
			{
				direction = BUTTTONDIR::BUTTONDIR_UP;
				iItemFrameX = 0;
				bActive = eButtonActive::BA_ITEM;

				//GameTurnManager::GetSingleton()->NextTurn();
			}

		}
	}
	else if (PtInRect(&rcSelectEndButton, _ptMouse))
	{
		iAttackFrameX = 0;
		iSkillFrameX = 0;
		iItemFrameX = 0;
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
	else if (bActive == eButtonActive::BA_ITEM)
	{
		if (PtInRect(&rcItem1, _ptMouse))
		{
			if (GameTurnManager::GetSingleton()->PlayerTrun())
			{
				if (GAMESYS->GetHpDrinkCount() > 0)
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
						GAMESYS->SetItemType(eItemType::ITEM_HP);

						ButtonManager::GetSingleton()->SetSelectActive(true, bActive);
						GAMESYS->SetSkilling(true);

					}
				}

			}

		}
		else if (PtInRect(&rcItem2, _ptMouse))
		{
			if (GameTurnManager::GetSingleton()->PlayerTrun())
			{
				if (GAMESYS->GetMpDrinkCount() > 0)
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
						bActive = eButtonActive::BA_ITEM;
						GAMESYS->SetItemType(eItemType::ITEM_MP);

						ButtonManager::GetSingleton()->SetSelectActive(true, bActive);
						GAMESYS->SetSkilling(true);

					}
				}
			


			}
		}
	}
	else if (bActive == eButtonActive::BA_SKILL)
	{
		if (PtInRect(&rcSkill1, _ptMouse))
		{
			if (GameTurnManager::GetSingleton()->PlayerTrun())
			{
				if (GAMESYS->SkillCheck(1))
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
						skillIndex = 1;
						GameTurnManager::GetSingleton()->SetSkillIndex(1);
					}
				}
				
			}
			
		}
		else if (PtInRect(&rcSkill2, _ptMouse))
		{
			if (GameTurnManager::GetSingleton()->PlayerTrun())
			{
				if (GAMESYS->SkillCheck(2))
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
						skillIndex = 2;
						GameTurnManager::GetSingleton()->SetSkillIndex(2);

					}

				}
			
			}
		
		}
		else if (PtInRect(&rcSkill3, _ptMouse))
		{
			if (GameTurnManager::GetSingleton()->PlayerTrun())
			{
				if (GAMESYS->SkillCheck(3))
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

						skillIndex = 3;
						GameTurnManager::GetSingleton()->SetSkillIndex(3);
					}
				}
				
			}
			
		}
		
		
	}

	else
	{
		direction = BUTTTONDIR::BUTTONDIR_NONE;
		iAttackFrameX = 0;
		iSkillFrameX = 0;
		iItemFrameX = 0;
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
	
	if (GAMESYS->IsItem())
	{
		imgSelectItemButton->FrameRender(hdc, rcSelectItemButton.left, rcSelectItemButton.top, iItemFrameX, iItemFrameY);
	}
	imgSelectEndButton->FrameRender(hdc, rcSelectEndButton.left, rcSelectEndButton.top, iEndFrameX, iEndFrameY);

	if (bActive == eButtonActive::BA_SKILL)
	{
		POINT pt1 = { 598, 575 };
		std::string str1 = GameTurnManager::GetSingleton()->SkillText(1);
		FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG_S"), str1, &pt1, COLOR_M);

		POINT pt2 = { 598, 645 };
		std::string str2 = GameTurnManager::GetSingleton()->SkillText(2);
		FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG_S"), str2, &pt2, COLOR_M);

		POINT pt3 = { 598, 715 };
		std::string str3 = GameTurnManager::GetSingleton()->SkillText(3);
		FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG_S"), str3, &pt3, COLOR_M);


#if defined(_DEBUG_TEST)
		//DrawObject(hdc, rcSkill1, 1, RGB(25, 125, 25), RECTANGLE);
		//DrawObject(hdc, rcSkill2, 1, RGB(125, 25, 25), RECTANGLE);
		//DrawObject(hdc, rcSkill3, 1, RGB(25, 25, 125), RECTANGLE);
		
#endif
		int frameX = GameTurnManager::GetSingleton()->GetIconFrameX(1);
		int frameY = GameTurnManager::GetSingleton()->GetIconFrameY(1);

		imgSkill1->FrameRender(hdc, rcSkill1.left, rcSkill1.top, frameX , frameY);

		frameX = GameTurnManager::GetSingleton()->GetIconFrameX(2);
		frameY = GameTurnManager::GetSingleton()->GetIconFrameY(2);

		imgSkill2->FrameRender(hdc, rcSkill2.left, rcSkill2.top, frameX, frameY);

		frameX = GameTurnManager::GetSingleton()->GetIconFrameX(3);
		frameY = GameTurnManager::GetSingleton()->GetIconFrameY(3);
		imgSkill3->FrameRender(hdc, rcSkill3.left, rcSkill3.top, frameX, frameY);


	}
	else if(bActive == eButtonActive::BA_ITEM)
	{
		
		imgItem1->FrameRender(hdc, rcItem1.left, rcItem1.top, 0, 2);

		imgItem2->FrameRender(hdc, rcItem2.left, rcItem2.top, 1, 2);

		POINT pt1 = { 598, 575 };
		TCHAR str1[256];
		_stprintf(str1, TEXT("박카스 : 체력이 회복됩니다.(HP회복 : 20 ) x %d"),GAMESYS->GetHpDrinkCount());

		FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG_S"), str1, &pt1, COLOR_M);

		POINT pt2 = { 598, 645 };
		_stprintf(str1, TEXT("레드불 : 날개를 달아줘요(MP회복 : 20 ) x %d"), GAMESYS->GetMpDrinkCount());
		FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG_S"), str1, &pt2, COLOR_M);

			
	}

}
