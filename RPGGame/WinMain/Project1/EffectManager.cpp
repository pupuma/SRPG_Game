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
// �̹����� ������ ��������Ʈ �̹����� ������ ����Ʈ�� �����.
// �̹����� ���ϸ޴ϼ� ���� ��쿡�� �ϳ��� ��������
// ����Ʈ�� �̹����� ����� �Ǵ� ��ü�� �����.
// �ִϸ��̼� ��ü�� ����� ��ü Ǯ�� ����� ȣǮ�� �Ǹ� ��ü�� ���� ��Ų��. ( ��� ) 
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
	//		// ����ȭ ��ü �������� ,,,
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
