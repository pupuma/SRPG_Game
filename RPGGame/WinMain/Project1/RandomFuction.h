#pragma once

#include "SingletonBase.h"
#include <time.h>
class RandomFuction 
	: public SingletonBase<RandomFuction>
{
public:
	RandomFuction() 
	{
		srand(GetTickCount());
	}
	~RandomFuction() {}

	inline int GetInt(int num) { return rand() % num; }
	
	inline int GetFromIntoTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};
