#pragma once
//#include "Game.h"
#include <Windows.h>

// RECT ~~MakeCenter : Pivot ���� 

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

// �Լ��� ����� �� �Լ��� ȣ�� �Ҷ� ���(�����ϰ� �ִ� ������ �����ϰ� , �Լ� ȣ���� ���ؼ� ���ؿ� �Ҵ�)�� ���µ� 
// �Լ� ȣ�� ����� ���̱� ���� ���, �����Ϸ��� �Ǵ��Ͽ� ���ȴ�. (���ȵ� ���� �ִ�.) 

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

	//Restoperation : �̹������� �̹����� ������ ��� ó���ϰڴ°�..
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
//			// �浹 ���� ó���� ���� ������ ������.. 
//			return true;
//		}
//	}
//	return false;
//}
