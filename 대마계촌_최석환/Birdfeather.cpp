#include "stdafx.h"
#include "Birdfeather.h"

HRESULT Birdfeather::init(void)
{
	_gravity = 0.1f;
	_count = 0;
	_index = 0;
	_check = false;
	IMAGEMANAGER->addFrameImage("������_����", "images/������_����.bmp", 90, 30, 3, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void Birdfeather::release(void)
{


}

void Birdfeather::update(void)
{
	_count++;
	this->move();
	IMAGEMANAGER->findImage("������_����")->setFrameY(0);
	if (_count % 15 == 0) {
		_index++;
		if (_index > 2) {
			_index = 0;
		}
		IMAGEMANAGER->findImage("������_����")->setFrameX(_index);
	}
}

void Birdfeather::render(void)
{
	RECT _bodyRC;
	_bodyRC.left = _body.left - Camera::getSingleton()->GetCameraRect().left;
	_bodyRC.top = _body.top - Camera::getSingleton()->GetCameraRect().top;
	_bodyRC.right = _body.right - Camera::getSingleton()->GetCameraRect().left;
	_bodyRC.bottom = _body.bottom - Camera::getSingleton()->GetCameraRect().top;
	IMAGEMANAGER->frameRender("������_����",getMemDC(), _bodyRC.left, _bodyRC.top);

	
}

void Birdfeather::Boom(POINT pt)
{
	_check = true;
	_pt = pt;
	_pt.x += RND->range(-100, 100);
	_pt.y += RND->range(-50, 50);
}

void Birdfeather::move()
{
	// ������ 2.5�� ���ӵǰ� �������.
	_pt.y += _gravity;
	_gravity += 0.1f;
	if (_count > 250) {
		_check = false;
	}
	_body = RectMakeCenter(_pt.x, _pt.y, 30, 30);
}
