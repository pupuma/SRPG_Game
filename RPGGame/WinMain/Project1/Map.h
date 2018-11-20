#pragma once

class TileCell;
//class Viewer;
#define TILEWIDTH 16
#define TILEHEIGHT 12

class Map
	: public Component
{
private:
	int width;
	int height;

	int tileSize;
	int renderWidth;
	int renderHeight;
private:
	Image* img;
	//Viewer* viewer;
private:
	std::vector<std::vector<TileCell*>> tileArray;
	std::vector<Image*> imgList;
private:
	Component* viewer;
	TilePoint prevViewTilePosition;
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
	std::vector<std::vector<TileCell*>> GetTileArray() { return tileArray; }
};

