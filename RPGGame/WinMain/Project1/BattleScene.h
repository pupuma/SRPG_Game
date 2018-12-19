#pragma once
class BattleScene
	: public GameNode
{
public:
	BattleScene();
	~BattleScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

