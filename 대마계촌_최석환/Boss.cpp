#include "stdafx.h"
#include "Boss.h"

HRESULT Boss::init(void)
{
	_health = 10;
	_index = 0;
	_count = 0;
	_isDead = false;
	_state = (BOSS_STATE)RND->range(2);
	_body = RectMakeCenter(8230, 415, 334, 322);
	IMAGEMANAGER->addFrameImage("�����⺻", "boss/�׽�Ʈ.bmp", 10464, 322, 32, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "boss/�׽�Ʈ3.bmp", 5344, 322, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "boss/�׽�Ʈ2.bmp", 9209, 322, 26, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void Boss::release(void)
{
}

void Boss::update(class Player* player)
{
	if (!_isDead) {
		switch (_state)
		{
		
		case Boss::IDLE:
			_count++;
			IMAGEMANAGER->findImage("�����⺻")->setFrameY(0);
			if (_count % 5 == 0) {
				_index++;
				if (_index > 31) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("�����⺻")->setFrameX(_index);
				if (_index == 31) {
					_state = (BOSS_STATE)RND->range(2);
				}
			}
			break;
		case Boss::BLOOD:
			_count++;
			IMAGEMANAGER->findImage("������")->setFrameY(0);
			if (_count % 5 == 0) {
				_index++;
				if (_index > 25) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("������")->setFrameX(_index);
				if (_index == 25) {
					_state = (BOSS_STATE)RND->range(2);
				}
			}
			break;
		case Boss::DIE:
			_count++;
			IMAGEMANAGER->findImage("��������")->setFrameY(0);
			if (_count % 5 == 0) {
				_index++;
				if (_index > 15) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("��������")->setFrameX(_index);
				if (_index == 15) {
					_isDead = true;
					UIMANAGER->SetScore(UIMANAGER->GetScore() + 5000);
				}
			}
			break;
		}
		RECT _imrc;
		for (int i = 0; i < BULLETMAX; i++) {
			if (!player->GetBullet()[i].getFire()) continue;
			if (IntersectRect(&_imrc, &_body, &player->GetBullet()[i].getRect()))
			{
				_health--;
				player->GetBullet()[i].setFire(false);
			}
		}

		if (IntersectRect(&_imrc, &_body, &player->GetCrush()) && player->GetisCrush())
		{
			if (!player->GetHit()) player->hitPlayer();
		}

		if (_health < 0 && _state != BOSS_STATE::DIE) {
			_state = BOSS_STATE::DIE;
		}
	}
	
}

void Boss::render(void)
{
	RECT bodyRC;
	bodyRC.left = _body.left - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.top = _body.top - Camera::getSingleton()->GetCameraRect().top;
	bodyRC.right = _body.right - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.bottom = _body.bottom - Camera::getSingleton()->GetCameraRect().top;
	switch (_state)
	{
	case Boss::IDLE:
		IMAGEMANAGER->frameRender("�����⺻",getMemDC(), bodyRC.left, bodyRC.top);
		break;
	case Boss::BLOOD:
		IMAGEMANAGER->frameRender("������", getMemDC(), bodyRC.left, bodyRC.top);
		break;
	case Boss::DIE:
		IMAGEMANAGER->frameRender("��������", getMemDC(), bodyRC.left, bodyRC.top);
		break;
	}
}
