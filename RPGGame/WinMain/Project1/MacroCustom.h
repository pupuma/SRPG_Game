#pragma once


// ����� ���� ���� ����
//#define _RENDER_TEST
//#define _CROP_TEST
//#define _FRAME_TEST
//#define _TRIFUNC_TEST
#define _STALKER_TEST

// �޸� ���� ��ũ��
#define SAFE_DELETE(p) { if(p) {delete (p); (p) = NULL;}}
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = NULL;}}

// Macro

#define		WINSTARX		100
#define		WINSTARY		100
#define		WINSIZEX		1200
#define		WINSIZEY		600


//
#define PI 3.141592f
#define PI2 PI*2

//
#define RAND			RandomFuction::GetSingleton()
#define KEYMANAGER		KeyManager::GetSingleton()
