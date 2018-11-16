#pragma once

//#define PI 3.141592654f
//#define PI2 PI*2

namespace UTIL
{
	//float GetDistance(float startX, float startY, float endX, float endY);
	float GetDistance(const float startX, const float startY, const float endX, const float endY);

	float GetAngle(const float x1, const float y1, const float x2, const float y2);
}