#pragma once

// 사용자 정의 자료형



enum TERRAIN
{
	TR_CEMENT,
	TR_GROUND,
	TR_GRASS,
	TR_WATER,
	TR_END,
};

enum OBJ_TYPE
{
	ELLIPSE = 0,
	RECTANGLE,
};

enum DS_STATE
{
	DS_LEFT = -1,
	DS_NONE,
	DS_RIGHT,
};


//
struct SPERE
{
	float x, y;
	float r;
};


struct Tile
{
	TERRAIN		terrain;
	RECT		rc;
	int			frameX;
	int			frameY;
};


//
typedef struct _Point
{
	float x;
	float y;
} Point;


//
typedef struct _TilePoint
{
	int x;
	int y;
} TilePoint;

//
enum eDirection
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	DIR_NONE,
};


// 사용자 정의 타입
//typedef void(*CALL_FUNC)();
//typedef void(*CALL_FUNC_PARAM)(void*);

// Extern
extern HWND			_hWnd;
extern HINSTANCE	_hInst;
extern POINT		_ptMouse;

extern HWND			_hWndAvi;

#if defined(_MOVE_TEST)

# endif //

