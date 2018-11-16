#pragma once
#include "BackBuffer.h"

class GameNode
{
private:
	BackBuffer*		_backBuffer;

	bool			_managerInit;

public:
	GameNode();
	virtual ~GameNode();
public:
	void SetBackBuffer();				// Buffer
public:
	virtual bool Init();
	virtual bool Init(bool mInit);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
public:
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
public:
	BackBuffer* GetBackBuffer() { return _backBuffer; }

};

