#include "Game.h"
#include "AnimationManager.h"
#include "Animation.h"


AnimationManager::AnimationManager()
{
}


AnimationManager::~AnimationManager()
{
}

bool AnimationManager::Init()
{
	return true;
}

void AnimationManager::Release()
{
	for (it = totalAni.begin(); it != totalAni.end(); it++)
	{
		SAFE_DELETE((it->second));
	}

	totalAni.clear();
}

void AnimationManager::Update()
{
	for (it = totalAni.begin(); it != totalAni.end(); it++)
	{
		if ((it->second)->isPlay())
		{
			(it->second)->FrameUpdate(TIMEMANAGER->GetElapsedTime());
		}
	}
}

void AnimationManager::AddDefAni(std::string keyName, std::string imageName, int fps, bool reverse, bool loop)
{
	it = totalAni.find(keyName);
	if (it != totalAni.end())
	{
		return;
	}
	Image* img = IMAGEMANAGER->FindImage(imageName);
	assert(img != NULL);

	Animation* ani = new Animation();

	ani->Init(img);
	ani->SetDefPlayFrame(reverse, loop);
	ani->SetFPS(fps);

	totalAni.insert({ keyName, ani });
}

void AnimationManager::AddArrAni(std::string keyName, std::string imageName, int* arr, int arrLen, int fps, bool loop)
{
	it = totalAni.find(keyName);
	if (it != totalAni.end())
	{
		return;
	}
	Image* img = IMAGEMANAGER->FindImage(imageName);
	assert(img != NULL);

	Animation* ani = new Animation();

	ani->Init(img);
	ani->SetPlayFrame(arr, arrLen,loop);
	ani->SetFPS(fps);

	totalAni.insert({ keyName, ani });
}

void AnimationManager::AddCoordAni(std::string keyName, std::string imageName, int start, int end, int fps,bool reverse , bool loop)
{
	it = totalAni.find(keyName);
	if (it != totalAni.end())
	{
		return;
	}
	Image* img = IMAGEMANAGER->FindImage(imageName);
	assert(img != NULL);

	Animation* ani = new Animation();

	ani->Init(img);
	ani->SetPlayFrame(start, end,reverse , loop);
	ani->SetFPS(fps);

	totalAni.insert({ keyName, ani });
}



void AnimationManager::Start(std::string key)
{
	it = totalAni.find(key);
	if (it == totalAni.end())
	{
		return;
	}
	(it->second)->Start();
		
}

void AnimationManager::Stop(std::string key)
{
	it = totalAni.find(key);
	if (it == totalAni.end())
	{
		return;
	}
	(it->second)->Stop();
}

void AnimationManager::Pause(std::string key)
{
	it = totalAni.find(key);
	if (it == totalAni.end())
	{
		return;
	}
	(it->second)->Pause();
}

void AnimationManager::Resume(std::string key)
{
	it = totalAni.find(key);
	if (it == totalAni.end())
	{
		return;
	}
	(it->second)->Resume();
}

Animation * AnimationManager::FindAni(std::string key)
{
	it = totalAni.find(key);
	if (it != totalAni.end())
	{
		return (it->second);
	}
	return NULL;
}
