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

	// �̹��� �Ŵ��� �ʱ�ȭ 
	IMAGEMANAGER->Init();
	IMAGEMANAGER->AddImage(TEXT("Player"), TEXT("../Resource/SpaceShip/rocket.bmp"), 52, 64, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("FrontLoading"), TEXT("../Resource/SpaceShip/hpBarTop.bmp"), 0, WINSIZEY - 20,
		WINSIZEX, 20, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("BackLoading"), TEXT("../Resource/SpaceShip/hpBarBottom.bmp"), 0, WINSIZEY - 20,
		WINSIZEX, 20, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Loading"), TEXT("../Resource/SpaceShip/Loading.bmp"), WINSIZEX, WINSIZEY, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("UFO"), TEXT("../Resource/SpaceShip/ufo.bmp"), 0, 0, 530, 32, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("background2"), TEXT("../Resource/SpaceShip/background.bmp"), WINSIZEX, WINSIZEY, 1, 1, false, RGB(0, 0, 0));
	
	// Scene�� �߰� �۾� : ���Ŵ����� �ʱ�ȭ �ϰ� ���� �߰� ���� 

	// �� �ʱ�ȭ 
	SCENEMANAGER->Init();

	// �� �߰� 

	// Test Scene

	SCENEMANAGER->AddScene(TEXT("BattleSceneTest"), new BattleSceneTest());





	// ù ���� ���� 
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

