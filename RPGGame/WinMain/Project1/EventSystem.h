#pragma once

class Character;

enum eGameType
{
	GT_NONE,
	GT_EVENT,
	GT_BATTLE,

};

enum eBranch
{
	B_TALK,
	B_END,
	B_BATTLE,
	B_EVENT,
	B_NONE,
};
class EventSystem 
	: public SingletonBase<EventSystem>
{
private:
	std::vector<Character*> playerList;
	std::vector<Character*> npcList;
	std::vector<Character*> monsterList;
private:
	Image* fadeImg;
private:
	eGameType type;
	bool isEvent;
	bool isEventStart;
	bool isEvnetEnd;

	int qusetNumber;
	bool isFadeOut;
	bool isFadeIn;
	bool isTextEnd;
	bool isTextStart;
	bool isNext;
private:
	float deltaTime;
	int playerCount;
	int npcCount;
	int monsterCount;
	int index;
	int colorKey;
	
private:
	int textIndex;
	int iSceneNumber;
	eBranch branch;
	int charIndex;
	std::string text;
	std::string fileName;
	int frameX;
	int frameY;
private:
	std::string name;
private:
	std::vector<Character*> characterList;
	std::queue<std::string> q_Data;

public:
	EventSystem();
	~EventSystem();
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void DeInit();

public:
	void MapDataInit();
	void QusetInit();
	void UpdateEvent(Character* _player);
	void NextQusetNumber();
	int GetPlayerCount();
	int GetNPCCount();
	int GetMonsterCount();
	void FadeIn(HDC hdc);
	void FadeOut(HDC hdc);
	std::string GetCharacterName();
	void AddCharacterList(Character* _character);
	void EventData();
	void PopData();
	void ChangeScene();
	Image* FindFaceImg();
public:
	bool IsFadeIn() { return isFadeIn; }
	bool IsFadeOut() { return isFadeOut; }
	void SetFadeIn(bool _isFadeIn) { isFadeIn = _isFadeIn; }
	void SetFadeOut(bool _isFadeOut) { isFadeOut = _isFadeOut; }
	int GetQusetNumber() { return qusetNumber; }
	void SetQusetNumber(int _num) { qusetNumber = _num; }
	int GetSceneNumber() {	return iSceneNumber; }
	eGameType GetGameType() { return type; }
	void SetGameType(eGameType _type) { type = _type; }
	bool IsEvent() { return isEvent; }
	void SetEvent(bool _event)  { isEvent = _event; }
	std::vector<Character*> GetCharacterList() { return characterList; }
	int GetBoxImgFrameX() { return frameX; }
	int GetBoxImgFrameY() { return frameY; }
	std::string GetText() { return text; }
	std::string GetFileName() { return fileName; }
	void SetTextEnd(bool _isTextEnd) { isTextEnd = _isTextEnd; }
	eBranch GetBranch() { return branch; }
	void SetBranch(eBranch _branch) { branch = _branch; }
	bool IsNext() { return isNext; }
	void SetNext(bool _isNext) { isNext = _isNext; }
	std::vector<Character*> GetPlayerList() { return playerList; }
	std::vector<Character*> GetMonsterList() { return monsterList; }
	std::vector<Character*> GetNPCList() { return npcList; }
};

