#include "Game.h"
#include "GameSystem.h"

#include "Map.h"
#include "TileCell.h"
#include "Character.h"

GameSystem::GameSystem()
{
	isAction = false;
	isAttacking = false;
	round = 1;
	currentCharacterIndex = 0;
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
bool GameSystem::TargetCheck(std::vector<Component*> _list, Character* _character)
{
	// AttackRange
	std::vector<TileInfo> tileAttackList = g_Map->GetAttackList();

	// 리스트 안에 플레이어가 있으면 안된다. 
	eComponentType characterType = _character->GetComponetType();
	for (auto a : _list)
	{
		eComponentType type = a->GetComponetType();
		if (type == characterType)
		{
			return false;
		}
	}

	// target 
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
void GameSystem::AddCharacterList(Character * _character)
{
	characterList.push_back(_character);
}
void GameSystem::GameTurn()
{
	/*unsigned int characterSize = characterList.size();

	characterList[currentCharacterIndex]->SetTurn(true);
	currentCharacterIndex++;
	round++;

	if (currentCharacterIndex >= characterSize)
	{
		currentCharacterIndex = 0;
	}*/

	characterList[0]->SetTurn(true);
	characterList[1]->SetTurn(false);

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(TEXT("Map"));
	g_Map->ResetViewer();
	g_Map->SetViewer((Component*)characterList[0]);


}
eDirection GameSystem::LookAtCharacter(std::vector<Component*> _list, Character* _character)
{
	eDirection dir =  eDirection::DIR_LEFT;
	std::vector<Component*>::iterator it = _list.begin();

	if ((*it)->GetTilePosition().x < _character->GetTilePosition().x)
	{
		dir = eDirection::DIR_LEFT;
	}
	else if ((*it)->GetTilePosition().x > _character->GetTilePosition().x)
	{
		dir = eDirection::DIR_RIGHT;
	}


	if ((*it)->GetTilePosition().y < _character->GetTilePosition().y)
	{
		dir = eDirection::DIR_DOWN;
	}

	if ((*it)->GetTilePosition().y < _character->GetTilePosition().y)
	{
		dir = eDirection::DIR_UP;
	}
	return dir;
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
