#pragma once

#include "SingletonBase.h"
#include <bitset>
using std::bitset;

#define KEYMAX 256

class KeyManager
	: public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
	bitset<KEYMAX> _keyPress;

public:
	KeyManager();
	~KeyManager();
public:
	bool Init();
	void Release();
public:
	bool IsOnceKeyDown(int _key);
	bool IsOnceKeyUp(int _key);
	bool IsStayKeyDown(int _key);
	bool IsToggleKey(int _key);

	bitset<KEYMAX> GetKeyUp();
	bitset<KEYMAX> GetKeyDown();

	void SetKeyDown(int _key, bool _state);
	void SetKeyUp(int _key, bool _state);

};

