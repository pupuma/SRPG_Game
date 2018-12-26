#include "Game.h"
#include "TitleScene.h"
#include "FontManager.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

bool TitleScene::Init()
{
	img = IMAGEMANAGER->FindImage(TEXT("TitleBG"));
	imgBox = IMAGEMANAGER->FindImage(TEXT("StartBox"));
	ptTitle = { 250, 250 };

	ptStart = { WINSIZEX / 2 , 600 };
	rcBox = RectMakeCenter(ptStart.x, ptStart.y, 300, 150);
	colorKey = 0;
	dex = 1;
	return true;
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (PtInRect(&rcBox, _ptMouse))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->ChangeScene(TEXT("QusetScene"));
		}
	}
	colorKey = colorKey + (dex * 15);

	if (colorKey >= 255)
	{
		dex *= -1;
	}
	else if (colorKey <= 0)
	{
		dex *= -1;
	}
}

void TitleScene::Render(HDC hdc)
{
	img->Render(hdc);

	SetBkMode(hdc, TRANSPARENT);
	//DrawObject(hdc, rcBox, 1, RGB(125, 125, 125), RECTANGLE);

	FontManager::GetSingleton()->RenderText(hdc, TEXT("NBB"), TEXT("코딩용사의 모험"), &ptTitle, RGB(225, 225, 225));

	
	imgBox->AlphaRender(hdc, rcBox.left, rcBox.top, colorKey);
	POINT pt = { rcBox.left + 10, rcBox.top + 50 };
	FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG"), TEXT("Please click on the box! "), &pt, RGB(0, 0, 0));

}
