#include "stdafx.h"
#include "Bird.h"
#include "Player.h"
#include "Bullet.h"
#define FRAMESPEED 5

HRESULT Bird::init(int x, int y)
{

	_index = 0;													// ������ ������ �ε��� �ʱ�ȭ
	_count = 0;													// ������ ������ ī��Ʈ �ʱ�ȭ
	_isLeft = true;												// ������ ��,�� �ʱ�ȭ
	_isDead = false;											// ������ �׾���?
	_find = false;												// �������� �÷��̾� ã�ҳ�?
	_crush = true;												// ������ �浹����
	_health = 5;												// ������ ü��
	_gravity = 0.3f;											// ������ �߷� �ʱ�ȭ
	_jumppw = 6.0f;												// ������ �����Ŀ� �ʱ�ȭ
	_pt = { x, y };												// ������ ��ǥ �ʱ�ȭ
	_state = (BIRD_STATE)RND->range(2);							// ������ ���� ���� �ʱ�ȭ
	_body = RectMakeCenter(_pt.x, _pt.y, 125, 100);				// ������ RECT �ʱ�ȭ
	_crushRect = RectMakeCenter(_pt.x, _pt.y + 25, 100, 50);	// ������ �浹 RECT �ʱ�ȭ
	_birdfeather = new Birdfeather[FEATHERMAX];					// ������ ���� �ʱ�ȭ
	for (int i = 0; i < FEATHERMAX; i++) {
		_birdfeather[i].init();
	}

	image* newImage = nullptr;
	newImage = new image;
	newImage->init("images/������_�⺻��.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/������_�⺻����.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/������_���.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/������_����.bmp", 750, 200, 6, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/������_����.bmp", 125, 200, 1, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/������_����.bmp", 750, 200, 6, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);







	// ====================================================================================================================
	// ############################################ ������ �̹��� �ʱ�ȭ #####################################################
	// ====================================================================================================================
	//IMAGEMANAGER->addFrameImage("������_�⺻���ƿ���", "images/������_�⺻���ƿ���.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("������_�⺻����", "images/������_�⺻����.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("������_�⺻��", "images/������_�⺻��.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("������_���", "images/������_���.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("������_����", "images/������_����.bmp", 750, 200, 6, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("������_����", "images/������_����.bmp", 125, 200, 1, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("������_����", "images/������_����.bmp", 750, 200, 6, 2, true, RGB(255, 0, 255));
	return S_OK;
}

void Bird::release(void)
{
	for (int i = 0; i < imagelist.size(); i++) {
		imagelist[i]->release();
		SAFE_DELETE(imagelist[i]);
	}
	imagelist.clear();
}

void Bird::update(class Player* player)
{
	// �÷��̾�� �������� �Ÿ��� Ȯ��
	// �÷��̾ �������� ������ ������, true
	if (!_isDead) 
	{
		float x = this->_pt.x - player->Getpt().x;
		float y = this->_pt.y - player->Getpt().y;
		// �÷��̾���� �Ÿ��� Ȯ��
		// �Ÿ��� ��������� �����Ѵ�.
		if ((sqrtf((x*x) + (y * y)) < 350) && _find == false ){//&& (_state == BIRD_STATE::IDLE || _state == BIRD_STATE::IDLEJUMP || _state == BIRD_STATE::IDLETURN)) {
			_find = true; _state = BIRD_STATE::JUMP;
		}

		if (_health < 0){// && _state != BIRD_STATE::DIE) {
			_state = BIRD_STATE::DIE;
		}
			
		switch (_state)
		{
		case BIRD_STATE::IDLE:
			_count++;
			imagelist[(int)BIRD_STATE::IDLE]->setFrameY(1);
			
			if (_count % (FRAMESPEED*2) == 0) {
				_index++;
				if (_index > 5) {
					_index = 0;
				}
				imagelist[(int)BIRD_STATE::IDLE]->setFrameX(_index);
				
				if (_index == 5) {
					_state = (BIRD_STATE)RND->range(2);
				}
			}
			break;
		case BIRD_STATE::IDLEJUMP:
			_count++;
			imagelist[(int)BIRD_STATE::IDLEJUMP]->setFrameY(1);
			if (_count % (FRAMESPEED*2) == 0) {
				_index++;
				if (_index > 5) {
					_index = 0;
				}
				imagelist[(int)BIRD_STATE::IDLEJUMP]->setFrameY(_index);
				if (_index == 5) {
					_state = (BIRD_STATE)RND->range(2);
				}
			}
			break;
		//case BIRD_STATE::IDLETURN:
		//	_count++;
		//	IMAGEMANAGER->findImage("������_�⺻���ƿ���")->setFrameY(1);
		//	if (_count % (FRAMESPEED*2) == 0) {
		//		_index++;
		//		if (_index > 5) {
		//			_index = 0;
		//		}
		//		IMAGEMANAGER->findImage("������_�⺻���ƿ���")->setFrameX(_index);
		//		if (_index == 5) {
		//			_state = (BIRD_STATE)RND->range(3);
		//		}
		//	}
		//	break;
		case BIRD_STATE::JUMP:
			_count++;
			_pt.y -= _jumppw;
			_jumppw -= _gravity;
			imagelist[(int)BIRD_STATE::JUMP]->setFrameY(1);
			if (_count % FRAMESPEED == 0) {
				_index++; _pt.x -= 1;
				if (_index > 3) {
					_index = 0;
				}
				imagelist[(int)BIRD_STATE::JUMP]->setFrameX(_index);
			}
			if (player->GetCrush().top  < _pt.y ) {
				_state = BIRD_STATE::FLY;
			}
			break;
		case BIRD_STATE::FLY:
			_count++;
			_jumppw = 0.0f;
			_pt.x -= 5;
			imagelist[(int)BIRD_STATE::FLY]->setFrameY(1);
			if (_count % FRAMESPEED == 0) {
				_index++;
				if (_index > 5) {
					_index = 0;
				}
				imagelist[(int)BIRD_STATE::FLY]->setFrameX(_index);
				if (_index == 5) {
					_index--;
				}
			}
			break;
		case BIRD_STATE::HIT:
			_count++;
			if (_count % FRAMESPEED == 10) {
				imagelist[(int)BIRD_STATE::HIT]->setFrameY(1);
				imagelist[(int)BIRD_STATE::HIT]->setFrameY(0);
				_state = BIRD_STATE::DIE;
			}
			break;
		case BIRD_STATE::DIE:
			_crush = false;
			_count++;
			imagelist[(int)BIRD_STATE::DIE]->setFrameY(1);
			if (_count % (FRAMESPEED*2) == 0) {
				_index++;
				if (_index > 5) {
					_index = 0;
				}
				imagelist[(int)BIRD_STATE::DIE]->setFrameX(_index);
				if (_index == 5) {
					_isDead = true;
					for (int i = 0; i < FEATHERMAX; i++)
					{
						if (_birdfeather[i].GetCheck()) continue;
						_birdfeather[i].Boom(_pt);
					}
					UIMANAGER->SetScore(UIMANAGER->GetScore() + 500);
				}
			}
			break;
		}

		// ==========================================================================================
		// ############################ ������ �÷��̾� �Ѿ� �浹 ó�� ##################################
		// ==========================================================================================
		for (int i = 0; i < BULLETMAX; i++) {
			RECT _imrc;
			if (!player->GetBullet()[i].getFire()) continue;
			if (IntersectRect(&_imrc, &_crushRect, &player->GetBullet()[i].getRect()) && _crush == true)
			{
				// �÷��̾��� �Ѿ˿� ���̷����� ������ ü�°��� --
				_health--;
				// �浹�� �Ѿ��� false ó�� ���ش�.
				player->GetBullet()[i].setFire(false);
			}
		}

		// ==========================================================================================
		// ############################ ������ �÷��̾� �浹 ó�� #######################################
		// ==========================================================================================
		RECT _imrc;
		if (IntersectRect(&_imrc, &player->GetCrush(), &_crushRect) && player->GetisCrush())
		{
			if (!player->GetHit()) player->hitPlayer();
		}
		
	}
	
	for (int i = 0; i < FEATHERMAX; i++)
	{
		if (!_birdfeather[i].GetCheck()) continue;
		_birdfeather[i].update();
	}
	
	_crushRect = RectMakeCenter(_pt.x, _pt.y + 25, 100, 50);	// ������ �浹 RECT �ʱ�ȭ
	_body = RectMakeCenter(_pt.x, _pt.y, 125, 100);				// ������ RECT �ʱ�ȭ
}

void Bird::render(void)
{
	RECT bodyRC;
	bodyRC.left = _body.left - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.top = _body.top - Camera::getSingleton()->GetCameraRect().top;
	bodyRC.right = _body.right - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.bottom = _body.bottom - Camera::getSingleton()->GetCameraRect().top;
	if (!_isDead) {
		switch (_state)
		{
		case BIRD_STATE::IDLE:
			imagelist[(int)BIRD_STATE::IDLE]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			
			break;
		case BIRD_STATE::IDLEJUMP:
			imagelist[(int)BIRD_STATE::IDLEJUMP]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		//case BIRD_STATE::IDLETURN:
		//	IMAGEMANAGER->frameRender("������_�⺻���ƿ���", getMemDC(), bodyRC.left, bodyRC.top);
		//	break;
		case BIRD_STATE::JUMP:
			imagelist[(int)BIRD_STATE::JUMP]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case BIRD_STATE::FLY:
			imagelist[(int)BIRD_STATE::FLY]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case BIRD_STATE::HIT:
			imagelist[(int)BIRD_STATE::HIT]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case BIRD_STATE::DIE:
			imagelist[(int)BIRD_STATE::DIE]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		}
	}
	else {
		for (int i = 0; i < FEATHERMAX; i++)
		{
			if (!_birdfeather[i].GetCheck()) continue;
			_birdfeather[i].render();
		}
	}
	if (_isDebug)
	{
		//FrameRect(getMemDC(), bodyRC, RGB(255, 0, 255));
		FrameRect(getMemDC(), _crushRect, RGB(255, 0, 0));
		FrameRect(getMemDC(), _body, RGB(255, 0, 0));
	}
}
