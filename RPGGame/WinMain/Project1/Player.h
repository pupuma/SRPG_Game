#pragma once

#include "Character.h"


enum eJobClass
{
	JOB_NONE,
	JOB_WARRIOR,
	JOB_ARCHER,
	JOB_HEALER,
};


class Player 
	: public Character
{
private:
	eJobClass job;
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

