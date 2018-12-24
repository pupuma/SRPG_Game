#pragma once

class Map;

class QusetScene
	: public GameNode
{
private:
	Image* img;
	Image* talkBox;
	int frameX;
	int frameY;
private:
	Character* player;
	std::vector<Character*> playerList;
	std::vector<Character*> monsterList;
	std::vector<Character*> npcList;
private:
	std::string characterName;
	std::string text;
private:
	std::list<Component*> stageComponentList;
	RECT rcTextBox;
	RECT rcDrawText;
	float deltaTime;
	int count;
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

