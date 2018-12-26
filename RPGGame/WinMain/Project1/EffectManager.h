#pragma once

#include "SingletonBase.h"

class Effect;

class EffectManager
	: public SingletonBase<EffectManager>
{
private:
	typedef std::vector<Effect*>						vEffect;
	typedef std::vector<Effect*>::iterator				iEffect;


	typedef std::map<std::string, vEffect>				mTotalEffect;
	typedef std::map<std::string, vEffect>::iterator	iTotalEffect;
private:

	//typedef std::map<std::string, Effect*>				EffectMap;
	//typedef std::map<std::string, Effect*>::iterator	iEffectMap;
	//typedef std::list<Effect*>							EffectQueue;
	//typedef std::list<Effect*>::iterator				iEffectQueue;


private:
	mTotalEffect _mtotalEffect;
private:
	//EffectMap	_mTotalEffect;
	//EffectQueue _qEffectList;

	//std::unique_ptr<std::thread*> _th;
	
	std::thread* _th;
	std::mutex _mutexObj;

	bool isStart;
	bool isEnd;
	HDC hdc;
public:
	EffectManager();
	~EffectManager();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	HDC GetHDC() { return hdc; }
	void SetHDC(HDC _hdc) { hdc = _hdc; }
	void ProcessEffect();
public:
	void AddEffect(std::string effectName,
		const TCHAR* imageName, int imageWidth, int imageHeight,
		int effectWidth, int effectHeight,
		int fps, float elapsedTime, int beffer,
		COLORREF color = COLOR_M);

	void Play(std::string effectName, int x, int y);
	void Play(std::string effectName, POINT p);
};

