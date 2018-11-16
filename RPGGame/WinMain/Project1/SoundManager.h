#pragma once

#include "SingletonBase.h"

#include "../Resource/Sound/SoundM/inc/fmod.hpp"							// fmod�� ����� ���� ���̺귯�� �ش�

#pragma comment(lib, "../Resource/Sound/SoundM/lib/fmodex_vc.lib")			// ���̺귯�� ��ġ 

using namespace FMOD;

#define TOTALSOUNDBUFFER 15													// ���ÿ� ����� �� �ִ� ����


struct SoundInfo
{
	Sound*		sound;			// �ε��� ���� ����
	Channel*	channel;		// ���� ������ ���� ���� 
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

