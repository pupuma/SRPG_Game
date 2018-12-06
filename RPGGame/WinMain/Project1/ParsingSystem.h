#pragma once
class ParsingSystem
	: public SingletonBase<ParsingSystem>
{
private:
	int tileWidth;
	int tileHeight;

	int layerSize;
private:
	std::queue<std::string> q_TileMapLayerBase;
	std::queue<std::string> q_TileMapLayerTile;
	std::queue<std::string> q_TileMapLayerObject;

public:
	ParsingSystem();
	~ParsingSystem();
public:
	void MapDataParsing(std::string _fileName);
public:
	std::queue<std::string> GetTileMapLayerBase() { return q_TileMapLayerBase; }
	std::queue<std::string> GetTileMapLayerTile() { return q_TileMapLayerTile; }
	std::queue<std::string> GetTileMapLayerObject() { return q_TileMapLayerObject; }
	int GetTileWidth() { return tileWidth; }
	int GetTIleHeight() { return tileHeight; }
	int GetLayerSize() { return layerSize; }

};

