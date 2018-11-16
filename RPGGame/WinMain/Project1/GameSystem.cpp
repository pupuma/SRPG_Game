#include "Game.h"
#include "GameSystem.h"


GameSystem::GameSystem()
{
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