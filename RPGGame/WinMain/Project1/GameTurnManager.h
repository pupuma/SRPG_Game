#pragma once

class Character;

class GameTurnManager
	: public SingletonBase<GameTurnManager>
{
private:
	Character* turnCharacter;
	Image* faceImg;

private:
	int characterIndex;
	int skillIndex;
public:
	GameTurnManager();
	~GameTurnManager();
public:
	void Init();
	void NextTurn();
	void AttackAction();
	bool PlayerTrun();
	bool MyTurn(TilePoint _pos);
	void SkillAction(int _number);
	Character* GetTurn();
	Image* GetFaceImg();
	Image* FindFaceImg(Character* _click);
	std::string SkillText(int _index);
	int GetIconFrameX(int _index);
	int GetIconFrameY(int _index);
public:
	int GetSkillIndex() { return skillIndex; }
	void SetSkillIndex(int _index) { skillIndex = _index; }
};

