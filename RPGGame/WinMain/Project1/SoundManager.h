#pragma once

#include "SingletonBase.h"

#include "../Resource/Sound/SoundM/inc/fmod.hpp"							// fmod의 사용을 위한 라이브러리 해더

#pragma comment(lib, "../Resource/Sound/SoundM/lib/fmodex_vc.lib")			// 라이브러리 위치 

using namespace FMOD;

#define TOTALSOUNDBUFFER 15													// 동시에 출력할 수 있는 버퍼


struct SoundInfo
{
	Sound*		sound;			// 로드한 음원 정보
	Channel*	channel;		// 현재 음원의 상태 정보 
};

class SoundManager
	: public SingletonBase<SoundManager>
{
private:
	System * _system;
	std::map<std::string, SoundInfo*> totalSound;
	std::map<std::string, SoundInfo*>::iterator it;
public:
	SoundManager();
	~SoundManager();
public:
	bool Init();
	void Release();
	void Update();
public:
	void AddSound(std::string keyName, std::string soundName, bool bgm, bool loop);
public:
	void Play(std::string keyName, float volume);
	void Stop(std::string keyName);
	void Pause(std::string keyName);
	void Resume(std::string keyName);
public:
	bool IsPlaySound(std::string keyName);
	bool IsPauseSound(std::string keyName);
public:
	bool ErrCheck(FMOD_RESULT result);
};

