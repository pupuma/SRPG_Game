#include "Game.h"
#include "EndScene.h"
#include "FontManager.h"


EndScene::EndScene()
{
}


EndScene::~EndScene()
{
}

bool EndScene::Init()
{
	bg = IMAGEMANAGER->FindImage(TEXT("Book"));
	return true;
}

void EndScene::Release()
{
}

void EndScene::Update()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->ChangeScene(TEXT("QusetScene"));
	}
}

void EndScene::Render(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);

	bg->Render(hdc);
	POINT pt = { 350 , WINSIZEY / 2 };
	FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG_B"), TEXT("�÷������ּż� �����մϴ�.!!"), &pt, RGB(255, 255, 255));
}
