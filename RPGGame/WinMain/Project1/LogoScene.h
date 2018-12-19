#pragma once
class LogoScene
	: public GameNode
{
public:
	LogoScene();
	~LogoScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

