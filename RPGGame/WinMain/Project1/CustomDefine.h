#pragma once

// ����� ���� �ڷ���



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



// ����� ���� Ÿ��
//typedef void(*CALL_FUNC)();
//typedef void(*CALL_FUNC_PARAM)(void*);

// Extern
extern HWND			_hWnd;
extern HINSTANCE	_hInst;
extern POINT		_ptMouse;

extern HWND			_hWndAvi;

#if defined(_MOVE_TEST)

# endif //

