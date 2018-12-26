#pragma once

class EndScene
	: public GameNode

{
private:
	Image* bg;
public:
	EndScene();
	~EndScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

