#include "Game.h"
#include "GameSystem.h"

#include "Map.h"
#include "TileCell.h"

GameSystem::GameSystem()
{
	isAction = false;
	isAttacking = false;
}


GameSystem::~GameSystem()
{
}

void GameSystem::SetMousePosition(LPARAM lParam)
{
	_ptMouse.x = LOWORD(lParam);
	_ptMouse.y = HIWORD(lParam);
}


POINT GameSystem::GetMousePosition()
{
	return _ptMouse;
}
void GameSystem::ResetTarget()
{
	g_Map->ResetViewer();
}
void GameSystem::SetMap(Map * _map)
{
	g_Map = _map;
}
bool GameSystem::TargetCheck(std::vector<Component*> _list)
{
	std::vector<TileInfo> tileAttackList = g_Map->GetAttackList();
	for (auto a : _list)
	{
	
		for (auto b : tileAttackList)
		{
			temp = b.tile->GetTilePosition();
			if (temp == a->GetTilePosition())
			{
				return true;
			}
		}
	}


	return false;
}
//
//void GameSystem::SetMoveTileList(std::list<TileInfo> _moveTileList)
//{
//	this->moveTileList = _moveTileList;
//}
//
//std::list<TileInfo> GameSystem::GetMoveTileList()
//{
//	return this->moveTileList;
//}
