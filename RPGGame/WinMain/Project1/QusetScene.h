#pragma once

class Map;

class QusetScene
	: public GameNode
{
private:
	Character* player;
private:
	std::string characterName;
	std::string text;
private:
	std::list<Component*> stageComponentList;
	RECT rcTextBox;
	RECT rcDrawText;
	float deltaTime;
	RECT rcCharacterBox;
	RECT rcNameBox;
private:
	Map* map;
public:
	QusetScene();
	~QusetScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

