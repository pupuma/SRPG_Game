#pragma once
#include "SingletonBase.h"

typedef std::map<std::string, HFONT> MFONT;


class FontManager
	: public SingletonBase<FontManager>
{
private:
	MFONT				fontMap;
	MFONT::iterator		it_Font;
	std::string temp;
	int iNumber;
	std::string str;
	Image* img;
public:
	FontManager();
	~FontManager();
public:
	void Init();
	void RenderText(HDC hdc, const std::string fontName, const std::string strText, POINT* pos, COLORREF color);
	void RenderTextBox(HDC hdc, const std::string fontName, const std::string strText, RECT* rc, COLORREF color);
	void RenderTextBox(HDC hdc, const std::string fontName, int size , const std::string strText, RECT* rc, COLORREF color);
	void TextGaugeRender(HDC hdc, int iHp, RECT * rc, COLORREF color);
	void TextGaugeRender(HDC hdc, int _gauge,int _maxGauge, RECT* rc, COLORREF color);

	void SetNumber(int num);
	void RenderNumber(HDC hdc, int destX, int destY);
};

