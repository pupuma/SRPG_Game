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
	{

		//RECT rc1, rcClient;
		//GetClientRect(_hWnd, &rc1);

		//POINT pt1, pt2;
		//pt1.x = rc1.left;
		//pt1.y = rc1.top;
		//pt2.x = rc1.right;
		//pt2.y = rc1.bottom;


		//ClientToScreen(_hWnd, &pt1);
		//ClientToScreen(_hWnd, &pt2);

		//rcClient.left = pt1.x;
		//rcClient.right = pt2.x;
		//rcClient.top = pt1.y;
		//rcClient.bottom = pt2.y;

		//ClipCursor(&rcClient);
	}
	// �̹��� �Ŵ��� �ʱ�ȭ 
	IMAGEMANAGER->Init();
	IMAGEMANAGER->AddImage(TEXT("Player"), TEXT("../Resource/SpaceShip/rocket.bmp"), 52, 64, true, COLOR_M);
	
	// �̹��� ������
	{
		IMAGEMANAGER->AddFrameImage(TEXT("Actor1"), TEXT("../Resource/Images/Actor1.bmp"), 573, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Evil"), TEXT("../Resource/Images/Evil.bmp"), 573, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Outside_A2"), TEXT("../Resource/Images/Outside_A2.bmp"), 768, 576, 16, 12, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("TileIdle"), TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("Select"), TEXT("../Resource/Images/Select.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("SelectObject"), TEXT("../Resource/Images/SelectObject.bmp"), 96, 48, 2, 1, true, COLOR_M);

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

