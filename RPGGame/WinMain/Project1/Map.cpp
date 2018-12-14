#include "Game.h"
#include "Map.h"
#include "TileCell.h"
#include "TileObject.h"
#include "Animation.h"
#include "GameTurnManager.h"

Map::Map(std::string _name)
	: Component(_name,0)
{
}


Map::~Map()
{
}

bool Map::Init( )
{
	//width = TILEWIDTH;
	//height = TILEHEIGHT;
	width = PARSING->GetTileWidth();
	height = PARSING->GetTIleHeight();
	

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


	// TileMapCreateSampleTile
	TileMapCreateSampleTile();
	if (PARSING->GetLayerSize() == 3)
	{
		TileMapCreateSampleObject();
	}

	CreateTileMap();

	// Init Info 
	{

		tileSize = 48;

		renderWidth = (WINSIZEX + 350) / tileSize +1;
		renderHeight = (WINSIZEY + 350)/ tileSize + 1;
	}

	return true;
}

void Map::Deinit()
{
}

void Map::Update()
{

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
		renderPos.x = -350;
		renderPos.y = -350;
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
			renderPos.x = -350;
			renderPos.y += tileSize;
		}
	}

	{
		if (viewer != NULL)
		{
			// 캐릭터 이동 거리 
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
				mousePosImg->Render(hdc, rc.left - iCameraX, rc.top - iCameraY);
			}
			else
			{
				if (GameTurnManager::GetSingleton()->PlayerTrun())
				{
					mouseMovePosImg->AniRender(hdc, rc.left - iCameraX, rc.top - iCameraY, mouseMovePosAni);
				}
				else
				{
					mousePosImg->Render(hdc, rc.left - iCameraX, rc.top - iCameraY);
				}
			}
		
	}

	{
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
	//LayerBase();
	//LayerTile();
	//LayerObject();
	//
	switch (PARSING->GetLayerSize())
	{
	case 1:
		LayerBase();
		break;
	case 2:
		LayerBase();
		LayerTile();
		break;
	case 3:
		LayerBase();
		LayerTile();
		LayerObject();
		break;
	}

	{
		// 
		POINT renderPos;
		renderPos.x = 0;
		renderPos.y = 0;
		int tileSize = 48;

		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
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

void Map::SetTileComponent(TilePoint tilePosition, Component * component, bool _isCharacter)
{
	tileArray[tilePosition.y][tilePosition.x]->AddComponent(component);
	tileArray[tilePosition.y][tilePosition.x]->IsCharacter(_isCharacter);
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

	OpenListClear();

	viewer = _com;
	//tileAttackList = GAMESYS->GetTileAttackList();
	prevViewTilePosition = viewer->GetTilePosition();
	// 현재 위치 자기 자신의 정보 타겟 -> 
	//
	RECT rcClient, rcWorld;
	rcClient = { 0, 0, WINSIZEX, WINSIZEY };
	rcWorld = { 0, 0, 5000, 6000 };
	pt = { 0 , 0};
	CAMERA->Init(&pt, rcClient, rcWorld);
	MaxTravelDistance(viewer);
}

void Map::UpdateViewer()
{
	if (NULL == viewer)
	{
		return;
	}


	// 마우스 
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
			if (!tileCellOpenList.empty())
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

			if (tileAttackList.size() >= 1)
			{
				for (size_t i = 0; i < tileAttackList.size(); i++)
				{
					if(tileAttackList[i].tile->GetTilePosition().x == tileCell->GetTilePosition().x &&
						tileAttackList[i].tile->GetTilePosition().y == tileCell->GetTilePosition().y)
					{
						isSelectMove = true;
						mouseMovePosAni->Start();
						rc = RectMake(tileCell->GetPosition().x, tileCell->GetPosition().y, 48, 48);
					}
				}
			}
			
		}
		mouseMovePosAni->FrameUpdate(TIMEMANAGER->GetElapsedTime() * 10);

	}
	
}

void Map::OpenListClear()
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
	tileCellOpenList.clear();
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
	// 여기서 위치를 다 구한다. 


}

void Map::MaxTravelDistanceRender(HDC hdc)
{
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
			if (GameTurnManager::GetSingleton()->MyTurn(viewer->GetTilePosition()))
			{
				std::vector<TileInfo>::iterator it;
				if (!tileAttackList.empty())
				{
					for (it = tileAttackList.begin(); it != tileAttackList.end(); it++)
					{
						(*it).tileImg->AlphaRender(hdc, (*it).tile->GetPosition().x - iCameraX, (*it).tile->GetPosition().y - iCameraY, 150);
					}
				}
			}
			
		}
	}
}

// 수정 사항 int _distance, TilePoint _pos

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
			tileInfo.distance = _distance;
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

					if (searchTilePosision.x < 0 || searchTilePosision.x >= width ||
						searchTilePosision.y < 0 || searchTilePosision.y >= height)
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
					tileInfo.distance = _distance;

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
	}

	{
		while (!pathfindingQueue.empty())
		{
			pathfindingQueue.pop();
		}

		for (auto a : tileCellOpenList)
		{
			a.tile->SetSearchPathfinding(false);
		}
	}
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

	
	int midX = (WINSIZEX) / 2;
	int midY = (WINSIZEY) / 2;


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

			//rectList.push_back(rect);
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
	//tileCellOpenList.clear();
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
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
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
//
//void Map::SetAttackRange()
//{
//
//	{
//
//		ResetAttackList();
//
//		// 정보를 미리 저장 
//		TileInfo tileInfo;
//		
//		TilePoint t1 = viewer->GetTilePosition();
//		t1.x--;
//		TileCell*  searchTileCell = FindTileCell(t1);
//
//		tileInfo.tile = searchTileCell;
//		tileInfo.tileImg = new Image();
//		tileInfo.tileImg->Init(TEXT("../Resource/Images/AttackTile.bmp"), 48, 48, true, COLOR_M);
//
//
//		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
//		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
//
//		tileAttackList.push_back(tileInfo);
//
//		//
//		TilePoint t2 = viewer->GetTilePosition();
//		t2.x++;
//		searchTileCell = FindTileCell(t2);
//
//		tileInfo.tile = searchTileCell;
//		tileInfo.tileImg = new Image();
//		tileInfo.tileImg->Init(TEXT("../Resource/Images/AttackTile.bmp"), 48, 48, true, COLOR_M);
//
//
//		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
//		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
//
//		tileAttackList.push_back(tileInfo);
//
//		//
//		//
//		TilePoint t3 = viewer->GetTilePosition();
//		t3.y--;
//		searchTileCell = FindTileCell(t3);
//
//		tileInfo.tile = searchTileCell;
//		tileInfo.tileImg = new Image();
//		tileInfo.tileImg->Init(TEXT("../Resource/Images/AttackTile.bmp"), 48, 48, true, COLOR_M);
//
//
//		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
//		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
//
//		tileAttackList.push_back(tileInfo);
//
//		//
//		//
//		TilePoint t4 = viewer->GetTilePosition();
//		t4.y++;
//		searchTileCell = FindTileCell(t4);
//
//		tileInfo.tile = searchTileCell;
//		tileInfo.tileImg = new Image();
//		tileInfo.tileImg->Init(TEXT("../Resource/Images/AttackTile.bmp"), 48, 48, true, COLOR_M);
//
//
//		tileInfo.tileImg->SetX(searchTileCell->GetPosition().x);
//		tileInfo.tileImg->SetY(searchTileCell->GetPosition().y);
//
//		tileAttackList.push_back(tileInfo);
//
//
//	}
//
//}

void Map::SetAttackRange(std::vector<TileInfo> _attackList)
{
	// 이미지 파일 어차피 없으니 
	tileAttackList.clear();

	tileAttackList = _attackList;
}

std::vector<Component*> Map::GetComponentList(TileCell* _tileCell)
{
	std::vector<Component*> componentArray;
	if (NULL == _tileCell)
	{
		return componentArray;
	}

	// 범위 체크 (맵 안에 있는지)
	if (_tileCell->GetTilePosition().x < 0 || width <= _tileCell->GetTilePosition().x ||
		_tileCell->GetTilePosition().y < 0 || height <= _tileCell->GetTilePosition().y)
	{
		return componentArray;
	}
	
	if (!FindTileCell(_tileCell->GetTilePosition())->GetCharacter())
	{
		return componentArray;
	}

	std::list<Component*> tileComponentList = FindTileCell(_tileCell->GetTilePosition())->GetTileComponentList();
	std::list<Component*>::iterator it;
	for (it= tileComponentList.begin(); it != tileComponentList.end(); it++)
	{
		componentArray.push_back((*it));
	}

	return componentArray;
}

void Map::ResetAttackList()
{
	tileAttackList.clear();
}

void Map::LayerBase()
{
	{
		//std::vector<std::string> recordList = RESOURCEMANAGER->FindScript(TEXT("MapData_Layer01"));
		std::queue<std::string> recordList = PARSING->GetTileMapLayerBase();
		char record[1000];
		char* token;
		std::string strRecord;

		for (int y = 0; y < height; y++)
		{
			strRecord = recordList.front();
			strcpy_s(record, strRecord.c_str());
			token = strtok(record, ",");

			std::vector<TileCell*> rowList;
			for (int x = 0; x < width; x++)
			{
				int spriteIndex = atoi(token);
				Image* image = imgTileList[spriteIndex].img;
				
				image->SetX(imgTileList[spriteIndex].destX);
				image->SetY(imgTileList[spriteIndex].destY);
				image->SetFrameX(imgTileList[spriteIndex].frameX);
				image->SetFrameY(imgTileList[spriteIndex].frameY);



				TileCell* tileCell = new TileCell();
				tileCell->Init(x, y);

				// 타일 오브젝트를 생성
				char name[256];
				//wsprintf(name, L"map_layer01_%d_%d", line, x);
				_stprintf(name, TEXT("map_layer01_Base_%d"), x);

				TileObject* tileObject = new TileObject(name, image, x, y, 0.1f);
				tileObject->SetFramePos(imgTileList[spriteIndex].frameX, imgTileList[spriteIndex].frameY);

				tileCell->AddComponent(tileObject);

				rowList.push_back(tileCell);

				token = strtok(NULL, ",");
			}
			tileArray.push_back(rowList);
			recordList.pop();
		}
	}
}

void Map::LayerTile()
{
		// Layer 2 
	{
		std::queue<std::string> recordList = PARSING->GetTileMapLayerTile();

		char record[1000];
		char* token;
		std::string strRecord;


		// 세번 째 라인 부터가 실제 맵 인덱스 데이타
		for (int y = 0; y < height; y++)
		{
			strRecord = recordList.front();
			strcpy_s(record, strRecord.c_str());
			token = strtok(record, ",");

			std::vector<TileCell*> rowList = tileArray[y];
			for (int x = 0; x < width; x++)
			{
				int spriteIndex = atoi(token);
				if (0 <= spriteIndex)
				{
					Image* sprite = imgTileList[spriteIndex].img;
					//sprite->SetX(imgObjectList[spriteIndex].destX);
					//sprite->SetY(imgObjectList[spriteIndex].destY);
					//sprite->SetFrameX(imgTileList[spriteIndex].frameX);
					//sprite->SetFrameY(imgTileList[spriteIndex].frameY);

					TileCell* tileCell = rowList[x];

					// 타일 오브젝트를 생성
					char name[256];
					_stprintf(name, TEXT("map_layer02_Tile_%d"), x);

					TileObject* tileObject = new TileObject(name, sprite, x, y , 0.2f);
					tileObject->SetFramePos(imgTileList[spriteIndex].frameX, imgTileList[spriteIndex].frameY);
					tileObject->SetCanMove(false);

					tileCell->AddComponent(tileObject);
				}

				token = strtok(NULL, ",");
			}
			tileArray.push_back(rowList);
			recordList.pop();
		}
	}
}

void Map::LayerObject()
{
	// Layer 3 
	{
		std::queue<std::string> recordList = PARSING->GetTileMapLayerObject();

		char record[1000];
		char* token;
		std::string strRecord;

		// 세번 째 라인 부터가 실제 맵 인덱스 데이타
		for (int y = 0; y < height; y++)
		{
			strRecord = recordList.front();
			strcpy_s(record, strRecord.c_str());
			token = strtok(record, ",");

			std::vector<TileCell*> rowList = tileArray[y];
			for (int x = 0; x < width; x++)
			{
				int spriteIndex = atoi(token);
				if (0 <= spriteIndex)
				{
					Image* sprite = imgObjectList[spriteIndex].img;


					TileCell* tileCell = rowList[x];

					// 타일 오브젝트를 생성
					char name[256];
					_stprintf(name, TEXT("map_layer03_obj_%d"), x);

					TileObject* tileObject = new TileObject(name, sprite, x, y, 0.2f);
					tileObject->SetFramePos(imgObjectList[spriteIndex].frameX, imgObjectList[spriteIndex].frameY);
					tileObject->SetCanMove(false);

					tileCell->AddComponent(tileObject);
				}

				token = strtok(NULL, ",");
			}
			tileArray.push_back(rowList);
			recordList.pop();
		}
	}
}

void Map::TileMapCreateSampleTile()
{
	{
		int srcX = 0;
		int srcY = 0;
		int destX = 0;
		int destY = 0;
		int spriteSize = 48;
		for (int j = 0; j < 307; j++)
		{
			for (int i = 0; i < 16; i++)
			{

				//Image* img = new Image();
				//img->Init(TEXT("../Resource/Images/TileMap_Cell_B.bmp"), 768, 14736, 16, 307, true, COLOR_M);

				//img->Init(TEXT("../Resource/Images/Outside_A2.bmp"), 768, 576, 16, 12, true, COLOR_M);
				Image* img = IMAGEMANAGER->FindImage("TileMap_Cell_B");
				//Image* imgObj = IMAGEMANAGER->FindImage("TileMap_OBJ_B");
				assert(img != NULL);

				img->SetFrameX(srcX);
				img->SetFrameY(srcY);
				img->SetX(destX);
				img->SetY(destY);


				imgTileInfo.img = img;
				imgTileInfo.frameX = srcX;
				imgTileInfo.frameY = srcY;
				imgTileInfo.destX = destX;
				imgTileInfo.destY = destY;

				imgTileList.push_back(imgTileInfo);
				//imgObjectList.push_back(imgObjectInfo);

				srcX++;
				destX += spriteSize;
			}
			destX = 0;
			srcX = 0;
			srcY++;
			destY += spriteSize;
		}
	}
}

void Map::TileMapCreateSampleObject()
{
	{
		int srcX = 0;
		int srcY = 0;
		int destX = 0;
		int destY = 0;
		int spriteSize = 48;
		for (int j = 0; j < 192; j++)
		{
			for (int i = 0; i < 16; i++)
			{
				Image* imgObj = IMAGEMANAGER->FindImage("TileMap_OBJ_B");
				assert(imgObj != NULL);

				//
				imgObj->SetFrameX(srcX);
				imgObj->SetFrameY(srcY);
				imgObj->SetX(destX);
				imgObj->SetY(destY);

				imgObjectInfo.img = imgObj;
				imgObjectInfo.frameX = srcX;
				imgObjectInfo.frameY = srcY;
				imgObjectInfo.destX = destX;
				imgObjectInfo.destY = destY;

				imgObjectList.push_back(imgObjectInfo);

				srcX++;
				destX += spriteSize;
			}
			destX = 0;
			srcX = 0;
			srcY++;
			destY += spriteSize;
		}
	}
}

void Map::MapSearchClear()
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			tileArray[i][j]->SetSearchPathfinding(false);
		}
	}
}
