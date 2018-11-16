#pragma once

#include <string>

class Component;

struct sMessageParam
{
	Component* sender;
	Component* receiver;
	std::string message;
	int attackPoint;
};
