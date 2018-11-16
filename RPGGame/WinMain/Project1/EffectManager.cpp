#include "Game.h"
#include "EffectManager.h"

#include "Effect.h"

EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
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
}

void EffectManager::Play(std::string effectName, POINT p)
{
	Play(effectName, p.x, p.y);
}
