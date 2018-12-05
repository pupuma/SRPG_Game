#pragma once
class TileObject
	: public Component
{
private:
	Image* image;
	int tileX;
	int tileY;

	int frameX;
	int frameY;
public:
	TileObject(std::string _name, Image* _image, int _tileX, int _tileY, float _deep);
	~TileObject();
public:
	bool Init();
	void Deinit();
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
public:
	void SetFramePos(int _frameX, int _frameY);
};

