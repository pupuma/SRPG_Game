#pragma once
#include "SingletonBase.h"

typedef std::map<std::string, HFONT> MFONT;


class FontManager
	: public SingletonBase<FontManager>
{
private:
	MFONT				fontMap;
	MFONT::iterator		it_Font;
public:
	FontManager();
	~FontManager();
public:
	void Init();
	void RenderText(HDC hdc, const std::string fontName, const std::string strText, POINT* pos, COLORREF color);
	void RenderTextBox(HDC hdc, const std::string fontName, const std::string strText, RECT* rc, COLORREF color);

	void TextHpRender(HDC hdc, int iHp, RECT * rc, COLORREF color);

};

