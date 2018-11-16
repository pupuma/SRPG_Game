#pragma once
class TileObject
	: public Component
{
public:
	TileObject(std::string _name);
	~TileObject();
public:
	bool Init();
	void Deinit();
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
};

