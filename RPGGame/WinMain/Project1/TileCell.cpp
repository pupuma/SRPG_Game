#include "Game.h"
#include "TileCell.h"



TileCell::TileCell()
{
	position = { 0,0 };
	pathfindingSearch = false;
	isCharacter = false;
	//deep = 0.0f;
}


TileCell::~TileCell()
{

}

bool TileCell::Init(int _tileX, int _tileY)
{
	tilePosition.x = _tileX;
	tilePosition.y = _tileY;

	
	return true;
}

void TileCell::Update()
{
}

void TileCell::Render(HDC hdc)
{
	std::list<Component*>::iterator it;

	// ±íÀÌ Á¤·Ä

	//
	for (it = componentList.begin(); it != componentList.end(); it++)
	{
		(*it)->SetPosition(position);
		(*it)->Render(hdc);
	}

	// Line

	int iCameraX = CAMERA->GetPosition()->x;
	int iCameraY = CAMERA->GetPosition()->y;

	int iTileCellSize = 48;
	LineMake(hdc, position.x - iCameraX, position.y - iCameraY, (position.x + iTileCellSize) - iCameraX, (position.y) - iCameraY);
	LineMake(hdc, position.x - iCameraX, position.y - iCameraY, (position.x ) - iCameraX, (position.y + iTileCellSize) - iCameraY);
	LineMake(hdc, (position.x + iTileCellSize) - iCameraX, (position.y + iTileCellSize) - iCameraY, (position.x + iTileCellSize) - iCameraX, (position.y) - iCameraY);
	LineMake(hdc, position.x - iCameraX, (position.y +iTileCellSize)- iCameraY, (position.x + iTileCellSize) - iCameraX, (position.y + iTileCellSize) - iCameraY);


}

void TileCell::Release()
{
}

void TileCell::Reset()
{
}

void TileCell::AddComponent(Component * _component)
{
	componentList.push_back(_component);
	//swapComList.push_back(_component);
}

void TileCell::RemoveComponent(Component * _component)
{
	componentList.remove(_component);

}

void TileCell::ResetPathfinding()
{
	{
		pathfindingSearch = false;
		prevTileCell = NULL;
		distanceFromStart = 0.0f;
	}

}

void TileCell::DeepSort()
{
	//std::sort(componentList.begin(), componentList.end());
	/*Component* temp;
	for (size_t i = 0; i < swapComList.size(); i++)
	{
		for (size_t j = 0; j < swapComList.size() - (i + 1); j++)
		{
			if (swapComList[j]->GetDeep() > swapComList[j + 1]->GetDeep())
			{
				temp = swapComList[j + 1];
				swapComList[j + 1] = swapComList[j];
				swapComList[j] = temp;
			}
		}
	}

	for (size_t i = 0; i < swapComList.size(); i++)
	{
		componentList.push_back(swapComList[i]);
	}*/

}

bool TileCell::CanMove()
{
	std::list<Component*>::iterator it;
	for (it = componentList.begin(); it != componentList.end();it++)
	{
		if (false == (*it)->CanMove())
		{
			return false;
		}
	}
	return true;
}

void TileCell::IsCharacter(bool _isCharacter)
{
	isCharacter = _isCharacter;
}

