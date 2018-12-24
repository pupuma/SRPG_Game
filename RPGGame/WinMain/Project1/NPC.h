#pragma once
#include "Character.h"


class NPC
	: public Character
{
public:
	NPC(std::string _name, float _deep);
	~NPC();
public:
	bool Init();
};

