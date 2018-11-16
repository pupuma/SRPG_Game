#pragma once


enum eComponentType
{
	CT_DEFAULT,
	CT_PLAYER,
	CT_NPC,
	CT_MONSTER,
	CT_ITEM,
};

class Component
{
protected:
	eComponentType type;
	std::string name;

	Point position;
	//bool _isLive;
public:
	Component(std::string _name);
	~Component();
public:
	virtual bool Init() = 0;
	virtual void Deinit() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	virtual void Release() = 0;
	virtual void Reset() = 0;
public:
	virtual void ReceiveMsg(const sMessageParam& _param);
};

