#pragma once
class TitleScene
	: public GameNode
{
private:
	Image* img;
	POINT ptTitle;
	POINT ptStart;
	RECT rcBox;
	Image* imgBox;
	BYTE colorKey;
	int dex;
public:
	TitleScene();
	~TitleScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

