#pragma once
class TileCell
{
private:
	POINT position;
private:
	std::list<Component*> componentList;
public:
	TileCell();
	~TileCell();

public:
	bool Init(int _tileX, int _tileY);
	void Update();
	void Render();

	void Release();
	void Reset();
public:
	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);
public:
	
};

