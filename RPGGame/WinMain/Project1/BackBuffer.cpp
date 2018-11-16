#include "Game.h"
#include "BackBuffer.h"



BackBuffer::BackBuffer() 
	: _backBufferInfo(NULL)
{
}

BackBuffer::~BackBuffer()
{
}

bool BackBuffer::Init(int width, int height)
{
	if (_backBufferInfo != NULL)
	{
		Release();
	}

	HDC hdc = GetDC(_hWnd);
	_backBufferInfo = new BackBuffer_Info();
	_backBufferInfo->hMemDC = CreateCompatibleDC(hdc);
	_backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_backBufferInfo->hOldBit = (HBITMAP)SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
	_backBufferInfo->iWidth = width;
	_backBufferInfo->iHeight = height;

	if (_backBufferInfo->hBit == NULL)
	{
		Release();
		return false;
	}

	ReleaseDC(_hWnd, hdc);

	return true;

}

void BackBuffer::Release()
{
	if (_backBufferInfo)
	{
		SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hOldBit);
		DeleteObject(_backBufferInfo->hBit);
		DeleteDC(_backBufferInfo->hMemDC);

		SAFE_DELETE(_backBufferInfo);

	}
}

void BackBuffer::Render(HDC hdc, int destX, int destY)
{
	// 백버퍼에 출력된 내용들을 화면으로 고속 복사한다. 
	BitBlt(hdc,									// 복사가 되는 DC
		destX,									// 복사가 되는 위치
		destY,									// 
		_backBufferInfo->iWidth,				// 복사가 되는 크기
		_backBufferInfo->iHeight,			
		_backBufferInfo->hMemDC,				// 복사할 소스가 있는 DC
		0,										// 복사할 소스의 시작 위치
		0,										
		SRCCOPY);								// 
}
