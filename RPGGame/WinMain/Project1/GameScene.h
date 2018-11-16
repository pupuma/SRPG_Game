#pragma once

#include "MainGame.h"

class RenderTest;
class ImageCropTest;
class FrameRenderTest;
class TrigonometricTest;
class StalkerTest;
class GameScene
	: public MainGame
{
private:
#if defined(_RENDER_TEST)
	RenderTest * renderTest;
#elif defined(_CROP_TEST)
	ImageCropTest * imageCropTest;
#elif defined(_FRAME_TEST)
	FrameRenderTest* frameTest;
#elif defined(_TRIFUNC_TEST)
	TrigonometricTest* triFuncTest;
#elif defined(_STALKER_TEST)
	StalkerTest* _stalkerTest;
#else
#endif
	RECT _rcClient;
	//Image* _loopBackGround;
	//Image* _obj;
	//int iOffset;

public:
	GameScene();
	~GameScene();

public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};