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
	mTotalEffect _mtotalEffect;
public:
	EffectManager();
	~EffectManager();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void AddEffect(std::string effectName,
		const TCHAR* imageName, int imageWidth, int imageHeight,
		int effectWidth, int effectHeight,
		int fps, float elapsedTime, int beffer,
		COLORREF color = COLOR_M);

	void Play(std::string effectName, int x, int y);
	void Play(std::string effectName, POINT p);
};

