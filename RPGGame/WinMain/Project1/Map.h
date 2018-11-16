#pragma once
class Map
	: public Component
{
public:
	Map(std::string _name);
	~Map();
public:
	bool Init();
	void Deinit();
	void Update();
	void Render(HDC hdc);

	void Release();
	void Reset();
};

