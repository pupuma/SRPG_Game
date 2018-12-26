#include "Game.h"
#include "GameUI.h"

#include "SelectStateButton.h"
#include "GameYesNoButton.h"
#include "FontManager.h"

#include "GameTurnManager.h"
#include "Character.h"
#include "TileCell.h"
#include "Component.h"
GameUI::GameUI()
{
}


GameUI::~GameUI()
{
}

bool GameUI::Init()
{
	{
		selectYNButton = new GameYesNoButton();
		selectYNButton->Init();
	}
	{
		selectStateButton = new SelectStateButton();
		selectStateButton->Init();
		isActive = false;

		rcTopTimer = RectMake(552, 0, 96, 96);
		rcTest1 = RectMake(11, 407, 252, 123);
		rcTest2 = RectMake(31, 533, 253, 253);
		rcTest3 = RectMake(320, 549, 140, 220);
		rcTest4 = RectMake(498, 549, 383, 220);
		//rcTest5 = RectMake(535, 465, 130, 75);
		rcTest6 = RectMake(917, 533, 253, 253);
		rcTest7 = RectMake(937, 407, 252, 123);

		imgTest1 = IMAGEMANAGER->FindImage(TEXT("UI1"));
		imgTest2 = IMAGEMANAGER->FindImage(TEXT("UI2"));
		imgTest3 = IMAGEMANAGER->FindImage(TEXT("UI3"));
		imgTest4 = IMAGEMANAGER->FindImage(TEXT("UI4"));
		//imgTest5 = IMAGEMANAGER->FindImage(TEXT("UI5"));
		imgTest6 = IMAGEMANAGER->FindImage(TEXT("UI2"));
		imgTest7 = IMAGEMANAGER->FindImage(TEXT("UI1"));

		turnImg = NULL;
		clickImg = NULL;
	}
	return false;
}

void GameUI::Release()
{
	selectYNButton->Release();
	selectStateButton->Release();

	SAFE_DELETE(selectYNButton);
	SAFE_DELETE(selectStateButton);


}


void GameUI::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('3'))
	{
		isActive = true;
	}
	if (KEYMANAGER->IsOnceKeyDown('4'))
	{
		isActive = false;
	}

	if (isActive)
	{
		selectStateButton->Update();
		selectYNButton->Update();

		leftMaxHp = GameTurnManager::GetSingleton()->GetTurn()->MaxGetHp();
		leftHp = GameTurnManager::GetSingleton()->GetTurn()->GetHp();

		leftMaxMp = GameTurnManager::GetSingleton()->GetTurn()->GetMaxMp();
		leftMp = GameTurnManager::GetSingleton()->GetTurn()->GetMp();

		TileCell* tile = GAMESYS->GetSaveClickTileCell();

		if (tile != NULL)
		{
			std::list<Component*>::iterator it;
			if (!tile->GetTileComponentList().empty())
			{
				std::list<Component*> comList = tile->GetTileComponentList();
				for (it = comList.begin(); it != comList.end(); it++)
				{
					if ((*it)->GetComponetType() == eComponentType::CT_PLAYER ||
						(*it)->GetComponetType() == eComponentType::CT_MONSTER ||
						(*it)->GetComponetType() == eComponentType::CT_NPC)
					{
						clickChar = (Character*)(*it);
						break;
					}
				}
				if (clickChar != NULL)
				{
					rightHp = clickChar->GetHp();
					rightMaxHp = clickChar->MaxGetHp();

					rightMp = clickChar->GetMp();
					rightMaxMp = clickChar->GetMaxMp();
				}
			}
			
		
		}
		
		turnImg = GameTurnManager::GetSingleton()->GetFaceImg();

		clickImg = GameTurnManager::GetSingleton()->FindFaceImg(clickChar);
		turnImg = GameTurnManager::GetSingleton()->FindFaceImg(GameTurnManager::GetSingleton()->GetTurn());

	}


}

void GameUI::Render(HDC hdc)
{
	if (isActive)
	{
		//DrawObject(hdc, rcTopTimer, 1, RGB(255, 0, 0), RECTANGLE);
		//DrawObject(hdc, rcTest1, 1, RGB(125, 0, 125), RECTANGLE);
		//DrawObject(hdc, rcTest2, 1, RGB(125, 255, 125), RECTANGLE);
		//DrawObject(hdc, rcTest3, 1, RGB(125, 125, 125), RECTANGLE);
		//DrawObject(hdc, rcTest4, 1, RGB(125, 125, 125), RECTANGLE);
		//DrawObject(hdc, rcTest5, 1, RGB(255, 255, 125), RECTANGLE);
		//DrawObject(hdc, rcTest6, 1, RGB(125, 255, 125), RECTANGLE);
		//DrawObject(hdc, rcTest7, 1, RGB(125, 0, 125), RECTANGLE);


		//

		imgTest1->Render(hdc, rcTest1.left, rcTest1.top);
		imgTest2->Render(hdc, rcTest2.left, rcTest2.top);
		imgTest3->Render(hdc, rcTest3.left, rcTest3.top);
		imgTest4->Render(hdc, rcTest4.left, rcTest4.top);
	
		//imgTest5->Render(hdc, rcTest5.left, rcTest5.top);
		//
		//
		if (GAMESYS->IsClickCharacter())
		{
			imgTest6->Render(hdc, rcTest6.left, rcTest6.top);
			imgTest7->Render(hdc, rcTest7.left, rcTest7.top);

			POINT pt = { WINSIZEX - 250, 420 };
			FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG"), TEXT("HP"), &pt, RGB(255, 0, 0));

			POINT pt2 = { WINSIZEX - 250, 475 };
			FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG"), TEXT("Attack"), &pt2, RGB(0, 0, 0));

			RECT rc = RectMake(WINSIZEX - 200, 420, 170, 30);
			FontManager::GetSingleton()->TextGaugeRender(hdc, rightHp, rightMaxHp, &rc, RGB(0, 0, 0));

			rc = RectMake(WINSIZEX - 200, 495, 475, 30);
			//FontManager::GetSingleton()->TextGaugeRender(hdc, rightMp, rightMaxMp, &rc, RGB(0, 0, 0));
		

			if (clickImg != NULL)
			{
				if (clickChar != NULL)
				{
					if (clickChar->IsLive())
					{
						clickImg->FrameRender(hdc, rcTest6.left + 60, rcTest6.top + 20, clickChar->GetFaceFrameX(), clickChar->GetFaceFrameY());
						POINT pt = { rcTest6.left + 50 ,rcTest6.bottom - 70 };
						std::string name = clickChar->GetName();
						FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG"), name, &pt, RGB(255, 0, 255));

						TCHAR str[256];

						_stprintf(str, TEXT("%d"), clickChar->GetAttackPoint());
						POINT pt3 = { WINSIZEX - 100, 475 };
						FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG"), str, &pt3, RGB(0, 0, 0));

					}


				}
			}
		}

		if (turnImg != NULL)
		{
			turnChar = GameTurnManager::GetSingleton()->GetTurn();
			if (turnChar != NULL)
			{
				turnImg->FrameRender(hdc, rcTest2.left + 60, rcTest2.top + 20, turnChar->GetFaceFrameX(), turnChar->GetFaceFrameY());
				POINT pt = { rcTest2.left +  50 , rcTest2.bottom - 70 };
				std::string name = turnChar->GetName();
				FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG"), name, &pt, RGB(255, 0, 255));

			}
		}
		//
		selectStateButton->Render(hdc);
		selectYNButton->Render(hdc);

		{
			RECT rc = RectMake(70, 420, 170, 30);
			FontManager::GetSingleton()->TextGaugeRender(hdc, leftHp, leftMaxHp, &rc, RGB(0, 0, 0));
			
			rc = RectMake(70, 475, 170, 30);
			FontManager::GetSingleton()->TextGaugeRender(hdc, leftMp, leftMaxMp, &rc, RGB(0, 0, 0));


		}
#if defined(_DEBUG_TEST)
		{
			POINT pt = { 27, 420 };
			FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG"), TEXT("HP"), &pt, RGB(255,0,0));

			POINT pt2 = { 27, 475 };
			FontManager::GetSingleton()->RenderText(hdc, TEXT("NBG"), TEXT("MP"), &pt2, RGB(0, 0, 255));
			
		}
#endif//
	}
	

}
