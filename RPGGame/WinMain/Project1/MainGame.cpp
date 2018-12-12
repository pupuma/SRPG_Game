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
	// 이미지 매니져 초기화 
	IMAGEMANAGER->Init();
	IMAGEMANAGER->AddImage(TEXT("Player"), TEXT("../Resource/SpaceShip/rocket.bmp"), 52, 64, true, COLOR_M);
	GAMESYS->Init();
	// 이미지 프레임
	{
		IMAGEMANAGER->AddFrameImage(TEXT("Actor1"), TEXT("../Resource/Images/Actor1.bmp"), 573, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Evil"), TEXT("../Resource/Images/Evil.bmp"), 573, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Outside_A2"), TEXT("../Resource/Images/Outside_A2.bmp"), 768, 576, 16, 12, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("TileIdle"), TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("AttackTile"), TEXT("../Resource/Images/AttackTile.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("Select"), TEXT("../Resource/Images/Select.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("SelectObject"), TEXT("../Resource/Images/SelectObject.bmp"), 96, 48, 2, 1, true, COLOR_M);

		IMAGEMANAGER->AddFrameImage(TEXT("TileMap_Cell_B"), TEXT("../Resource/Images/TileMap_Cell_B.bmp"), 768, 14736, 16, 307, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("TileMap_OBJ_B"), TEXT("../Resource/Images/TileMap_OBJ_B.bmp"), 768, 9216, 16, 192, true, COLOR_M);
		backGround = IMAGEMANAGER->AddImage(TEXT("Background"), TEXT("../Resource/Images/BackGround.bmp"), 1200,800, false, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("UI_Button"), TEXT("../Resource/Images/BUTTON.bmp"), 260, 192, 2, 4, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI1"), TEXT("../Resource/Images/UI1.bmp"), 252, 123,true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI2"), TEXT("../Resource/Images/UI2.bmp"), 253, 253,true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI3"), TEXT("../Resource/Images/UI3.bmp"), 140, 220,true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI4"), TEXT("../Resource/Images/UI4.bmp"), 383, 220,true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI5"), TEXT("../Resource/Images/UI5.bmp"), 130, 75,true, COLOR_M);

		IMAGEMANAGER->AddFrameImage(TEXT("SelectButton"), TEXT("../Resource/Images/BUTTON.bmp"), 260, 192, 2, 4, true, COLOR_M);

	}

	{
		RESOURCEMANAGER->AddScript(TEXT("MapData"));
		RESOURCEMANAGER->AddScript(TEXT("MapData_Layer01"));
		RESOURCEMANAGER->AddScript(TEXT("MapData_Layer02"));
		RESOURCEMANAGER->AddScript(TEXT("Map_1"));

		PARSING->MapDataParsing(TEXT("Map_1"));
	}

	{
		//IMAGEMANAGER->AddFrameImage(TEXT("Absorb"), TEXT("../Resource/Images/Absorb.bmp"), 960, 960, 5, 5, true, RGB(255, 255, 255));

		//EFFECTMANAGER->AddEffect(TEXT("Absorb"), TEXT("Absorb"), 960, 960, 5, 5, 1, 0.1f, 10, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Absorb"), TEXT("../Resource/Images/Absorb.bmp"), 960, 960, 192, 192, 1, 1.0f, 10, RGB(255, 255, 255));

	}
	// Scene을 추가 작업 : 씬매니저를 초기화 하고 씬을 추가 하자 

	// 씬 초기화 
	SCENEMANAGER->Init();

	// 씬 추가 

	// Test Scene
	//

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
	backGround->Render(backDC);
	SCENEMANAGER->Render(backDC);
	
	//================
	this->GetBackBuffer()->Render(hdc, 0, 0);
}
