#include "Game.h"
#include "MainGame.h"

#include "BattleSceneTest.h"
#include "GameTurnManager.h"
#include "ButtonManager.h"
#include "FontManager.h"
#include "SkillSystem.h"

//Scene
#include "LogoScene.h"
#include "TitleScene.h"
#include "QusetScene.h"
#include "BattleScene.h"
#include "EndScene.h"
#include "EventSystem.h"

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
	// 이미지 프레임
	{
		IMAGEMANAGER->AddFrameImage(TEXT("Actor1"), TEXT("../Resource/Images/Actor1.bmp"), 576, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Actor2"), TEXT("../Resource/Images/Actor2.bmp"), 576, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Actor3"), TEXT("../Resource/Images/Actor3.bmp"), 576, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Evil"), TEXT("../Resource/Images/Evil.bmp"), 576, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Monster"), TEXT("../Resource/Images/Monster.bmp"), 576, 384, 12, 8, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Outside_A2"), TEXT("../Resource/Images/Outside_A2.bmp"), 768, 576, 16, 12, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("TileIdle"), TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("AttackTile"), TEXT("../Resource/Images/AttackTile.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("Select"), TEXT("../Resource/Images/Select.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("SelectObject"), TEXT("../Resource/Images/SelectObject.bmp"), 96, 48, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("AttackTile"),TEXT("../Resource/Images/AttackTile.bmp"), 48, 48, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("TileMap_Cell_B"), TEXT("../Resource/Images/TileMap_Cell_B.bmp"), 768, 14736, 16, 307, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("TileMap_OBJ_B"), TEXT("../Resource/Images/TileMap_OBJ_B.bmp"), 768, 9216, 16, 192, true, COLOR_M);
		backGround = IMAGEMANAGER->AddImage(TEXT("Background"), TEXT("../Resource/Images/BackGround.bmp"), 1200,800, false, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("UI_Button"), TEXT("../Resource/Images/BUTTON.bmp"), 260, 192, 2, 4, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI1"), TEXT("../Resource/Images/UI1.bmp"), 252, 123,true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI2"), TEXT("../Resource/Images/UI2.bmp"), 253, 253,true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI3"), TEXT("../Resource/Images/UI3.bmp"), 140, 220,true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI4"), TEXT("../Resource/Images/UI4.bmp"), 383, 220,true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("UI5"), TEXT("../Resource/Images/UI5.bmp"), 132, 75,true, COLOR_M);

		IMAGEMANAGER->AddFrameImage(TEXT("SelectButton"), TEXT("../Resource/Images/BUTTON.bmp"), 260, 192, 2, 4, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("YesButton"), TEXT("../Resource/Images/YesButton.bmp"), 122, 65, 2,1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("NoButton"), TEXT("../Resource/Images/NoButton.bmp"), 122, 65, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("Map002"), TEXT("../Resource/Images/Map002.bmp"), 600, 600, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("TextBox"), TEXT("../Resource/Images/TextBox.bmp"), (WINSIZEX - 200), 300, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("TitleBG"), TEXT("../Resource/Images/TitleBG.bmp"), WINSIZEX, WINSIZEY, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("Book"), TEXT("../Resource/Images/Book.bmp"), WINSIZEX, WINSIZEY, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("StartBox"), TEXT("../Resource/Images/StartBox.bmp"), 300, 150, true, COLOR_M);
	}

	{
		IMAGEMANAGER->AddFrameImage(TEXT("Actor1_Face"), TEXT("../Resource/Images/Actor1_Face.bmp"), 576, 288, 4, 2, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Actor1_Face_B"), TEXT("../Resource/Images/Actor1_Face_B.bmp"), 1152, 576, 4, 2, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Actor2_Face_B"), TEXT("../Resource/Images/Actor2_Face_B.bmp"), 1152, 576, 4, 2, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Actor3_Face_B"), TEXT("../Resource/Images/Actor3_Face_B.bmp"), 1152, 576, 4, 2, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Actor2_Face"), TEXT("../Resource/Images/Actor2_Face.bmp"), 576, 288, 4, 2, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Actor3_Face"), TEXT("../Resource/Images/Actor3_Face.bmp"), 576, 288, 4, 2, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("Monster_Face"), TEXT("../Resource/Images/Monster_Face.bmp"), 576, 288, 4, 2, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("IconSet"), TEXT("../Resource/Images/IconSet.bmp"), 768, 8496, 16, 177, true, COLOR_M);
	}


	{
		RESOURCEMANAGER->AddScript(TEXT("MapData"));
		RESOURCEMANAGER->AddScript(TEXT("MapData_Layer01"));
		RESOURCEMANAGER->AddScript(TEXT("MapData_Layer02"));
		RESOURCEMANAGER->AddScript(TEXT("Map_1"));
		RESOURCEMANAGER->AddScript(TEXT("Map_2"));
		RESOURCEMANAGER->AddScript(TEXT("Map_3"));
		RESOURCEMANAGER->AddScript(TEXT("Map_4"));

		RESOURCEMANAGER->AddScript(TEXT("Talk"));
		RESOURCEMANAGER->AddScript(TEXT("SkillInfo"));

		PARSING->MapDataParsing(TEXT("Map_1"));
		//PARSING->MapDataParsing(TEXT("Map_2"));
		//PARSING->MapDataParsing(TEXT("Map_1"));
		PARSING->TalkParsing(TEXT("Talk"));

		GameTurnManager::GetSingleton()->Init();
		ButtonManager::GetSingleton()->Init();
		FontManager::GetSingleton()->Init();
		SkillSystem::GetSingleton()->Init();

	}

	{
		//IMAGEMANAGER->AddFrameImage(TEXT("Absorb"), TEXT("../Resource/Images/Absorb.bmp"), 960, 960, 5, 5, true, RGB(255, 255, 255));

		//EFFECTMANAGER->AddEffect(TEXT("Absorb"), TEXT("Absorb"), 960, 960, 5, 5, 1, 0.1f, 10, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Absorb"), TEXT("../Resource/Images/Absorb.bmp"), 960, 960, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Breath"), TEXT("../Resource/Images/Breath.bmp"), 960, 576, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("ClawSpecial2"), TEXT("../Resource/Images/ClawSpecial2.bmp"), 960, 576, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("ClawSpecial1"), TEXT("../Resource/Images/ClawSpecial1.bmp"), 960, 960, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Darkness1"), TEXT("../Resource/Images/Darkness1.bmp"), 960, 768, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Darkness2"), TEXT("../Resource/Images/Darkness2.bmp"), 960, 960, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Darkness3"), TEXT("../Resource/Images/Darkness3.bmp"), 960, 384, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Darkness4"), TEXT("../Resource/Images/Darkness4.bmp"), 960, 384, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Darkness5"), TEXT("../Resource/Images/Darkness5.bmp"), 960, 1152, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Cure1"), TEXT("../Resource/Images/Cure1.bmp"), 960, 1152, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Cure2"), TEXT("../Resource/Images/Cure2.bmp"), 960, 1152, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Cure3"), TEXT("../Resource/Images/Cure3.bmp"), 960, 1152, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Holy1"), TEXT("../Resource/Images/Holy1.bmp"), 960, 1152, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Holy2"), TEXT("../Resource/Images/Holy2.bmp"), 960, 1152, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Holy3"), TEXT("../Resource/Images/Holy3.bmp"), 960, 576, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Fire1"), TEXT("../Resource/Images/Fire1.bmp"), 960, 1152, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Fire2"), TEXT("../Resource/Images/Fire2.bmp"), 960, 384, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));
		EFFECTMANAGER->AddEffect(TEXT("Fire3"), TEXT("../Resource/Images/Fire3.bmp"), 960, 1152, 192, 192, 1, 1.0f, 20, RGB(255, 255, 255));

	}
	// Scene을 추가 작업 : 씬매니저를 초기화 하고 씬을 추가 하자 

	// 씬 초기화 
	EventSystem::GetSingleton()->Init();
	SCENEMANAGER->Init();
	GAMESYS->Init();

	// 씬 추가 

	// Test Scene
	//

	SCENEMANAGER->AddScene(TEXT("BattleSceneTest"), new BattleSceneTest());
	
	//
	SCENEMANAGER->AddScene(TEXT("LogoScene"), new LogoScene());
	SCENEMANAGER->AddScene(TEXT("TitleScene"), new TitleScene());
	SCENEMANAGER->AddScene(TEXT("QusetScene"), new QusetScene());
	SCENEMANAGER->AddScene(TEXT("BattleScene"), new BattleScene());
	SCENEMANAGER->AddScene(TEXT("EndScene"), new EndScene());



	// 첫 씬의 설정 
	SCENEMANAGER->ChangeScene(TEXT("EndScene"));
	
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
