#include "stdafx.h"
#include "FlowerBullet.h"

HRESULT FlowerBullet::init(void)
{
	_gravity = 0.0f;				// �ذ�� �Ѿ� �߷� �ʱ�ȭ
	_count = 0;						// �ذ�� �Ѿ� ������ ī��Ʈ �ʱ�ȭ
	_index = 0;						// �ذ�� �Ѿ� ������ �ε��� �ʱ�ȭ
	_time = 0;						// �ذ�� �Ѿ� �߷� �ð� �ʱ�ȭ
	_angle = 0.0f;					// �ذ�� �Ѿ� ���� �ʱ�ȭ
	_state = FlowerBullet::LEFT;	// �ذ�� �Ѿ� ���� �ʱ�ȭ
	_fire = false;					// �ذ�� �Ѿ� �߻� �Ƴ� ?

	// �ذ�� �Ѿ� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("�ذ��_�Ѿ�", "images/�ذ��_�Ѿ�.bmp", 100, 100, 2, 2, true, RGB(255, 0, 255));
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
		IMAGEMANAGER->findImage("�ذ��_�Ѿ�")->setFrameY(1);
		if (_count % 5 == 0) {
			_index++;
			if (_index > 1) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("�ذ��_�Ѿ�")->setFrameX(_index);
			if (_index == 1) {
				_state = FlowerBullet::RIGHT;
			}
		}
		break;
	case FlowerBullet::RIGHT:
		_count++; 
		IMAGEMANAGER->findImage("�ذ��_�Ѿ�")->setFrameY(0);
		if (_count % 5 == 0) {
			_index++;
			if (_index > 1) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("�ذ��_�Ѿ�")->setFrameX(_index);
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
	IMAGEMANAGER->frameRender("�ذ��_�Ѿ�", getMemDC(), RC.left, RC.top);
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
