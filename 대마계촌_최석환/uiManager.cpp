#include "stdafx.h"
#include "uiManager.h"


HRESULT uiManager::init(void)
{
	_score = 0;
	_time = 120;
	_life = 2;
	_weap = WEAP::SPEAR;
	return S_OK;
}

void uiManager::release(void)
{
}
