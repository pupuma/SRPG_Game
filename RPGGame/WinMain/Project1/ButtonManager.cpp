#include "Game.h"
#include "ButtonManager.h"
#include "SelectStateButton.h"



ButtonManager::ButtonManager()
{
}


ButtonManager::~ButtonManager()
{
}

void ButtonManager::Init()
{
	bAcitve = eButtonActive::BA_NONE;
	isActive = false;
	isAttack = false;
}

void ButtonManager::Update()
{
	switch (bAcitve)
	{
	case eButtonActive::BA_ATTACK:
		isAttack = true;
		break;
	case eButtonActive::BA_SKILL:
		isAttack = false;
		break;
	case eButtonActive::BA_ITEM:
		isAttack = false;
		break;
	case eButtonActive::BA_END:
		isAttack = false;
		break;
	}
}

void ButtonManager::SetSelectActive(bool _isActive)
{
	isActive = _isActive;
}
void ButtonManager::SetSelectActive(bool _isActive, eButtonActive _bAcitve)
{
	isActive = _isActive;
	bAcitve = _bAcitve;
}
