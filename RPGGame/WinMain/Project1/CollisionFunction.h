#pragma once
class Image;

bool CollisionRectAndRect(const RECT& r1, const RECT& r2);

bool CollisionCircleAndCircle(const float r1, const float x1, const float y1, const float r2, const float x2, const float y2);

//int CollisionPixelAndRect(const Image* _image, const RECT& rc, int _probY);

int CollisionPixelAndRect(Image* _mountain, int  _x, int  _y, COLORREF _colorKey);


