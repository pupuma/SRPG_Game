#pragma once

class TileCell;
class Animation;


#define TILEWIDTH 33
#define TILEHEIGHT 33

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

	bool isSelectMove;
	POINT pt;
private:
	Image* img;
	Image* mousePosImg;
	Image* mouseMovePosImg;
	Animation* mouseMovePosAni;

	TileInfo tileInfo;
	RECT rc;
	RECT rect;
	std::vector<RECT> rectList;
private:
	std::vector<std::vector<TileCell*>> tileArray;
	std::vector<Image*> imgList;
	//std::list<TileInfo> moveTileList;
	
	std::list<TileInfo> tileCellOpenList;
	std::vector<TileInfo> tileAttackList;
	
	std::queue<TileCell*> pathfindingQueue;

	//std::priority_queue<TileCell*> pathfindingQueue;
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
	void ResetPahtfinding();
	void SortTile();
	void ResetViewer();
	void ReleaseOpenList();
	std::vector<Component*> SetAttackRange();
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
	std::list<TileInfo> GetOpenTileCellList() { return tileCellOpenList; }

};

