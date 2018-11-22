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
	
	// �̹��� ������
	{
		IMAGEMANAGER->AddFrameImage(TEXT("Actor1"), TEXT("../Resource/Images/Actor1.bmp"), 573, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Outside_A2"), TEXT("../Resource/Images/Outside_A2.bmp"), 768, 576, 16, 12, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("TileIdle"), TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("Select"), TEXT("../Resource/Images/Select.bmp"), 48, 48, true, COLOR_M);

	}


	{
		RESOURCEMANAGER->AddScript(TEXT("MapData"));
		RESOURCEMANAGER->AddScript(TEXT("MapData_Layer01"));
		RESOURCEMANAGER->AddScript(TEXT("MapData_Layer02"));


	}
	// Scene�� �߰� �۾� : ���Ŵ����� �ʱ�ȭ �ϰ� ���� �߰� ���� 

	// �� �ʱ�ȭ 
	SCENEMANAGER->Init();

	// �� �߰� 

	// Test Scene
	//

	//

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

