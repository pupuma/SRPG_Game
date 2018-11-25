#include "Game.h"
#include "Map.h"
#include "TileCell.h"
#include "TileObject.h"
#include "Animation.h"
Map::Map(std::string _name)
	: Component(_name,0)
{
}


Map::~Map()
{
}

bool Map::Init( )
{
	width = TILEWIDTH;
	height = TILEHEIGHT;

	

	{
		mousePosImg = IMAGEMANAGER->FindImage(TEXT("Select"));
		assert(mousePosImg != NULL);

		//
		mouseMovePosImg = IMAGEMANAGER->FindImage(TEXT("SelectObject"));
		assert(mouseMovePosImg != NULL);

		isSelectMove = false;
		mouseMovePosAni = new Animation();
		mouseMovePosAni->Init(mouseMovePosImg);
		mouseMovePosAni->SetFPS(1);
		mouseMovePosAni->SetDefPlayFrame(false, true);
	}


	{
		int srcX = 0;
		int srcY = 0;
		int destX = 0;
		int destY = 0;
		int spriteSize = 48;
		for (int j = 0; j < 12; j++)
		{
			for (int i = 0; i < 16; i++)
			{
				Image* img = new Image();
				img->Init(TEXT("../Resource/Images/Outside_A2.bmp"), 768, 576, 16, 12, true, COLOR_M);
				assert(img != NULL);
				img->SetFrameX(srcX);
				img->SetFrameY(srcY);
				img->SetX(destX);
				img->SetY(destY);
				imgList.push_back(img);
				srcX++;
				destX += spriteSize;
			}
			destX = 0;
			srcX = 0;
			srcY++;
			destY += spriteSize;
		}
	}
	
	{
		//viewer = new Viewer(TEXT("Viewer"));
		
	}
	CreateTileMap();



	{
		tileSize = 48;

		renderWidth = WINSIZEX / tileSize + 1;
		renderHeight = WINSIZEY / tileSize + 1;

		
	}

	{
	}
	return true;
}

void Map::Deinit()
{
}

void Map::Update()
{
	{
		if (GAMESYS->IsAttacking())
		{

		}
	}
	//for (int y = 0; y < height; y++)
	//{
	//	for (int x = 0; x < width; x++)
	//	{
	//		tileArray[y][x]->Update();
	//	}
	//}

	//{
	//	int midTileCountX = renderWidth / 2;
	//	int midTileCountY = renderHeight / 2;

	//	int iCameraX = CAMERA->GetPosition()->x;
	//	int iCameraY = CAMERA->GetPosition()->y;
	//	int startTileX = viewer->GetTilePosition().x - iCameraX - midTileCountX - 1;
	//	int startTileY = viewer->GetTilePosition().y - iCameraY - midTileCountY - 1;

	//	int endTileX = startTileX + renderWidth + 1;
	//	int endTileY = startTileY + renderHeight + 1;

	//	if (width < endTileX)
	//	{
	//		endTileX = width;
	//	}
	//	if (height < endTileY)
	//	{
	//		endTileY = height;
	//	}

	//	POINT renderPos;
	//	renderPos.x = 0;
	//	renderPos.y = 0;
	//	int tileSize = 48;
	//	for (int j = startTileY; j < endTileY; j++)
	//	{
	//		if (0 <= j)
	//		{
	//			for (int i = startTileX; i < endTileX; i++)
	//			{
	//				if (0 <= i)
	//				{
	//					tileArray[j][i]->SetPosition(renderPos);
	//					//rect = RectMake(tileArray[j][i]->GetPosition().x, tileArray[j][i]->GetPosition().y,48,48);
	//					//rectList.push_back(rect);
	//				}
	//				renderPos.x += tileSize;
	//			}
	//		}
	//		renderPos.x = 0.0f;
	//		renderPos.y += tileSize;
	//	}

	//}
	//viewer->Update();

	//
#if defined(_DEBUG_TEST)


		RECT rc1, rcClient;
		GetClientRect(_hWnd, &rc1);

		POINT pt1, pt2;
		pt1.x = rc1.left;
		pt1.y = rc1.top;
		pt2.x = rc1.right;
		pt2.y = rc1.bottom;


		ClientToScreen(_hWnd, &pt1);
		ClientToScreen(_hWnd, &pt2);

		rcClient.left = pt1.x;
		rcClient.right = pt2.x;
		rcClient.top = pt1.y;
		rcClient.bottom = pt2.y;

		ClipCursor(&rcClient);
	//if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
	//{
	//	pt.x--;
	//}

	//if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
	//{
	//	pt.x++;
	//}

	//if (KEYMANAGER->IsOnceKeyDown(VK_UP))
	//{
	//	pt.y--;
	//}

	//if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
	//{
	//	pt.y++;
	//}
	CAMERA->setPosition(&pt);
#endif
	CAMERA->Update();
	UpdateViewer();
}

void Map::Render(HDC hdc)
{
	//img->Render(hdc);
	{
		int midTileCountX = renderWidth / 2;
		int midTileCountY = renderHeight / 2;

		int iCameraX = CAMERA->GetPosition()->x;
		int iCameraY = CAMERA->GetPosition()->y;
		int startTileX = viewer->GetTilePosition().x - iCameraX - midTileCountX - 1;
		int startTileY = viewer->GetTilePosition().y - iCameraY - midTileCountY - 1;

		int endTileX = startTileX + renderWidth + 1;
		int endTileY = startTileY + renderHeight + 1;

		if (width < endTileX)
		{
			endTileX = width;
		}
		if (height < endTileY)
		{
			endTileY = height;
		}

		POINT renderPos;
		renderPos.x = 0;
		renderPos.y = 0;
		int tileSize = 48;
		for (int j = startTileY; j < endTileY; j++)
		{
			if (0 <= j)
			{
				for (int i = startTileX; i < endTileX; i++)
				{
					if (0 <= i)
					{
						tileArray[j][i]->SetPosition(renderPos);
						tileArray[j][i]->Render(hdc);
						//rect = RectMake(tileArray[j][i]->GetPosition().x, tileArray[j][i]->GetPosition().y,48,48);
						//rectList.push_back(rect);
					}
					renderPos.x += tileSize;
				}
			}
			renderPos.x = 0.0f;
			renderPos.y += tileSize;
		}
	}

	{
		if (viewer != NULL)
		{
			// ĳ���� �̵� �Ÿ� 
			MaxTravelDistanceRender(hdc);
		}

#if defined (_DEBUG_TEST)
		//std::vector<RECT>::iterator it;
		//for (it = rectList.begin(); it != rectList.end(); it++)
		//{
		//	DrawObject(hdc, (*it), 1, RGB(125, 25, 125), RECTANGLE);
		//}

		TCHAR str[256];
		_stprintf(str, TEXT("Mouse [X] : %d , || [Y] : %d"), mouseTargetX, mouseTargetY);
		TextOut(hdc, 10, 30, str, _tcslen(str));


#endif // Rect
	}

	{
		// Mouse

		int iCameraX = CAMERA->GetPosition()->x;
		int iCameraY = CAMERA->GetPosition()->y;

		if (!isSelectMove)
		{
			mousePosImg->Render(hdc, rc.left - iCameraX, rc.top  - iCameraY);
		}
		else
		{
			mouseMovePosImg->AniRender(hdc, rc.left- iCameraX, rc.top - iCameraY, mouseMovePosAni);
		}

	}

	{
		//int tileSize = 48;
		//POINT renderPos = { 10,10 };
		//for (int j = 0; j < 32; j++)
		//{
		//	for (int i = 0; i < 32; i++)
		//	{
		//		tileArray[j][i]->SetPosition(renderPos);
		//		tileArray[j][i]->Render(hdc);
		//		renderPos.x += tileSize;
		//	}
		//	renderPos.x =10;
		//	renderPos.y += tileSize;


		//}
	}

	{
		//int midTileCountX = renderWidth / 2;
		//int midTileCountY = renderHeight / 2;

		//int startTileX = viewer->GetTilePosition().x - midTileCountX - 1;
		//int startTileY = viewer->GetTilePosition().y - midTileCountY - 1;

		//int endTileX = startTileX + renderWidth + 1;
		//int endTileY = startTileY + renderHeight + 1;

		//if (width < endTileX)
		//{
		//	endTileX = width;
		//}
		//if (height < endTileY)
		//{
		//	endTileY = height;
		//}

	
		//int tileSize = 48;

		//int iRenderWidth = 32;
		//int iRenderHeight = 32;

		//for (int j = startTileY; j < endTileY; j++)
		//{
		//	if (0 <= j)
		//	{
		//		for (int i = startTileX; i < endTileX; i++)
		//		{
		//			if (0 <= i)
		//			{
		//				LineMake(hdc, i * tileSize + tileArray[j][i]->GetPosition().x,
		//					tileArray[j][i]->GetPosition().y,
		//					i * tileSize + +tileArray[j][i]->GetPosition().x,
		//					iRenderWidth * tileSize + +tileArray[j][i]->GetPosition().y);

		//				//LineMake(hdc, tileArray[j][i]->GetPosition().x, i * tileSize + tileArray[j][i]->GetPosition().y,
		//				//	iRenderHeight * tileSize + tileArray[j][i]->GetPosition().x, i * tileSize + tileArray[j][i]->GetPosition().y);

		//			}
		//		}
		//	}
		//}

		//int tileSize = 48;
		//int renderWidth = 32;
		//int renderHeight = 32;
		//for (int i = 0; i <= 32; i++)
		//{
		//	LineMake(hdc, i * tileSize + tileArray[0][0]->GetPosition().x,
		//		tileArray[0][0]->GetPosition().y,
		//		i * tileSize + +tileArray[0][0]->GetPosition().x,
		//		renderWidth * tileSize + +tileArray[0][0]->GetPosition().y);
		//}
		//for (int i = 0; i <=  32; i++)
		//{
		//	LineMake(hdc, tileArray[0][0]->GetPosition().x, i * tileSize + tileArray[0][0]->GetPosition().y,
		//		renderHeight * tileSize + tileArray[0][0]->GetPosition().x, i * tileSize + tileArray[0][0]->GetPosition().y);
		//}
	}
}

void Map::Release()
{
}

void Map::Reset()
{
}

void Map::CreateTileMap()
{
	// Layer 1
	{
		std::vector<std::string> recordList = RESOURCEMANAGER->FindScript(TEXT("MapData_Layer01"));

		char record[1000];
		char* token;
		strcpy_s(record, recordList[0].c_str());
		token = strtok(record, ",");		// ù�� ° ĭ�� ��ŵ : mapsize
		token = strtok(NULL, ",");			// �ι� ° ���� ���� ũ�� : 16
		width = atoi(token);
		token = strtok(NULL, ",");			// ���� ° ���� ���� ũ�� : 10
		height = atoi(token);

		int line = 2;
		for (int y = 0; y < height; y++)
		{
			strcpy_s(record, recordList[line].c_str());
			token = strtok(record, ",");

			std::vector<TileCell*> rowList;
			for (int x = 0; x < width; x++)
			{
				int spriteIndex = atoi(token);
				Image* image = imgList[spriteIndex];

				TileCell* tileCell = new TileCell();
				tileCell->Init(x, y);

				// Ÿ�� ������Ʈ�� ����
				char name[256];
				//wsprintf(name, L"map_layer01_%d_%d", line, x);
				_stprintf(name, TEXT("map_layer01_%d_%d"), line, x);

				TileObject* tileObject = new TileObject(name, image, x, y, 0.1f);
				tileCell->AddComponent(tileObject);

				rowList.push_back(tileCell);

				token = strtok(NULL, ",");
			}
			tileArray.push_back(rowList);
			line++;
		}
	}

	{
		std::vector<std::string> recordList = RESOURCEMANAGER->FindScript(TEXT("MapData_Layer02"));

		char record[1000];
		char* token;

		// ù ° ������ �� ũ�� ����
		strcpy_s(record, recordList[0].c_str());
		token = strtok(record, ",");		// ù�� ° ĭ�� ��ŵ : mapsize
		token = strtok(NULL, ",");			// �ι� ° ���� ���� ũ�� : 16
		width = atoi(token);
		token = strtok(NULL, ",");			// ���� ° ���� ���� ũ�� : 10
		height = atoi(token);

		// �� ° ������ ��ŵ

		// ���� ° ���� ���Ͱ� ���� �� �ε��� ����Ÿ
		int line = 2;
		for (int y = 0; y < height; y++)
		{
			strcpy_s(record, recordList[line].c_str());
			token = strtok(record, ",");

			std::vector<TileCell*> rowList = tileArray[y];
			for (int x = 0; x < width; x++)
			{
				int spriteIndex = atoi(token);
				if (0 <= spriteIndex)
				{
					Image* sprite = imgList[spriteIndex];

					TileCell* tileCell = rowList[x];

					// Ÿ�� ������Ʈ�� ����
					char name[256];
					_stprintf(name, TEXT("map_layer02_%d_%d"), line, x);

					TileObject* tileObject = new TileObject(name, sprite, x, y , 0.2f);
					tileObject->SetCanMove(false);

					tileCell->AddComponent(tileObject);
				}

				token = strtok(NULL, ",");
			}
			tileArray.push_back(rowList);
			line++;
		}
	}


	{
		// 
		POINT renderPos;
		renderPos.x = 0;
		renderPos.y = 0;
		int tileSize = 48;

		for (int j = 0; j < 33; j++)
		{
			for (int i = 0; i < 33; i++)
			{
				tileArray[j][i]->SetPosition(renderPos);
				renderPos.x += tileSize;

			}
			renderPos.x = 0.0f;
			renderPos.y += tileSize;
		}

	}
}

void Map::SetTileComponent(TilePoint tilePosition, Component * component)
{
	tileArray[tilePosition.y][tilePosition.x]->AddComponent(component);

}

void Map::ResetTileComponent(TilePoint tilePosition, Component * component)
{
	tileArray[tilePosition.y][tilePosition.x]->RemoveComponent(component);
}

void Map::SetViewer(Component* _com)
{
	//if (viewer != NULL)
	//{
	//	viewer->SetViewer(_com);
	//}
	viewer = _com;
	//tileAttackList = GAMESYS->GetTileAttackList();
	prevViewTilePosition = viewer->GetTilePosition();

	// ���� ��ġ �ڱ� �ڽ��� ���� Ÿ�� -> 
	//
	RECT rcClient, rcWorld;
	rcClient = { 0, 0, WINSIZEX, WINSIZEY };
	rcWorld = { 0, 0, 5000, 6000 };
	pt = viewer->GetPosition();
	CAMERA->Init(&pt, rcClient, rcWorld);
	MaxTravelDistance(viewer);
}

void Map::UpdateViewer()
{
	if (NULL == viewer)
	{
		return;
	}


	// ���콺 
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &(_ptMouse));
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));

		int mouseX = (int)_ptMouse.x;
		int mouseY = (int)_ptMouse.y;
		
		if (mouseX < 0)
		{
			mouseX = 0;
		}
		if (mouseX > WINSIZEX)
		{
			mouseX = WINSIZEX;
		}

		if (mouseY < 0)
		{
			mouseY = 0;
		}
		if (mouseY > WINSIZEY)
		{
			mouseY = WINSIZEY;
		}


		TileCell* tileCell = map->FindTileCellByMousePosition(mouseX, mouseY);

		if (tileCell != NULL)
		{
			mouseTargetX = tileCell->GetTilePosition().x;
			mouseTargetY = tileCell->GetTilePosition().y;
		}
		else
		{
			mouseTargetX = 0;
			mouseTargetY = 0;
		}

		if (tileCell != NULL)
		{
			isSelectMove = false;

			rc = RectMake(tileCell->GetPosition().x, tileCell->GetPosition().y, 48, 48);
			mouseMovePosAni->Stop();
		}


		std::list<TileInfo>::iterator it;
		if (tileCell != NULL)
		{
			for (it = tileCellOpenList.begin(); it != tileCellOpenList.end(); it++)
			{
				if ((*it).tile->GetTilePosition().x == tileCell->GetTilePosition().x &&
					(*it).tile->GetTilePosition().y == tileCell->GetTilePosition().y)
				{
					isSelectMove = true;
					mouseMovePosAni->Start();
					rc = RectMake(tileCell->GetPosition().x, tileCell->GetPosition().y, 48, 48);
					break;
				}
				
			}
		}
		mouseMovePosAni->FrameUpdate(TIMEMANAGER->GetElapsedTime() * 10);

	}
	
}

TileCell* Map::FindTileCell(TilePoint _searchTilePosision)
{
	if (_searchTilePosision.x < 0 || width <= _searchTilePosision.x ||
		_searchTilePosision.y < 0 || height <= _searchTilePosision.y)
	{
		return NULL;
	}
	return tileArray[_searchTilePosision.y][_searchTilePosision.x];
}

void Map::MaxTravelDistance(Component * _target)
{
	TilePoint startPos = _target->GetTilePosition();
	
	targetStartPosition = startPos;
	targetTileCell = tileArray[startPos.y][startPos.x];
	//targetTileCell->SetSearchPathfinding(false);
	tileArray[startPos.y][startPos.x]->SetSearchPathfinding(false);
	//
	int distance = _target->GetMaxMoving();
	bool isSearch = false;

	//

	MaxPathFinder(distance, startPos);
	// ���⼭ ��ġ�� �� ���Ѵ�. 


}

void Map::MaxTravelDistanceRender(HDC hdc)
{
	//this->moveTileList = GAMESYS->GetMoveTileList();
	//std::list<TileInfo>::iterator it;
	//if (!this->moveTileList.empty())
	//{
	//	for (it = moveTileList.begin(); it != moveTileList.end(); it++)
	//	{
	//		//(*it)->Render(hdc, (*it)->GetX(), (*it)->GetY());
	//		(*it).tileImg->AlphaRender(hdc, (*it).tile->GetPosition().x, (*it).tile->GetPosition().y,200);
	//	}
	//}
	{

		int iCameraX = CAMERA->GetPosition()->x;
		int iCameraY = CAMERA->GetPosition()->y;

		if (!GAMESYS->IsAction())
		{
			


			std::list<TileInfo>::iterator it;
			if (!tileCellOpenList.empty())
			{
				for (it = tileCellOpenList.begin(); it != tileCellOpenList.end(); it++)
				{
					(*it).tileImg->AlphaRender(hdc, (*it).tile->GetPosition().x - iCameraX, (*it).tile->GetPosition().y - iCameraY, 150);
				}
			}
		}

		if (GAMESYS->IsAttacking())
		{
			std::vector<TileInfo>::iterator it;
			if (!tileAttackList.empty())
			{
				for (it = tileAttackList.begin(); it != tileAttackList.end(); it++)
				{
					(*it).tileImg->AlphaRender(hdc, (*it).tile->GetPosition().x - iCameraX, (*it).tile->GetPosition().y - iCameraY, 3);
				}
			}
		}
	}
}

// ���� ���� int _distance, TilePoint _pos
void Map::MaxPathFinder(int _distance, TilePoint _pos)
{
	//
	{
		ResetPahtfinding();
		// first
		for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
		{
			TilePoint currentTilePosition = targetTileCell->GetTilePosition();
			TilePoint searchTilePosision = GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
			TileCell*  searchTileCell = FindTileCell(searchTilePosision);

			if (searchTilePosision.x < 0 || searchTilePosision.x > 32 ||
				searchTilePosision.y < 0 || searchTilePosision.y > 32)
			{
				continue;
			}

			if (searchTilePosision.x == targetStartPosition.x && searchTilePosision.y == targetStartPosition.y ||
				tileArray[searchTilePosision.y][searchTilePosision.x]->IsSearchPathfinding() == true || false == searchTileCell->CanMove())
			{
				continue;
			}

			searchTileCell->SetSearchPathfinding(true);

			tileInfo.tile = searchTileCell;
			tileInfo.tileImg = new Image();
			tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

			tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
			tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

			tileCellOpenList.push_back(tileInfo);

			std::pair<TileCell*, int> p_data;
			pathfindingQueue.push(searchTileCell);
		}
		_distance -= 1;
		// second 

		//
		//std::priority_queue<TileCell*> prevPathfindingQueue;
		std::queue<TileCell*> prevPathfindingQueue;

		while (_distance > 0)
		{
			if (!pathfindingQueue.empty())
			{
				targetTileCell = pathfindingQueue.front();
				pathfindingQueue.pop();

				for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
				{
					TilePoint currentTilePosition = targetTileCell->GetTilePosition();
					TilePoint searchTilePosision = GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
					TileCell*  searchTileCell = FindTileCell(searchTilePosision);

					if (searchTilePosision.x < 0 || searchTilePosision.x > 32 ||
						searchTilePosision.y < 0 || searchTilePosision.y > 32)
					{
						continue;
					}

					if (searchTilePosision.x == targetStartPosition.x && searchTilePosision.y == targetStartPosition.y ||
						tileArray[searchTilePosision.y][searchTilePosision.x]->IsSearchPathfinding() == true || false == searchTileCell->CanMove())
					{
						continue;
					}

					searchTileCell->SetSearchPathfinding(true);

					tileInfo.tile = searchTileCell;
					tileInfo.tileImg = new Image();
					tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

					tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
					tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

					tileCellOpenList.push_back(tileInfo);

					std::pair<TileCell*, int> p_data;
					prevPathfindingQueue.push(searchTileCell);
				}
			}

			if (pathfindingQueue.empty())
			{
				_distance -= 1;
				pathfindingQueue = prevPathfindingQueue;
				for (size_t i = 0; i < prevPathfindingQueue.size(); i++)
				{
					prevPathfindingQueue.pop();
				}
			}

		}


		/*
		for (size_t i = 0; i < pathfindingQueue.size(); i++)
					{
						targetTileCell = pathfindingQueue.top();
						pathfindingQueue.pop();

						for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
						{
							TilePoint currentTilePosition = targetTileCell->GetTilePosition();
							TilePoint searchTilePosision = GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);

							if (searchTilePosision.x == targetStartPosition.x && searchTilePosision.y == targetStartPosition.y ||
								tileArray[searchTilePosision.y][searchTilePosision.x]->IsSearchPathfinding() == true)
							{
								continue;
							}

							TileCell*  searchTileCell = FindTileCell(searchTilePosision);
							searchTileCell->SetSearchPathfinding(true);

							tileInfo.tile = searchTileCell;
							tileInfo.tileImg = new Image();
							tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

							tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
							tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

							tileCellOpenList.push_back(tileInfo);

							std::pair<TileCell*, int> p_data;
							prevPathfindingQueue.push(searchTileCell);
						}
		*/


		//for (int direction = 0; direction < (int)eDirection::DIR_NONE; direction++)
		//{
		//	TilePoint currentTilePosition = targetTileCell->GetTilePosition();
		//	TilePoint searchTilePosision = GetSearchTilePositionByDirection(currentTilePosition, (eDirection)direction);
		//	
		//	if (searchTilePosision.x == targetStartPosition.x && searchTilePosision.y == targetStartPosition.y ||
		//		tileArray[searchTilePosision.y][searchTilePosision.x]->IsSearchPathfinding() == true)
		//	{
		//		continue;
		//	}

		//	TileCell*  searchTileCell = FindTileCell(searchTilePosision);
		//	searchTileCell->SetSearchPathfinding(true);

		//	tileInfo.tile = searchTileCell;
		//	tileInfo.tileImg = new Image();
		//	tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

		//	tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		//	tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

		//	tileCellOpenList.push_back(tileInfo);
		//	
		//	std::pair<TileCell*, int> p_data;
		//	pathfindingQueue.push(searchTileCell);
		//}

		//MaxPathFinder(_distance, targetTileCell->GetTilePosition());


		//
	}

	{
		while (!pathfindingQueue.empty())
		{
			pathfindingQueue.pop();
		}
	}
	/*{

		if (_distance <= 0 )
		{
			return;
		}

		
		TilePoint upTile = { _pos.x , _pos.y - 1 };
		TilePoint downTile = { _pos.x , _pos.y + 1 };
		TilePoint leftTile = { _pos.x - 1, _pos.y };
		TilePoint rightTile = { _pos.x + 1,_pos.y };
		
		
		if (upTile.x == targetStartPosition.x &&  upTile.y == targetStartPosition.y ||
			downTile.x == targetStartPosition.x &&  downTile.y == targetStartPosition.y ||
			leftTile.x == targetStartPosition.x &&  leftTile.y == targetStartPosition.y ||
			rightTile.x == targetStartPosition.x &&  rightTile.y == targetStartPosition.y)
		{
			_distance++;
			return;
		}


		if (tileArray[upTile.y][upTile.x] != NULL && upTile.y > 0 &&
			tileArray[upTile.y][upTile.x]->IsSearchPathfinding() == false)
		{
			
			tileInfo.tile = tileArray[upTile.y][upTile.x];
			tileInfo.tileImg = new Image();
			tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

			tileInfo.tileImg->SetX(tileArray[upTile.y][upTile.x]->GetPosition().x);
			tileInfo.tileImg->SetY(tileArray[upTile.y][upTile.x]->GetPosition().y);


			tileCellOpenList.push_back(tileInfo);
			tileArray[upTile.y][upTile.x]->SetSearchPathfinding(true);
			 

			MaxPathFinder(_distance - 1, upTile);
		}

		if (tileArray[downTile.y][downTile.x] != NULL && downTile.y < 33 &&
			tileArray[downTile.y][downTile.x]->IsSearchPathfinding() == false)
		{
		
			tileInfo.tile = tileArray[downTile.y][downTile.x];
			tileInfo.tileImg = new Image();
			tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

			tileInfo.tileImg->SetX(tileArray[downTile.y][downTile.x]->GetPosition().x);
			tileInfo.tileImg->SetY(tileArray[downTile.y][downTile.x]->GetPosition().y);

			tileCellOpenList.push_back(tileInfo);
			tileArray[downTile.y][downTile.x]->SetSearchPathfinding(true);
			 

			MaxPathFinder(_distance - 1, downTile);
		}

		if (tileArray[leftTile.y][leftTile.x] != NULL && leftTile.x > 0 &&
			tileArray[leftTile.y][leftTile.x]->IsSearchPathfinding() == false)
		{
			
			tileInfo.tile = tileArray[leftTile.y][leftTile.x];
			tileInfo.tileImg = new Image();
			tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

			tileInfo.tileImg->SetX(tileArray[leftTile.y][leftTile.x]->GetPosition().x);
			tileInfo.tileImg->SetY(tileArray[leftTile.y][leftTile.x]->GetPosition().y);

			tileCellOpenList.push_back(tileInfo);
			tileArray[leftTile.y][leftTile.x]->SetSearchPathfinding(true);
			 

			MaxPathFinder(_distance - 1, leftTile);
		}

		if (tileArray[rightTile.y][rightTile.x] != NULL && rightTile.x < 33 &&
			tileArray[rightTile.y][rightTile.x]->IsSearchPathfinding() == false)
		{
			
			tileInfo.tile = tileArray[rightTile.y][rightTile.x];
			tileInfo.tileImg = new Image();
			tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);

			tileInfo.tileImg->SetX(tileArray[rightTile.y][rightTile.x]->GetPosition().x);
			tileInfo.tileImg->SetY(tileArray[rightTile.y][rightTile.x]->GetPosition().y);

			tileCellOpenList.push_back(tileInfo);
			tileArray[rightTile.y][rightTile.x]->SetSearchPathfinding(true);
			 

			MaxPathFinder(_distance - 1, rightTile);
		}

		
	}*/
}



TilePoint Map::GetSearchTilePositionByDirection(TilePoint tilePosition, eDirection direction)
{
	TilePoint searchTilePosition = tilePosition;
	switch (direction)
	{
	case eDirection::DIR_LEFT:
		searchTilePosition.x--;
		break;
	case eDirection::DIR_RIGHT:
		searchTilePosition.x++;
		break;
	case eDirection::DIR_UP:
		searchTilePosition.y--;
		break;
	case eDirection::DIR_DOWN:
		searchTilePosition.y++;
		break;
	}
	return searchTilePosition;
}



TileCell* Map::FindTileCellByMousePosition(int _mouseX, int _mouseY)
{

	
	int midX = WINSIZEX / 2;
	int midY = WINSIZEY/ 2;


	int iCameraX = CAMERA->GetPosition()->x;
	int iCameraY = CAMERA->GetPosition()->y;


	int minX = viewer->GetTilePosition().x - iCameraX - (midX / tileSize) - 1;
	int maxX = viewer->GetTilePosition().x - iCameraX + (midX / tileSize) + 1;
	int minY = viewer->GetTilePosition().y - iCameraY - (midY / tileSize) - 1;
	int maxY = viewer->GetTilePosition().y - iCameraY + (midY / tileSize) + 1;

	if (minX < 0)
	{
		minX = 0;
	}
	if (width < maxX)
	{
		maxX = width;
	}
	if (minY < 0)
	{
		minY = 0;
	}
	if (height < maxY)
	{
		maxY = height;
	}

	for (int y = minY; y < maxY; y++)
	{
		for (int x = minX; x < maxX; x++)
		{
			TilePoint tilePosition;
			tilePosition.x = x;
			tilePosition.y = y;

			//RECT rect;
			rect = RectMake(FindTileCell(tilePosition)->GetPosition().x, FindTileCell(tilePosition)->GetPosition().y, 48, 48);
			//rect.left = FindTileCell(tilePosition)->GetPosition().x - tileSize / 2;
			//rect.right = FindTileCell(tilePosition)->GetPosition().x + tileSize / 2;
			//rect.top = FindTileCell(tilePosition)->GetPosition().y - tileSize / 2;
			//rect.bottom = FindTileCell(tilePosition)->GetPosition().y + tileSize / 2;

			rectList.push_back(rect);
			if (rect.left <= _mouseX && _mouseX <= rect.right &&
				rect.top <= _mouseY && _mouseY <= rect.bottom)
			{
				return FindTileCell(tilePosition);
			}
		}
	}
	return NULL;
}

void Map::ResetPahtfinding()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			TilePoint tilePosition;
			tilePosition.x = x;
			tilePosition.y = y;
			FindTileCell(tilePosition)->ResetPathfinding();
		}
	}

	{
		/*std::list<TileInfo>::iterator it;
		for (it = tileCellOpenList.begin(); it != tileCellOpenList.end(); it++)
		{
			TilePoint tilePosition;
			tilePosition.x = (*it).tile->GetTilePosition().x;
			tilePosition.y = (*it).tile->GetTilePosition().y;

			FindTileCell(tilePosition)->ResetPathfinding();
		}
*/
	}
}

void Map::SortTile()
{
	for (int j = 0; j < TILEHEIGHT; j++)
	{
		for (int i = 0; i < TILEWIDTH; i++)
		{
			tileArray[j][i]->DeepSort();
		}
	}
}

void Map::ResetViewer()
{
	ReleaseOpenList();
	prevViewTilePosition = viewer->GetTilePosition();
	MaxTravelDistance(viewer);
}

void Map::ReleaseOpenList()
{
	std::list<TileInfo>::iterator it;
	for (it = tileCellOpenList.begin(); it != tileCellOpenList.end(); it++)
	{
		(*it).tileImg->Release();
		delete it->tileImg;
	}

	
	tileCellOpenList.clear();


}

std::vector<Component*> Map::SetAttackRange()
{

	{
		TileInfo tileInfo;
		
		TilePoint t1 = viewer->GetTilePosition();
		t1.x--;
		TileCell*  searchTileCell = FindTileCell(t1);

		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = new Image();
		tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);


		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

		tileAttackList.push_back(tileInfo);

		//
		TilePoint t2 = viewer->GetTilePosition();
		t2.x++;
		searchTileCell = FindTileCell(t2);

		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = new Image();
		tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);


		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

		tileAttackList.push_back(tileInfo);

		//
		//
		TilePoint t3 = viewer->GetTilePosition();
		t3.y--;
		searchTileCell = FindTileCell(t3);

		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = new Image();
		tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);


		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

		tileAttackList.push_back(tileInfo);

		//
		//
		TilePoint t4 = viewer->GetTilePosition();
		t4.y++;
		searchTileCell = FindTileCell(t4);

		tileInfo.tile = searchTileCell;
		tileInfo.tileImg = new Image();
		tileInfo.tileImg->Init(TEXT("../Resource/Images/TileIdle.bmp"), 48, 48, true, COLOR_M);


		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);

		tileAttackList.push_back(tileInfo);


	}


	return std::vector<Component*>();
}
