#pragma once

class Character;

enum eGameType
{
	GT_NONE,
	GT_EVENT,
	GT_BATTLE,

};
class EventSystem 
	: public SingletonBase<EventSystem>
{
private:
	Image* fadeImg;
private:
	eGameType type;
	bool isEvent;
	int qusetNumber;
	bool isFadeOut;
	bool isFadeIn;
	bool isTextEnd;
	bool isTextStart;

private:
	int playerCount;
	int npcCount;
	int monsterCount;
	int index;
	int colorKey;
private:
	std::string name;
private:
	std::vector<Character*> characterList;
public:
	EventSystem();
	~EventSystem();
public:
	void Init();
	void Update();
	void Render(HDC hdc);
public:
	void UpdateEvent(Character* _player);
	void NextQusetNumber();
	int GetPlayerCount();
	int GetNPCCount();
	int GetMonsterCount();
	void FadeIn(HDC hdc);
	void FadeOut(HDC hdc);
	std::string GetCharacterName();
	void AddCharacterList(Character* _character);
public:

	int GetQusetNumber() { return qusetNumber; }
	void SetQusetNumber(int _num) { qusetNumber = _num; }
	eGameType GetGameType() { return type; }
	void SetGameType(eGameType _type) { type = _type; }
	bool IsEvent() { return isEvent; }
	void SetEvent(bool _event) { isEvent = _event; }
	std::vector<Character*> GetCharacterList() { return characterList; }
	bool IsFadeOut(){ return isFadeOut; }
	bool IsFadIn(){ return isFadeIn; }
};

