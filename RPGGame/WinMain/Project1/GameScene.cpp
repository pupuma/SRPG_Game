#include "Game.h"
#include "GameScene.h"
#include "BackBuffer.h"
#include "RenderTest.h"
#include "ImageCropTest.h"
#include "FrameRenderTest.h"
#include "TrigonometricTest.h"
#include "StalkerTest.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::Init()
{
	MainGame::Init();
	GetClientRect(_hWnd, &_rcClient);
	//=========================================================
#if defined(_RENDER_TEST)
	renderTest = new RenderTest;
	assert(renderTest != NULL);
	renderTest->Init();
#elif defined(_CROP_TEST)
	imageCropTest = new ImageCropTest();
	assert(imageCropTest != NULL);
	imageCropTest->Init();
#elif defined (_FRAME_TEST)
	frameTest = new FrameRenderTest();
	frameTest->Init();
#elif defined (_TRIFUNC_TEST)
	triFuncTest = new TrigonometricTest();
	triFuncTest->Init();
#elif defined (_STALKER_TEST)
	_stalkerTest = new StalkerTest();
	_stalkerTest->Init();
#else
#endif
	//_loopBackGround = new Image();
	//_loopBackGround->Init(TEXT("background.bmp"), WINSIZEX, WINSIZEY);
	
	//iOffset = 0;

	//=========================================================

	return true;
}

void GameScene::Release()
{
	MainGame::Release();
	//=========================================================
	//SelectObject(_hMemDC, _hOldBit);
	//DeleteObject(_hBit);
	//DeleteDC(_hMemDC);
#if defined(_RENDER_TEST)
	renderTest->Release();
#elif defined(_CROP_TEST)
	imageCropTest->Release();
#elif defined(_FRAME_TEST)
	frameTest->Release();
#elif defined (_TRIFUNC_TEST)
	triFuncTest->Release();
#elif defined (_STALKER_TEST)
	_stalkerTest->Release();
#endif
	//=========================================================

}

void GameScene::Update()
{
	MainGame::Update();
	//=========================================================
	//renderTest->Update();
	//iOffset += 5;
#if defined(_RENDER_TEST)
	renderTest->Update();
#elif defined(_CROP_TEST)
	imageCropTest->Update();
#elif defined(_FRAME_TEST)
	frameTest->Update();
#elif defined (_TRIFUNC_TEST)
	triFuncTest->Update();
#elif defined (_STALKER_TEST)
	_stalkerTest->Update();
#endif
	//=========================================================
	// 윈머지 - 아크로에딧
}

void GameScene::Render(HDC hdc)
{
	//MainGame::Render(hdc);
	HDC backDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//
#if defined(_RENDER_TEST)
	renderTest->Render(backDC);
#elif defined(_CROP_TEST)
	imageCropTest->Render(backDC);
#elif defined(_FRAME_TEST)
	frameTest->Render(backDC);
#elif defined (_TRIFUNC_TEST)
	triFuncTest->Render(backDC);
#elif defined (_STALKER_TEST)
	_stalkerTest->Render(backDC);
#endif
	//renderTest->Render(backDC);
	//_loopBackGround->LoopRender(backDC, &_rcClient, iOffset, 0);

	this->GetBackBuffer()->Render(hdc, 0,0);
}
