#include "Game.h"
#include "Map.h"
#include "TileCell.h"
#include "TileObject.h"

//#include "Viewer.h"
Map::Map(std::string _name)
	: Component(_name)
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
	return true;
}

void Map::Deinit()
{
}

void Map::Update()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			tileArray[y][x]->Update();
		}
	}
	//viewer->Update();
	UpdateViewer();
}

void Map::Render(HDC hdc)
{
	//img->Render(hdc);
	{
		int midTileCountX = renderWidth / 2;
		int midTileCountY = renderHeight / 2;

		int startTileX = viewer->GetTilePosition().x - midTileCountX - 1;
		int startTileY = viewer->GetTilePosition().y - midTileCountY - 1;

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
					}
					renderPos.x += tileSize;
				}
			}
			renderPos.x = 0.0f;
			renderPos.y += tileSize;
		}
	}

	{

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
		int tileSize = 48;
		int renderWidth = 32;
		int renderHeight = 32;
		for (int i = 0; i <= 32; i++)
		{
			LineMake(hdc, i * tileSize + tileArray[0][0]->GetPosition().x,
				tileArray[0][0]->GetPosition().y,
				i * tileSize + +tileArray[0][0]->GetPosition().x,
				renderWidth * tileSize + +tileArray[0][0]->GetPosition().y);
		}
		for (int i = 0; i <=  32; i++)
		{
			LineMake(hdc, tileArray[0][0]->GetPosition().x, i * tileSize + tileArray[0][0]->GetPosition().y,
				renderHeight * tileSize + tileArray[0][0]->GetPosition().x, i * tileSize + tileArray[0][0]->GetPosition().y);
		}
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
		token = strtok(record, ",");		// 첫번 째 칸은 스킵 : mapsize
		token = strtok(NULL, ",");			// 두번 째 실제 가로 크기 : 16
		width = atoi(token);
		token = strtok(NULL, ",");			// 세번 째 실제 세로 크기 : 10
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

				// 타일 오브젝트를 생성
				char name[256];
				//wsprintf(name, L"map_layer01_%d_%d", line, x);
				_stprintf(name, TEXT("map_layer01_%d_%d"), line, x);

				TileObject* tileObject = new TileObject(name, image, x, y);
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

		// 첫 째 라인은 맵 크기 정보
		strcpy_s(record, recordList[0].c_str());
		token = strtok(record, ",");		// 첫번 째 칸은 스킵 : mapsize
		token = strtok(NULL, ",");			// 두번 째 실제 가로 크기 : 16
		width = atoi(token);
		token = strtok(NULL, ",");			// 세번 째 실제 세로 크기 : 10
		height = atoi(token);

		// 둘 째 라인은 스킵

		// 세번 째 라인 부터가 실제 맵 인덱스 데이타
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

					// 타일 오브젝트를 생성
					char name[256];
					_stprintf(name, TEXT("map_layer02_%d_%d"), line, x);

					TileObject* tileObject = new TileObject(name, sprite, x, y);
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
	prevViewTilePosition = viewer->GetTilePosition();
}

void Map::UpdateViewer()
{
	if (NULL == viewer)
	{
		return;
	}

	
}
