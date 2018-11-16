#include "Game.h"
#include "Map.h"



Map::Map(std::string _name)
	: Component(_name)
{
}


Map::~Map()
{
}

bool Map::Init()
{
	return true;
}

void Map::Deinit()
{
}

void Map::Update()
{
}

void Map::Render(HDC hdc)
{
}

void Map::Release()
{
}

void Map::Reset()
{
}
