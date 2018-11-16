#pragma once
//#include "Game.h"
#include <Windows.h>

// RECT ~~MakeCenter : Pivot 설정 

inline POINT PointMake(int x, int y)
{
	POINT pt = { x,  y };
	return pt;
}

inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

// 함수를 사용할 때 함수를 호출 할때 비용(진행하고 있는 내용을 저장하고 , 함수 호출을 위해서 스텍에 할당)이 들어가는데 
// 함수 호출 비용을 줄이기 위해 사용, 컴파일러가 판단하에 사용된다. (사용안될 수도 있다.) 

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x , y , x + width , y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2) , y - (height / 2), x + (width / 2), y + (height / 2) };
	return rc;
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}


inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}



inline void DrawObject(HDC hdc, const RECT& rc, int size, const COLORREF penColor, const COLORREF brColor, const OBJ_TYPE nType, const int ropCode = R2_XORPEN)
{
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	//Restoperation : 이미지위에 이미지가 있으면 어떻게 처리하겠는가..
	//SetROP2(hdc, ropCode);

	hPen = CreatePen(PS_SOLID, size, penColor);
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(brColor);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	switch (nType)
	{
	case ELLIPSE:
		Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
		break;
	case RECTANGLE:
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		break;
	}

	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}


inline void DrawObject(HDC hdc, const RECT& rc, int size, const COLORREF color, const OBJ_TYPE nType, const int ropCode = R2_XORPEN)
{
	DrawObject(hdc, rc, size, color, color, nType, ropCode);
}

inline void DrawLine(HDC hdc, const POINT& pt1, const POINT& pt2, int size, const COLORREF color)
{
	HPEN hPen, hOldPen;

	hPen = CreatePen(PS_SOLID, size, color);
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, pt1.x, pt1.y, NULL);
	LineTo(hdc, pt2.x, pt2.y);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

//
//inline bool CollisionRectAndRect(const RECT& _rc1, const RECT& _rc2)
//{
//	if (_rc1.left <= _rc2.right && _rc1.right >= _rc2.left)
//	{
//		if (_rc1.top <= _rc2.bottom && _rc1.bottom >= _rc2.top)
//		{
//			// 충돌 이후 처리에 대한 로직이 들어가도록.. 
//			return true;
//		}
//	}
//	return false;
//}
