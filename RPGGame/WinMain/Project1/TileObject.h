#pragma once
class TileObject
	: public Component
{
private:
	Image* image;
	int tileX;
	int tileY;
public:
	TileObject(std::string _name, Image* _image, int _tileX, int _tileY);
	~TileObject();
public:
	bool Init();
	void Deinit();
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
};

