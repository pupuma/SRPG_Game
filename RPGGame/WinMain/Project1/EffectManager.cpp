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
