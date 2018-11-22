#pragma once

#include "SingletonBase.h"


class GameSystem
	: public SingletonBase<GameSystem>
{
private:
	//std::list<TileInfo> moveTileList;
public:
	GameSystem();
	~GameSystem();
public:
	void SetMousePosition(LPARAM lParam);
	POINT GetMousePosition();
public:
	//void SetMoveTileList(std::list<TileInfo> _moveTileList);
	//std::list<TileInfo> GetMoveTileList();

};

