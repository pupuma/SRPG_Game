#pragma once
#include "SingletonBase.h"
#include <time.h>

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction()
	{
		srand(GetTickCount());
	}

	~RandomFunction() {}

	inline int GetInt(int num) { return rand() % num; }

	inline int GetFromIntoTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};