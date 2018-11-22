#pragma once

class TileCell;

#define TILEWIDTH 16
#define TILEHEIGHT 12

class Map
	: public Component
{
private:
	//
#if defined(_DEBUG_TEST)
	int mouseTargetX;
	int mouseTargetY;

#endif //
	//
	int width;
	int height;

	int tileSize;
	int renderWidth;
	int renderHeight;
private:
	Image* img;
	Image* mousePosImg;
	TileInfo tileInfo;
	RECT rc;
	RECT rect;
	std::vector<RECT> rectList;
private:
	std::vector<std::vector<TileCell*>> tileArray;
	std::vector<Image*> imgList;
	std::list<TileInfo> moveTileList;
	
	std::list<TileInfo> tileCellOpenList;
	std::priority_queue<TileCell*> pathfindingQueue;

private:
	Component* viewer;
	TilePoint prevViewTilePosition;
	TilePoint targetStartPosition;
	TileCell* targetTileCell;
public:
	Map(std::string _name);
	~Map();
public:
	bool Init();
	void Deinit();
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
public:
	void CreateTileMap();
	void SetTileComponent(TilePoint tilePosition, Component* component);
	void ResetTileComponent(TilePoint tilePosition, Component* component);
public:
	void SetViewer(Component* _com);
	void UpdateViewer();
public:
	TileCell* FindTileCell(TilePoint _searchTilePosision);

	//
	void MaxTravelDistance(Component* _target);
	void MaxTravelDistanceRender(HDC hdc);
	void MaxPathFinder(int _distance, TilePoint _pos);
	TilePoint GetSearchTilePositionByDirection(TilePoint tilePosition, eDirection direction);
	TileCell* FindTileCellByMousePosition(int _mouseX, int _mouseY);

public:
	//bool operator==(const TilePoint &a, const TilePoint &b)
	//{
	//	if (a.x == b.y && a.y == b.y)
	//	{
	//		return true;
	//	}
	//	return false;
	//}

public:
	std::vector<std::vector<TileCell*>> GetTileArray() { return tileArray; }
};

