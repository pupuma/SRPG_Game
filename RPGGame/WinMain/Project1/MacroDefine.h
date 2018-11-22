#pragma once

// ����� ���� ���� ���� 
//#define _RENDER_TEST
//#define _CROP_TEST
//#define _FRAME_TEST
//#define _TRIFUNC_TEST
//#define _STALKER_TEST
//#define _ANI_TEST
//#define _CAMERA_TEST
//#define _PIXEL_TEST
//#define _EFFECT_TEST
//#define _MOVE_TEST
//#define _MAPTOOL_TEST
#define _DEBUG_TEST


#if defined(_UNICODE)
typedef  std::wstring		tstring;  //std::basic_string<wchar>
#else	
typedef  std::string		tstring;   //std::basic_string<char>
#endif // #if defined(_UNICODE)



//
#define PI				3.141592654f
#define PI2				PI*2
#define COLOR_M			RGB(255,0,255)


// �޸� ���� ��ũ��
#define SAFE_DELETE(p)	{if(p) {delete (p); (p) = NULL;}}
#define SAFE_RELEASE(p)	{if(p) {(p)->Release(); (p) = NULL;}}

// ������ ������ ���� ��ũ��
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define WINSIZEX	1000
#define WINSIZEY	800
#define WINSTARTX	100
#define WINSTARTY	100

// MAPTOOL or Tile���� ��ũ�� 
#define TILESIZE		32

#define TILEX			20
#define TILEY			20

#define TILESIZEX		TILESIZE * TILEX
#define TILESIZEY		TILESIZE * TILEY

#define SAMPLETILEX		20
#define SAMPLETILEY		9



// �̱��� ��ü ��ũ��

#define RAND			RandomFunction::GetSingleton()
#define CAMERA			Camera::GetSingleton()
#define KEYMANAGER		KeyManager::GetSingleton()
#define TIMEMANAGER		TimeManager::GetSingleton()
#define IMAGEMANAGER	ImageManager::GetSingleton()
#define EFFECTMANAGER	EffectManager::GetSingleton()
#define SCENEMANAGER	SceneManager::GetSingleton()
#define SOUNDMANAGER	SoundManager::GetSingleton()
#define TEXTDATA		TextData::GetSingleton()
#define ANIMANAGER		AnimationManager::GetSingleton()
#define COMSYS			ComponentSystem::GetInstance()
#define	RESOURCEMANAGER	ResourceManager::GetSingleton()
#define GAMESYS			GameSystem::GetSingleton()