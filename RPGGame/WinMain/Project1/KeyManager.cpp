#include "Game.h"
#include "KeyManager.h"



KeyManager::KeyManager()
{
	this->Init();
}


KeyManager::~KeyManager()
{
}

bool KeyManager::Init()
{
	this->GetKeyUp().reset();
	this->GetKeyDown().reset();
	return true;
}

void KeyManager::Release()
{
}


bool KeyManager::IsOnceKeyDown(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)			// 현재 키 상태 ( 이전 키 상태 확인 x ) 
	{
		if (!this->GetKeyDown()[_key])
		{
			this->SetKeyDown(_key, true);
			return true;
		}
	}
	else
	{
		this->SetKeyDown(_key, false);
	}
	return false;
}

bool KeyManager::IsOnceKeyUp(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
	{
		this->SetKeyUp(_key, true);
	}
	else
	{
		if (this->GetKeyUp()[_key])
		{
			this->SetKeyUp(_key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::IsStayKeyDown(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
	{
		return true;
	}
	return false;
}

// 토글키 처리 
bool KeyManager::IsToggleKey(int _key)
{
	if (GetKeyState(_key) & 0x0001)
	{
		return true;
	}
	return false;
}

bitset<KEYMAX> KeyManager::GetKeyUp()
{
	return _keyUp;
}

bitset<KEYMAX> KeyManager::GetKeyDown()
{
	return _keyDown;
}


void KeyManager::SetKeyDown(int _key, bool _state)
{
	_keyDown.set(_key, _state);
}
void KeyManager::SetKeyUp(int _key, bool _state)
{
	_keyUp.set(_key, _state);

}