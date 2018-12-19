#include "Game.h"
#include "EventSystem.h"

#include "Character.h"

EventSystem::EventSystem()
{
}


EventSystem::~EventSystem()
{
}

void EventSystem::Init()
{
	qusetNumber = 0;
	index = 0;
	type = eGameType::GT_NONE;
	isEvent = false;
	isFadeIn = false;
	isFadeOut = false;
	isTextEnd = true;
	isTextStart = false;
	fadeImg = IMAGEMANAGER->FindImage(TEXT("Background"));
}

void EventSystem::Update()
{
	if (true == isTextEnd)
	{
		colorKey += 3;
		if (colorKey >= 255)
		{
			colorKey = 255;
			isFadeOut = true;
		}
	}
}

void EventSystem::Render(HDC hdc)
{
	if (isEvent)
	{
		if (isTextEnd)
		{
			FadeOut(hdc);
		}
	}
	else
	{

	}
}

void EventSystem::UpdateEvent(Character * _player)
{
	switch (qusetNumber)
	{
	case 1:
	{
		if (_player->GetTilePosition().x >= 19)
		{
			isEvent = true;
			_player->ChangeState(eStateType::ST_IDLE);
		}
	}
		break;
	}
}

void EventSystem::NextQusetNumber()
{
	qusetNumber += 1;
}

int EventSystem::GetPlayerCount()
{
	switch (qusetNumber)
	{
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 3;
		break;
	case 5:
		return 3;
		break;
	}
	return 0;
}

int EventSystem::GetNPCCount()
{
	switch (qusetNumber)
	{
	case 1:
		return 0;

		break;
	case 2:
		return 0;

		break;
	case 3:
		return 1;

		break;
	case 4:
		return 0;

		break;
	case 5:
		return 0;

		break;
	}
	return 0;
}

int EventSystem::GetMonsterCount()
{
	switch (qusetNumber)
	{
	case 1:
		return 1;

		break;
	case 2:
		return 3;

		break;
	case 3:
		return 3;

		break;
	case 4:
		return 5;

		break;
	case 5:
		return 7;

		break;
	}
	return 0;
}

void EventSystem::FadeIn(HDC hdc)
{
	fadeImg->AlphaRender(hdc, colorKey);
}

void EventSystem::FadeOut(HDC hdc)
{
	fadeImg->AlphaRender(hdc, colorKey);
}

std::string EventSystem::GetCharacterName()
{
	if (!characterList.empty())
	{
		return characterList[index]->GetName();
	}

	std::string str = TEXT("...");
	return str;
}

void EventSystem::AddCharacterList(Character * _character)
{
	characterList.push_back(_character);
}
