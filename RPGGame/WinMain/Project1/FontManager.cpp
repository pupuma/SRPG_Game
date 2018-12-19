#include "Game.h"
#include "FontManager.h"

FontManager::FontManager()
{
	//font
	{
	
		/*fontMap.insert({ TEXT("AdobeSS"), font });

		font = CreateFont(15, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
			OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Adobe Caslon Pro Bold"));
		fontMap.insert({ TEXT("AdobeS"), font });

		font = CreateFont(20, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
			OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Adobe Caslon Pro Bold"));
		fontMap.insert({ TEXT("AdobeB"), font });

		font = CreateFont(30, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
			OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Adobe Caslon Pro Bold"));
		fontMap.insert({ TEXT("AdobeBB"), font });

		font = CreateFont(12, 0, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET,
			OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Adobe Caslon Pro Bold"));
		fontMap.insert({ TEXT("AdobeSB"), font });
*/

	}
}


FontManager::~FontManager()
{
}



void FontManager::Init()
{
	AddFontResource(TEXT("../Resource/Text/NanumBarunGothic.ttf"));
	HFONT font = CreateFont(30, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("NanumBarunGothic"));
	
	fontMap.insert({ TEXT("NBG"), font });

	font = CreateFont(15, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("NanumBarunGothic"));
	fontMap.insert({ TEXT("NBG_S"), font });


}

void FontManager::RenderText(HDC hdc, const std::string fontName, const std::string strText, POINT* pos, COLORREF color)
{

	//SetBkMode(hdc, TRANSPARENT);

	TCHAR szStr[256] = { 0, };
	HFONT oldFont;

	it_Font = fontMap.find(fontName);
	if (it_Font != fontMap.end())
	{
		HFONT font = (HFONT)(it_Font->second);
		oldFont = (HFONT)SelectObject(hdc, font);
		COLORREF oldColor = SetTextColor(hdc, color);



		TextOut(hdc, pos->x, pos->y, strText.c_str(), strText.size());

		SelectObject(hdc, oldFont);
		SetTextColor(hdc, oldColor);
	
	}
}

void FontManager::RenderTextBox(HDC hdc, const std::string fontName, const std::string strText, RECT * rc, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szStr[256] = { 0, };
	HFONT oldFont;

	it_Font = fontMap.find(fontName);
	if (it_Font != fontMap.end())
	{
		HFONT font = (HFONT)(it_Font->second);
		oldFont = (HFONT)SelectObject(hdc, font);
		COLORREF oldColor = SetTextColor(hdc, color);

		//DrawText(hdc, vString.c_str(), _tcslen(vString.c_str()), &rcText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		DrawText(hdc, strText.c_str(), strText.size(), rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		//TextOut(hdc, pos->x, pos->y, strText.c_str(), strText.size());

		SelectObject(hdc, oldFont);
		SetTextColor(hdc, oldColor);

	}
}

void FontManager::TextHpRender(HDC hdc, int iHp, RECT * rc, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szStr[256] = { 0, };
	HFONT oldFont;

	//std::string fontName;
	//if (iHp >= 1000 && iHp < 100000)
	//{
	//	fontName = TEXT("AdobeSS");

	//}
	//else if (iHp > 100 && iHp < 1000)
	//{
	//	fontName = TEXT("AdobeS");

	//}
	//else
	//{
	//	fontName = TEXT("AdobeB");
	//}

	/*it_Font = fontMap.find(fontName);

	if (it_Font != fontMap.end())
	{
		HFONT font = (HFONT)(it_Font->second);
		oldFont = (HFONT)SelectObject(hdc, font);
		COLORREF oldColor = SetTextColor(hdc, color);

		TCHAR strHp[256];
		_stprintf(strHp, TEXT("%d"), iHp);

		DrawText(hdc, strHp, _tcslen(strHp), rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);


		SelectObject(hdc, oldFont);
		SetTextColor(hdc, oldColor);
	}*/
}

