#include "Game.h"
#include "NPC.h"



NPC::NPC(std::string _name, float _deep)
	: Character(_name, _deep)
{
}


NPC::~NPC()
{
}

bool NPC::Init()
{
	return true;
}
