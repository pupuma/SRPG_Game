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
	AddFontResource(TEXT("../Resource/Text/NanumBarunGothicBold.ttf"));

	HFONT font = CreateFont(30, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET | HANGEUL_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("³ª´®¹Ù¸¥°íµñ"));
	
	fontMap.insert({ TEXT("NBG"), font });

	font = CreateFont(15, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("³ª´®¹Ù¸¥°íµñ"));
	fontMap.insert({ TEXT("NBG_S"), font });
	
	font = CreateFont(50, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("³ª´®¹Ù¸¥°íµñ"));
	fontMap.insert({ TEXT("NBG_B"), font });

	font = CreateFont(150, 100, 180, 180, 500, 1, 0, 0, DEFAULT_CHARSET | HANGEUL_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("³ª´®¹Ù¸¥°íµñ Bold"));

	fontMap.insert({ TEXT("NBB"), font });

	font = CreateFont(15, 0, 0, 0, 300, 0, 0, 0, HANGEUL_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("µ¸¿ò"));
	fontMap.insert({ TEXT("µ¸¿ò"), font });
	img = IMAGEMANAGER->AddFrameImage(TEXT("font"), TEXT("../Resource/SpaceShip/Damage.bmp"), 240, 160, 10, 5, true, COLOR_M);

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


void FontManager::RenderTextBox(HDC hdc, const std::string fontName, int size,const std::string strText, RECT * rc, COLORREF color)
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
		DrawText(hdc, strText.c_str(), size, rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		//TextOut(hdc, pos->x, pos->y, strText.c_str(), strText.size());

		SelectObject(hdc, oldFont);
		SetTextColor(hdc, oldColor);

	}
}


void FontManager::TextGaugeRender(HDC hdc, int iHp, RECT * rc, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szStr[256] = { 0, };
	HFONT oldFont;

	it_Font = fontMap.find(TEXT("NBG"));

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
	}

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

void FontManager::TextGaugeRender(HDC hdc, int _gauge, int _maxGauge, RECT * rc, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szStr[256] = { 0, };
	HFONT oldFont;

	it_Font = fontMap.find(TEXT("NBG"));

	if (it_Font != fontMap.end())
	{
		HFONT font = (HFONT)(it_Font->second);
		oldFont = (HFONT)SelectObject(hdc, font);
		COLORREF oldColor = SetTextColor(hdc, color);

		TCHAR strHp[256];
		_stprintf(strHp, TEXT("%d / %d"), _gauge, _maxGauge);

		DrawText(hdc, strHp, _tcslen(strHp), rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);


		SelectObject(hdc, oldFont);
		SetTextColor(hdc, oldColor);
	}

}


void FontManager::SetNumber(int num)
{
	iNumber = num;
}

void FontManager::RenderNumber(HDC hdc, int destX, int destY)
{
	str = std::to_string(iNumber);

	for (int i = 0; i < str.size(); i++)
	{
		// CharÇüÀ¸·Î °è»ê ÇØ¼­ °á°ú µµÃâ
		int n = (int)str[i];
		n -= (int)'0';


		img->FrameRender(hdc, destX + img->GetFrameWidth() * i, destY, n, 0);
	}
}
