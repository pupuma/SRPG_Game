#include "Game.h"
#include "CollisionFunction.h"
#include "Image.h"

bool CollisionRectAndRect(const RECT& r1, const RECT& r2)
{
	if (r1.left <= r2.right && r1.right >= r2.left)
	{
		if (r1.top <= r2.bottom && r1.bottom >= r2.top)
		{
			return true;
		}
	}

	return false;
}

bool CollisionCircleAndCircle(const float r1, const float x1, const float y1, const float r2, const float x2, const float y2)
{
	if (r1 + r2 >= UTIL::GetDistance(x1, y1, x2, y2))
		return true;

	return false;
}
int CollisionPixelAndRect(Image * _mountain, int _x, int _y, COLORREF _colorKey)
{
	return 0;
}
//
//int CollisionPixelAndRect(const Image* _image ,const RECT& rc, int _probY)
//{
//	_probY = _y + _ball->GetHeight() / 2;
//
//
//	for (int i = _probY - 100; i < _probY + 100; ++i)
//	{
//		COLORREF color = GetPixel(_mountain->GetMemDC(), _x, i);
//		int r = GetRValue(color);
//		int g = GetGValue(color);
//		int b = GetBValue(color);
//
//		if (!(r == 255 && g == 0 && b == 255))
//		{
//			_y = i - _ball->GetHeight() / 2;
//			break;
//		}
//	}
//
//	return _y;
//}
