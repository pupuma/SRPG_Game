#pragma once

class TileCell;
class Animation;

//#define TILEWIDTH 33
//#define TILEHEIGHT 33

class Map
	: public Component
{
private:

	ImgInfo imgTileInfo;
	ImgInfo imgObjectInfo;
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
	//std::vector<Image*> imgList;
	std::vector<ImgInfo> imgTileList;
	std::vector<ImgInfo> imgObjectList;

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
	void SetTileComponent(TilePoint tilePosition, Component* component,bool _isCharacter);

	void ResetTileComponent(TilePoint tilePosition, Component* component);
public:
	void SetViewer(Component* _com);
	void UpdateViewer();
	void OpenListClear();
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
	void SetAttackRange();
	void SetAttackRange(std::vector<TileInfo> _attackList);

	std::vector<Component*> GetComponentList(TileCell* _tileCell);
	void ResetAttackList();
	
public:
	void LayerBase();
	void LayerTile();
	void LayerObject();
	void TileMapCreateSampleTile();
	void TileMapCreateSampleObject();
	void MapSearchClear();
	
public:
	//bool operator==(const TilePoint &a)
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
	std::vector<TileInfo> GetAttackList() { return tileAttackList; }

	int GetWidth() const { return width; }	
	int GetHeight() const { return height; }
};

