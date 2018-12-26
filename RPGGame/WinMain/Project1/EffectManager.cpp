#include "Game.h"
#include "EffectManager.h"

#include "Effect.h"

EffectManager::EffectManager()
{
	isStart = false;
	isEnd = false;
}


EffectManager::~EffectManager()
{
	isEnd = true;
	_th->join();


	if (isEnd)
	{
		SAFE_DELETE(_th);
	}
}

bool EffectManager::Init()
{
	return true;
}

void EffectManager::Release()
{
	iTotalEffect it = _mtotalEffect.begin();

	for (; it != _mtotalEffect.end(); ++it)
	{
		iEffect vit = (it->second).begin();
		for (; vit != (it->second).end(); ++vit)
		{
			(*vit)->Release();
			SAFE_DELETE((*vit));
		}
		(it->second).clear();
	}

	//for (auto a : _mtotalEffect)
	//{
	//	a.second->Release();
	//	SAFE_DELETE((a.second));
	//}

}

void EffectManager::Update()
{
	iTotalEffect it = _mtotalEffect.begin();

	for (; it != _mtotalEffect.end(); ++it)
	{
		for (auto vit : it->second)
		{
			vit->Update();
		}
	}


}

void EffectManager::Render(HDC hdc)
{
	iTotalEffect it = _mtotalEffect.begin();

	for (; it != _mtotalEffect.end(); ++it)
	{
		for (auto vit : it->second)
		{
			vit->Render(hdc);
		}
	}
}
void EffectManager::ProcessEffect()
{
	//while (!isEnd)
	//{
	//	if (_qEffectList.empty())
	//	{
	//		continue;
	//	}
	//	std::unique_lock<std::mutex> lock(_mutexObj);
	//	for (iEffectQueue it = _qEffectList.begin(); it != _qEffectList.end(); it++)
	//	{
	//		if ((*it)->GetIsRunning() == false)
	//		{
	//			SAFE_DELETE((*it));
	//			it = _qEffectList.erase(it);
	//		}
	//		else
	//		{
	//			//(*it)->Update(TIMEMANAGER->GetElapsedTime());
	//			//(*it)->Render(GetHDC());
	//			//++it;
	//		}
	//	}
	//	lock.unlock();
	//}
}
// 이미지를 가지고 스프라이트 이미지를 가지고 이펙트를 만든다.
// 이미지나 에니메니션 같은 경우에는 하나만 만들지만
// 이펙트는 이미지가 출력이 되는 객체를 만든다.
// 애니메이션 객체를 만들고 객체 풀을 만들고 호풀이 되면 객체를 실행 시킨다. ( 사용 ) 
// 
void EffectManager::AddEffect(std::string effectName, const TCHAR * imageName, int imageWidth, int imageHeight,
	int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer, COLORREF color)
{
	Image* img;

	iTotalEffect it = _mtotalEffect.find(effectName);

	if (it != _mtotalEffect.end())
	{
		return;
	}

	img = IMAGEMANAGER->FindImage(effectName);

	if (img == NULL)
	{
		img = IMAGEMANAGER->AddImage(effectName, imageName, imageWidth, imageHeight, true, color);
	}

	vEffect vEffectBuffer;
	for (int i = 0; i < buffer; ++i)
	{
		vEffectBuffer.push_back(new Effect());
		vEffectBuffer[i]->Init(img, effectWidth, effectHeight, fps, elapsedTime);
	}

	_mtotalEffect.insert(std::pair<std::string, vEffect>(effectName, vEffectBuffer));
/*
	Image* img;

	iEffectMap it = _mTotalEffect.find(effectName);

	if (it != _mTotalEffect.end())
	{
		return;
	}

	img = IMAGEMANAGER->FindImage(effectName);
	assert(img != NULL);

	Effect* pEffect =new Effect();
	pEffect->Init(img, effectWidth, effectHeight, fps, elapsedTime);

	_mTotalEffect.insert(std::pair<std::string, Effect*>(effectName, pEffect));

*/
}

void EffectManager::Play(std::string effectName, int x, int y)
{
	iTotalEffect it = _mtotalEffect.find(effectName);

	if (it != _mtotalEffect.end())
	{
		for (auto vit : it->second)
		{
			if (vit->GetIsRunning())
			{
				continue;
			}
			vit->StartEffect(x, y);
			return;
		}
	}

	//iEffectMap it = _mTotalEffect.find(effectName);

	//if (it != _mTotalEffect.end())
	//{
	//	Effect* pEffect = new Effect(*(it->second));
	//	pEffect->Init(pEffect->GetImage(), pEffect->GetImage()->GetFrameWidth(),
	//		pEffect->GetImage()->GetFrameHeight(), pEffect->GetFPS(), pEffect
	//		->GetElapsedTime());
	//	{
	//		// 동기화 객체 슈마포어 ,,,
	//		std::lock_guard<std::mutex> lockGuard(_mutexObj);
	//		pEffect->StartEffect(x, y);
	//		_qEffectList.push_back(pEffect);

	//	}
	//	return;
	//}
}

void EffectManager::Play(std::string effectName, POINT p)
{
	Play(effectName, p.x, p.y);
}
