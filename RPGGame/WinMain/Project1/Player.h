#pragma once

#include "Character.h"


enum eJobClass
{
	JOB_NONE,
	JOB_WARRIOR,
	JOB_ARCHER,
	JOB_HEALER,
	JOB_MAGIC,
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
	bool Init(int _index);
	//void Render(HDC hdc);
public:
	void UpdateAI();
	void AttackPattern();
	void SkillPattern(int _number);
	eJobClass GetJobs() { return job; }
};

