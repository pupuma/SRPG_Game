#pragma once

#include "SingletonBase.h"

class Animation;

class AnimationManager
	: public SingletonBase<AnimationManager>
{
private:
	std::map<std::string, Animation*> totalAni;
	std::map<std::string, Animation*>::iterator it;
public:
	AnimationManager();
	~AnimationManager();

public:
	bool Init();
	void Release();
	void Update();

public:
	void AddDefAni(std::string keyName, std::string imageName, int fps, bool reverse = false, bool loop = false);
	void AddArrAni(std::string keyName, std::string imageName, int* arr, int arrLen, int fps, bool loop = false);
	void AddCoordAni(std::string keyName, std::string imageName, int start, int end, int fps, bool reverse = false, bool loop = false);

	void Start(std::string key);
	void Stop(std::string key);
	void Pause(std::string key);
	void Resume(std::string key);

	Animation* FindAni(std::string key);

};

