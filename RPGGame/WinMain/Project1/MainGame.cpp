#include "Game.h"
#include "MainGame.h"

#include "BattleSceneTest.h"


MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

bool MainGame::Init()
{
	GameNode::Init(true);

	// 이미지 매니져 초기화 
	IMAGEMANAGER->Init();
	IMAGEMANAGER->AddImage(TEXT("Player"), TEXT("../Resource/SpaceShip/rocket.bmp"), 52, 64, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("FrontLoading"), TEXT("../Resource/SpaceShip/hpBarTop.bmp"), 0, WINSIZEY - 20,
		WINSIZEX, 20, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("BackLoading"), TEXT("../Resource/SpaceShip/hpBarBottom.bmp"), 0, WINSIZEY - 20,
		WINSIZEX, 20, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Loading"), TEXT("../Resource/SpaceShip/Loading.bmp"), WINSIZEX, WINSIZEY, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("UFO"), TEXT("../Resource/SpaceShip/ufo.bmp"), 0, 0, 530, 32, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("background2"), TEXT("../Resource/SpaceShip/background.bmp"), WINSIZEX, WINSIZEY, 1, 1, false, RGB(0, 0, 0));
	
	// Scene을 추가 작업 : 씬매니저를 초기화 하고 씬을 추가 하자 

	// 씬 초기화 
	SCENEMANAGER->Init();

	// 씬 추가 

	// Test Scene

	SCENEMANAGER->AddScene(TEXT("BattleSceneTest"), new BattleSceneTest());





	// 첫 씬의 설정 
	SCENEMANAGER->ChangeScene(TEXT("BattleSceneTest"));

	return true;

}

void MainGame::Release()
{
	GameNode::Release();

	//================
	IMAGEMANAGER->Release();
	SCENEMANAGER->Release();
	//================
}

void MainGame::Update()
{
	GameNode::Update();
	//================

	//================
	SCENEMANAGER->Update();
	//================
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================
	SCENEMANAGER->Render(backDC);
	//================
	this->GetBackBuffer()->Render(hdc, 0, 0);
}

