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

	// ������ ������ �ʾҴٸ�...
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

// fmod�� wav ���� �θ� ����ؾ� �Ѵ�. 

void SoundManager::AddSound(std::string keyName, std::string soundName, bool bgm, bool loop)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		return;
	}

	SoundInfo* info = new SoundInfo();
	FMOD_RESULT	result;
	FMOD_MODE mode;							// ���� ��� 

	if (loop)
	{
		mode = FMOD_LOOP_NORMAL;			// ����( ������ ó��) 
	}
	else
	{
		mode = FMOD_DEFAULT;				// ����Ʈ 
	}


	if (bgm)
	{
		// 1�� �̻� �� ������ ��� �� �� 
		result = _system->createStream(soundName.c_str(), mode,
			NULL, &info->sound);
	}
	else
	{
		// 1�� ���� ������ ��� �� �� 
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

fmode�θ� �⺻ ��� �� ����� ���� ��� ������ ex��� �Ǿ��ִ� lib�� ��� �Ҷ��� ����Ʈ������ ��ť��Ʈ�� Ȯ�� �ؾ� �Ѵ�.
ex) 
10 �� ������ 1�� ¥�� ���� �� �ִٸ� 
������ 15�� ä���� ������ �ְ� , �ű⿡ ���� ä�ο� ������ ��ž�� �Ǿ�߸� ��ȯ�� �ȴ�. 

*/

