#include "Game.h"

#include "SoundManager.h"

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

bool SoundManager::Init()
{
	System_Create(&_system);

	// 파일이 열리지 않았다면...
	if (ErrCheck(_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL)))
	{
		return false;
	}

	unsigned int nVersion;
	if (ErrCheck(_system->getVersion(&nVersion)))
	{
		if (nVersion != FMOD_VERSION)
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

void SoundManager::Release()
{
	it = totalSound.begin();
	for (;it != totalSound.end(); it++)
	{
		if ((it->second)->channel)
		{
			(it->second)->channel->stop();
		}

		if ((it->second)->sound)
		{
			(it->second)->sound->release();
		}

		SAFE_DELETE((it->second));
	}

	totalSound.clear();

	if (_system)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::Update()
{
	_system->update();
}

// fmod는 wav 파일 로만 사용해야 한다. 

void SoundManager::AddSound(std::string keyName, std::string soundName, bool bgm, bool loop)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		return;
	}

	SoundInfo* info = new SoundInfo();
	FMOD_RESULT	result;
	FMOD_MODE mode;							// 현재 모드 

	if (loop)
	{
		mode = FMOD_LOOP_NORMAL;			// 루프( 끝나면 처음) 
	}
	else
	{
		mode = FMOD_DEFAULT;				// 디폴트 
	}


	if (bgm)
	{
		// 1분 이상 긴 음원을 재생 할 때 
		result = _system->createStream(soundName.c_str(), mode,
			NULL, &info->sound);
	}
	else
	{
		// 1분 이하 음원을 재생 할 때 
		result = _system->createSound(soundName.c_str(), mode,
			NULL, &info->sound);
	}

	if (!ErrCheck(result))
	{
		return;
	}

	totalSound.insert(make_pair(keyName, info));
}

void SoundManager::Play(std::string keyName, float volume)				// (0.0 ~ 1.0) 1/255
{

	it = totalSound.find(keyName);
	
	if (it != totalSound.end())
	{

		//if ((it->second)->channel)
		//{
		//	return;
		//}
		_system->playSound(FMOD_CHANNEL_FREE, (it->second)->sound, false, &(it->second)->channel);
		(it->second)->channel->setVolume(volume);
	}
}

void SoundManager::Stop(std::string keyName)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->stop();
	}
}

void SoundManager::Pause(std::string keyName)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->setPaused(true);
	}
}

void SoundManager::Resume(std::string keyName)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->setPaused(false);
	}
}

bool SoundManager::IsPlaySound(std::string keyName)
{
	bool isPlay = false;

	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->isPlaying(&isPlay);
	}


	return isPlay;
}

bool SoundManager::IsPauseSound(std::string keyName)
{
	bool isPause = false;

	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->getPaused(&isPause);
	}


	return isPause;
}

bool SoundManager::ErrCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		return false;
	}



	return true;
}


/*

fmode로만 기본 기능 만 사용할 때는 상관 없지만 ex라고 되어있는 lib을 사용 할때는 사이트에가서 도큐먼트를 확인 해야 한다.
ex) 
10 초 음원과 1초 짜리 음원 이 있다면 
음원이 15개 채널을 가지고 있고 , 거기에 대한 채널에 음원이 스탑이 되어야만 반환이 된다. 

*/

