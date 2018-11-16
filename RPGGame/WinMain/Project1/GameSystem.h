#pragma once

#include "SingletonBase.h"


class GameSystem
	: public SingletonBase<GameSystem>
{
private:

public:
	GameSystem();
	~GameSystem();
public:
	void SetMousePosition(LPARAM lParam);
	POINT GetMousePosition();

};

