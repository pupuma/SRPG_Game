#pragma once
#include "GameNode.h"


class MainGame : public GameNode
{
private:
	Image* backGround;
public:
	MainGame();
	~MainGame();

	//========================================

	//========================================

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

};

