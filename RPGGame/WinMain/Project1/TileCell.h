#pragma once
class TileCell
{
private:
	POINT position;
	POINT tilePostion;

private:
	std::list<Component*> componentList;
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
public:
	void SetPosition(POINT _pos) { position = _pos; }
	POINT GetPosition() { return position; }
};

