#pragma once
class BackBuffer
{
private:
	typedef struct tagBackBufferInfo
	{
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOldBit;
		float fPosX,fPosY;
		int iWidth;
		int iHeight;

		tagBackBufferInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			fPosX = 0.0f;
			fPosY = 0.0f;
			iWidth = 0;
			iHeight = 0;
		}
	}BackBuffer_Info, *LPBackBufferInfo;
private:
	LPBackBufferInfo _backBufferInfo;

public:
	BackBuffer();
	~BackBuffer();

public:
	bool Init(int width, int height);
	void Release();
	void Render(HDC hdc, int destX, int destY);

public:
	inline HDC GetMemDC() { return _backBufferInfo->hMemDC; }
};

