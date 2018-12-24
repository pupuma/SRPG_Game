#include "Game.h"
#include "ComponentSystem.h"

ComponentSystem* ComponentSystem::c_Instance = 0;

ComponentSystem * ComponentSystem::GetInstance()
{
	if (0 == c_Instance)
	{
		c_Instance = new ComponentSystem();
	}
	return c_Instance;
}

ComponentSystem::ComponentSystem()
{
	//ProcessMsgQueue();
}


ComponentSystem::~ComponentSystem()
{
}

void ComponentSystem::Update()
{
	ProcessMsgQueue();
}

void ComponentSystem::Release()
{
	for (auto a : c_ComponentMap)
	{
		//a.second->Release();
		a.second = NULL;
		delete a.second;
	}
	c_ComponentMap.clear();
}

void ComponentSystem::AddComponent(std::string _name, Component * _component)
{
	std::map<std::string, Component*>::iterator it = c_ComponentMap.find(_name);
	if (it == c_ComponentMap.end())
	{
		c_ComponentMap[_name] = _component;
	}
}

Component * ComponentSystem::FindComponent(std::string _name)
{
	std::map<std::string, Component*>::iterator it = c_ComponentMap.find(_name);
	if (it != c_ComponentMap.end())
	{
		return it->second;
	}
	return NULL;
}



void ComponentSystem::SendMsg(const sMessageParam & _param)
{
	c_MsgQueue.push(_param);
}

void ComponentSystem::ProcessMsgQueue()
{
	while (0 < c_MsgQueue.size())
	{
		sMessageParam param = c_MsgQueue.front();
		c_MsgQueue.pop();
		param.receiver->ReceiveMsg(param);
	}
}
