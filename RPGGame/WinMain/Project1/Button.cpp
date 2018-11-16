#include "Game.h"
#include "Button.h"



Button::Button()
{

}


Button::~Button()
{

}

bool Button::Init(const std::string imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, FUNC pFunc)
{
	_callBackFunc = pFunc;
	_direction = BUTTONDIR_NONE;

	_x = x;
	_y = y;

	_btnDownFramePoint = btnDownFramePoint;
	_btnUpFramePoint = btnUpFramePoint;

	_imageName = imageName;

	_image = IMAGEMANAGER->FindImage(_imageName);
	_rc = RectMakeCenter(_x, _y, _image->GetFrameWidth(), _image->GetFrameHeight());



	return true;
}

void Button::Release()
{
}

void Button::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);
	
	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIR_DOWN;
		}
		else if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIR_DOWN)
		{
			_direction = BUTTONDIR_UP;
			_callBackFunc();
		}
	}
	else
	{
		_direction = BUTTONDIR_NONE;
	}
}

void Button::Render(HDC hdc)
{
	switch (_direction)
	{
	case BUTTONDIR_NONE:

	case BUTTONDIR_UP:
		_image->FrameRender(hdc, _rc.left, _rc.top, _btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
	case BUTTONDIR_DOWN:
		_image->FrameRender(hdc, _rc.left, _rc.top, _btnDownFramePoint.x, _btnDownFramePoint.y);

		break;
	}
}


// static으로 맴버를 선언 해야 한다. 