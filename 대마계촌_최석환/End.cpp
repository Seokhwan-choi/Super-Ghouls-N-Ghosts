#include "stdafx.h"
#include "End.h"

HRESULT End::init(void)
{
	IMAGEMANAGER->addImage("�׳�", "images/�׳�.bmp", 1000, 672);
	_end = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 1000, 672);
	return S_OK;
}

void End::release(void)
{
}

void End::update(void)
{
}

void End::render(void)
{
	IMAGEMANAGER->render("�׳�", getMemDC(), _end.left, _end.top);
}
