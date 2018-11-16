#pragma once


class ComponentSystem
{
private:
	static ComponentSystem* c_Instance;

public:
	static ComponentSystem* GetInstance();
private:
	std::map<std::string, Component*> c_ComponentMap;
public:
	ComponentSystem();
	~ComponentSystem();
public:
	void Update();
public:
	void AddComponent(std::string _name, Component* _component);
	Component* FindComponent(std::string _name);

//
private:
	std::queue<sMessageParam> c_MsgQueue;
public:
	void SendMsg(const sMessageParam& _param);
	void ProcessMsgQueue();
};

