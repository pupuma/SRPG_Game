#pragma once

#include "Character.h"

class Player 
	: public Character
{
public:
	Player(std::string _name);
	~Player();
public:
	void UpdateAI();
};

