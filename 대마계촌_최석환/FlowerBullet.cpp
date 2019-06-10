#include "stdafx.h"
#include "FlowerBullet.h"

HRESULT FlowerBullet::init(void)
{
	_gravity = 0.0f;				// ÇØ°ñ²É ÃÑ¾Ë Áß·Â ÃÊ±âÈ­
	_count = 0;						// ÇØ°ñ²É ÃÑ¾Ë ÇÁ·¹ÀÓ Ä«¿îÆ® ÃÊ±âÈ­
	_index = 0;						// ÇØ°ñ²É ÃÑ¾Ë ÇÁ·¹ÀÓ ÀÎµ¦½º ÃÊ±âÈ­
	_time = 0;						// ÇØ°ñ²É ÃÑ¾Ë Áß·Â ½Ã°£ ÃÊ±âÈ­
	_angle = 0.0f;					// ÇØ°ñ²É ÃÑ¾Ë °¢µµ ÃÊ±âÈ­
	_state = FlowerBullet::LEFT;	// ÇØ°ñ²É ÃÑ¾Ë »óÅÂ ÃÊ±âÈ­
	_fire = false;					// ÇØ°ñ²É ÃÑ¾Ë ¹ß»ç µÆ³Ä ?

	// ÇØ°ñ²É ÃÑ¾Ë ÀÌ¹ÌÁö ÃÊ±âÈ­
	IMAGEMANAGER->addFrameImage("ÇØ°ñ²É_ÃÑ¾Ë", "images/ÇØ°ñ²É_ÃÑ¾Ë.bmp", 100, 100, 2, 2, true, RGB(255, 0, 255));
	return S_OK;
}

void FlowerBullet::release(void)
{

}

void FlowerBullet::update(void)
{
	this->move();

	switch (_state)
	{
	case FlowerBullet::LEFT:
		_count++;
		IMAGEMANAGER->findImage("ÇØ°ñ²É_ÃÑ¾Ë")->setFrameY(1);
		if (_count % 5 == 0) {
			_index++;
			if (_index > 1) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("ÇØ°ñ²É_ÃÑ¾Ë")->setFrameX(_index);
			if (_index == 1) {
				_state = FlowerBullet::RIGHT;
			}
		}
		break;
	case FlowerBullet::RIGHT:
		_count++; 
		IMAGEMANAGER->findImage("ÇØ°ñ²É_ÃÑ¾Ë")->setFrameY(0);
		if (_count % 5 == 0) {
			_index++;
			if (_index > 1) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("ÇØ°ñ²É_ÃÑ¾Ë")->setFrameX(_index);
			if (_index == 1) {
				_state = FlowerBullet::LEFT;
			}
		}
		break;
	}

	if ( _pt.y > WINSIZEY) {
		this->init();
	}
}

void FlowerBullet::render(void)
{
	RECT RC;
	RC.left = _rc.left - Camera::getSingleton()->GetCameraRect().left;
	RC.top = _rc.top - Camera::getSingleton()->GetCameraRect().top;
	RC.right = _rc.right - Camera::getSingleton()->GetCameraRect().left;
	RC.bottom = _rc.bottom - Camera::getSingleton()->GetCameraRect().top;
	IMAGEMANAGER->frameRender("ÇØ°ñ²É_ÃÑ¾Ë", getMemDC(), RC.left, RC.top);
}

void FlowerBullet::move()
{
	_gravity += 0.3f;
	_pt.x += cosf(_angle)* 10 ;
	_pt.y += -sinf(_angle)* 10 + _gravity;
	_rc = RectMakeCenter(_pt.x, _pt.y, 50, 50);
}

void FlowerBullet::Fire(POINT pt)
{
	_fire = true;
	this->_pt = pt;
	_rc = RectMakeCenter(_pt.x, _pt.y, 50, 50);
}
