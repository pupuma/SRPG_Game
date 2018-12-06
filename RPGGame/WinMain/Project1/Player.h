#pragma once

#include "Character.h"

class Player 
	: public Character
{
public:
	Player(std::string _name, float _deep);
	~Player();
public:
	bool Init();
	//void Render(HDC hdc);
public:
	void UpdateAI();
	void AttackPattern();
};

