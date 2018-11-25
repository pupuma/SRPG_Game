#pragma once

class Componet;

class TileCell
{
private:
	POINT position;
	TilePoint tilePostion;
private:
	bool pathfindingSearch;
	TileCell* prevTileCell;
	float distanceFromStart;
private:
	std::list<Component*> componentList;
	std::vector<Component*> swapComList;
public:
	TileCell();
	~TileCell();

public:
	bool Init(int _tileX, int _tileY);
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
public:
	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);
	void ResetPathfinding();
	void DeepSort();
	bool CanMove();

public:
	void SetPosition(POINT _pos) { position = _pos; }
	POINT GetPosition() { return position; }
	TilePoint GetTilePosition() { return tilePostion; }

	bool IsSearchPathfinding() { return pathfindingSearch; }
	void SetSearchPathfinding(bool _search) { pathfindingSearch = _search; }

	void SearchPathfind() { pathfindingSearch = true; }
	TileCell* GetPrevTileCell() { return prevTileCell; }
	void SetPrevTileCell(TileCell* _tileCell) { prevTileCell = _tileCell; }

	float GetDistanceFromStart() { return distanceFromStart; }
	void SetDistanceFromStart(float _distanceFromStart) { distanceFromStart = _distanceFromStart; }

	
};

