#include "Game.h"

#include "GameYesNoButton.h"

#include "GameTurnManager.h"

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
	if (GameTurnManager::GetSingleton()->PlayerTrun())
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &_ptMouse);

		if (PtInRect(&rcYesButton, _ptMouse))
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
			}

			if (direction == BUTTONDIR_UP)
			{
				yesButtonFrameX = 0;
				direction = BUTTONDIR_NONE;

			}
		}
	}
}

void GameYesNoButton::Render(HDC hdc)
{
	imgBox->Render(hdc, rcBox.left, rcBox.top);

#if defined(_DEBUG_TEST)
	{
		DrawObject(hdc, rcYesButton, 1, RGB(125, 125, 125), RECTANGLE);
		DrawObject(hdc, rcNoButton, 1, RGB(125, 125, 125), RECTANGLE);
	}
#endif // 
	imgYesButton->FrameRender(hdc, rcYesButton.left, rcYesButton.top, yesButtonFrameX, yesButtonFrameY);
	imgNoButton->FrameRender(hdc, rcNoButton.left, rcNoButton.top, noButtonFrameX, noButtonFrameY);

}
