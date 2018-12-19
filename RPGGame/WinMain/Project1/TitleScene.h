#pragma once
class TitleScene
	: public GameNode
{
public:
	TitleScene();
	~TitleScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

