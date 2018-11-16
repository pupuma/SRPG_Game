#pragma once
#include "Game.h"
#include "CustomDefine.h"
#include "MainGame.h"


//====================================================================================================
HWND		_hWnd;
HINSTANCE	_hInst;
POINT		_ptMouse;

//====================================================================================================

MainGame	_mg;

LPCTSTR		_lpszClass = TEXT("Win32API");

//=====================================================================================================

void setWindowsSize(int x, int y, int width, int height);


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//=====================================================================================================

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lPszCmdParam, int cmdShow)
{
	MSG							message;
	WNDCLASS					wndClass;

	_hInst = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	if (!_hWnd)
		return 0;

	setWindowsSize(WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY);

	if (!_mg.Init())
		return 0;

	ShowWindow(_hWnd, cmdShow);

	HDC hdc = GetDC(_hWnd);

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->Update(60.f);

			_mg.Update();
			_mg.Render(hdc);
		}
	}

	_mg.Release();
	ReleaseDC(_hWnd, hdc);

	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, NULL);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}