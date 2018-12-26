#pragma once

class Map;
class Character;
class GameUI;
class BattleScene
	: public GameNode
{
private:
	GameUI* gameUI;
	Map* map;
	float deltaTime;
	bool pause;
private:
	std::list<Component*> stageComponentList;

	std::vector<Character*> playerList;
	std::vector<Character*> monsterList;
	std::vector<Character*> npcList;
public:
	BattleScene();
	~BattleScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

