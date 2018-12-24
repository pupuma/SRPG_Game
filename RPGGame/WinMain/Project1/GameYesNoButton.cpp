#include "Game.h"

#include "GameYesNoButton.h"

#include "GameTurnManager.h"
#include "ButtonManager.h"

GameYesNoButton::GameYesNoButton()
{

}


GameYesNoButton::~GameYesNoButton()
{

}

bool GameYesNoButton::Init()
{

	yesButtonFrameX = 0;
	yesButtonFrameY = 0;

	noButtonFrameX = 0;
	noButtonFrameY = 0;

	rcBox = RectMake(535, 465, 130, 75);
	rcYesButton = RectMake(540, 470, 61, 65);
	rcNoButton = RectMake(602, 470, 61, 65);

	imgBox = IMAGEMANAGER->FindImage(TEXT("UI5"));
	imgYesButton = IMAGEMANAGER->FindImage(TEXT("YesButton"));
	imgNoButton = IMAGEMANAGER->FindImage(TEXT("NoButton"));
	
	return true;
}

void GameYesNoButton::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);


	if (PtInRect(&rcYesButton, _ptMouse))
	{
		if (ButtonManager::GetSingleton()->GetSelectActive())
		{
			noButtonFrameX = 0;
			if (GameTurnManager::GetSingleton()->PlayerTrun())
			{
				if (ButtonManager::GetSingleton()->GetButtonTypeActive() == eButtonActive::BA_ATTACK)
				{
					if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
					{
						yesButtonFrameX = 1;
						direction = BUTTONDIR_DOWN;

					}
					else if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTONDIR_DOWN)
					{
						direction = BUTTONDIR_UP;
						yesButtonFrameX = 0;
						//ButtonManager::GetSingleton()->SetAttackButton(false);
						//GAMESYS->SetAction(true);
						GameTurnManager::GetSingleton()->AttackAction();
						GAMESYS->SetAttacking(true);
						if (!GAMESYS->GetMove())
						{
							//GAMESYS->SetMove(true);
							GAMESYS->SetAction(false);
						}
						else
						{
							GAMESYS->SetAction(true);
						}

						ButtonManager::GetSingleton()->SetSelectActive(false);

					}

					if (direction == BUTTONDIR_UP)
					{
						yesButtonFrameX = 0;
						direction = BUTTONDIR_NONE;

					}
				}
				else if (ButtonManager::GetSingleton()->GetButtonTypeActive() == eButtonActive::BA_SKILL)
				{
					if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
					{
						yesButtonFrameX = 1;
						direction = BUTTONDIR_DOWN;

					}
					else if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTONDIR_DOWN)
					{
						direction = BUTTONDIR_UP;
						yesButtonFrameX = 0;
						//ButtonManager::GetSingleton()->SetAttackButton(false);
						//GAMESYS->SetAction(true);

						GAMESYS->SetAttacking(true);
						if (!GAMESYS->GetMove())
						{
							//GAMESYS->SetMove(true);
							GAMESYS->SetAction(false);
						}
						else
						{
							GAMESYS->SetAction(true);
						}

						GAMESYS->SkillActivation();


						ButtonManager::GetSingleton()->SetSelectActive(false);

					}

					if (direction == BUTTONDIR_UP)
					{
						yesButtonFrameX = 0;
						direction = BUTTONDIR_NONE;

					}
				}
				
			}
		}


	}
	else if (PtInRect(&rcNoButton, _ptMouse))
	{
		if (ButtonManager::GetSingleton()->GetSelectActive())
		{
			yesButtonFrameX = 0;
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				noButtonFrameX = 1;
				direction = BUTTONDIR_DOWN;

			}
			else if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && direction == BUTTONDIR_DOWN)
			{
				direction = BUTTONDIR_UP;
				ButtonManager::GetSingleton()->SetSelectActive(false);

				noButtonFrameX = 0;
				if (GAMESYS->IsAction())
				{
					GAMESYS->SetAction(false);
				}
				else
				{
					if (!GAMESYS->GetMove())
					{
						GAMESYS->SetMove(false);
					}
				}
				GAMESYS->SetAttacking(false);
				GAMESYS->SetSkilling(false);



				isAttack = false;
			}

		}

		if (direction == BUTTONDIR_UP)
		{
			noButtonFrameX = 0;
			direction = BUTTONDIR_NONE;

		}
	}
	else
	{
		yesButtonFrameX = 0;
		noButtonFrameX = 0;
	}

	
	

}

void GameYesNoButton::Render(HDC hdc)
{
	if (ButtonManager::GetSingleton()->GetSelectActive())
	{
		if (GameTurnManager::GetSingleton()->PlayerTrun())
		{
			imgBox->Render(hdc, rcBox.left, rcBox.top);

			imgYesButton->FrameRender(hdc, rcYesButton.left, rcYesButton.top, yesButtonFrameX, yesButtonFrameY);
			imgNoButton->FrameRender(hdc, rcNoButton.left, rcNoButton.top, noButtonFrameX, noButtonFrameY);

		}
		

	}
//		imgBox->Render(hdc, rcBox.left, rcBox.top);
//
//#if defined(_DEBUG_TEST)
//		{
//			DrawObject(hdc, rcYesButton, 1, RGB(125, 125, 125), RECTANGLE);
//			DrawObject(hdc, rcNoButton, 1, RGB(125, 125, 125), RECTANGLE);
//		}
//#endif // 
//
//
//		imgYesButton->FrameRender(hdc, rcYesButton.left, rcYesButton.top, yesButtonFrameX, yesButtonFrameY);
//		imgNoButton->FrameRender(hdc, rcNoButton.left, rcNoButton.top, noButtonFrameX, noButtonFrameY);


}
