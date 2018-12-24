#pragma once

#include "Character.h"
class Monster
	:  public Character
{
public:
	Monster(std::string _name, float _deep);
	~Monster();
public:
	bool Init();
	bool Init(int _index);
public:

	void UpdateAI();
	void AttackPattern();
};

