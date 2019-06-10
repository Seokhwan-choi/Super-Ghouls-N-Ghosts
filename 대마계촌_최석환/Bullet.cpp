#include "stdafx.h"
#include "Bullet.h"
#define BULLETSPPED 8


HRESULT Bullet::init(void)
{
	_fire = false; _time = 0;
	IMAGEMANAGER->addImage("왼창", "images/왼창.bmp", 51, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("오창", "images/오창.bmp", 51, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("위창", "images/위창.bmp", 16, 51, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아창", "images/아창.bmp", 16, 51, true, RGB(255, 0, 255));
	return S_OK;
}

void Bullet::release(void)
{
}

void Bullet::update(void)
{
	_time++;
	this->move();
}

void Bullet::render(void)
{
	RECT RC;
	RC.left = _rc.left - Camera::getSingleton()->GetCameraRect().left;
	RC.top = _rc.top - Camera::getSingleton()->GetCameraRect().top;
	RC.right = _rc.right - Camera::getSingleton()->GetCameraRect().left;
	RC.bottom = _rc.bottom - Camera::getSingleton()->GetCameraRect().top;
	switch (_way)
	{
	case WAY::LEFT:
		IMAGEMANAGER->render("왼창", getMemDC(), RC.left, RC.top);
		break;
	case WAY::RIGHT:
		IMAGEMANAGER->render("오창", getMemDC(), RC.left, RC.top);
		break;
	case WAY::UP:
		IMAGEMANAGER->render("위창", getMemDC(), RC.left, RC.top);
		break;
	case WAY::DOWN:
		IMAGEMANAGER->render("아창", getMemDC(), RC.left, RC.top);
		break;
	}
}

void Bullet::Fire(POINT pt)
{
	_fire = true;
	if (_way == WAY::LEFT || _way == WAY::RIGHT) {
		_rc = RectMakeCenter(pt.x, pt.y, 51, 17);
	}
	else {
		_rc = RectMakeCenter(pt.x, pt.y, 16, 51);
	}
}

void Bullet::move()
{
	switch (_way) 
	{
	case WAY::LEFT:
		_rc.left -= BULLETSPPED;
		_rc.right -= BULLETSPPED;
		break;
	case WAY::RIGHT:
		_rc.left += BULLETSPPED;
		_rc.right += BULLETSPPED;
		break;
	case WAY::UP:
		_rc.top -= BULLETSPPED;
		_rc.bottom -= BULLETSPPED;
		break;
	case WAY::DOWN:
		_rc.top += BULLETSPPED;
		_rc.bottom += BULLETSPPED;
		break;
	}

	if (_time > 125) {
		_fire = false;
		_time = 0;
	}

}
