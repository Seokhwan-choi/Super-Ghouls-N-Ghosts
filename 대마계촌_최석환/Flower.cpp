#include "stdafx.h"
#include "Flower.h"
#include "Player.h"
#include "Bullet.h"
#define FRAMESPEED 5

HRESULT Flower::init(int x, int y)
{
	_time = 0;										// �ذ�� �ð� �ʱ�ȭ
	_index = 0;										// �ذ�� ������ �ε��� �ʱ�ȭ
	_count = 0;										// �ذ�� ������ ī��Ʈ �ʱ�ȭ
	_movecount = 0;									// �ذ�� ���� ī��Ʈ
	_health = 5;									// �ذ�� ü�� �ʱ�ȭ
	_gravity = 0.4f;								// �ذ�� �߷� �ʱ�ȭ
	_jumppw = 0.0f;									// �ذ�� �����Ŀ� �ʱ�ȭ
	_attack = false;								// �ذ�� �����߳�?
	_find = false;									// �ذ�� �÷��̾� ã�ҳ�?
	_show = false;									// �ذ�� �����ֳ�?
	_isDead = false;								// �ذ�� ����?
	_state = FLOWER_STATE::SHOW;					// �ذ�� ���� �ʱ�ȭ
	_pt = { x, y };									// �ذ�� ��ǥ �ʱ�ȭ
	_body = RectMakeCenter(_pt.x, _pt.y, 100, 85);	// �ذ�� ��ġ �ʱ�ȭ

	_bullet = new FlowerBullet[BULLETMAX];	// �ذ�� �Ѿ� �ʱ�ȭ
	for (int i = 0; i < BULLETMAX; i++) {
		_bullet[i].init();
	}

	image* newImage = nullptr;
	newImage = new image;
	newImage->init("images/�ذ��_����.bmp", 500, 85, 5, 1, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/�ذ��_�⺻.bmp", 500, 85, 5, 1, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/�ذ��_�̵�.bmp", 300, 85, 3, 1, true, RGB(255, 0, 255)); 
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/�ذ��_����.bmp", 200, 85, 2, 1, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/�ذ��_����.bmp", 600, 85, 6, 1, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);

	
	// ======================================================================================================
	// ########################################## �ذ�� �̹��� �ʱ�ȭ #########################################
	// ======================================================================================================
	//IMAGEMANAGER->addFrameImage("�ذ��_����", "images/�ذ��_����.bmp", 500, 85, 5, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("�ذ��_�⺻", "images/�ذ��_�⺻.bmp", 500, 85, 5, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("�ذ��_����", "images/�ذ��_����.bmp", 200, 85, 2, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("�ذ��_�̵�", "images/�ذ��_�̵�.bmp", 300, 85, 3, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("�ذ��_����", "images/�ذ��_����.bmp", 600, 85, 6, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void Flower::release(void)
{
	for (int i = 0; i < imagelist.size(); i++) {
		imagelist[i]->release();
		SAFE_DELETE(imagelist[i]);
	}
	imagelist.clear();
}

void Flower::update(class Player* player)
{
	_time++;
	if (!_isDead) {
		_pt.y -= _jumppw;
		_jumppw -= _gravity;
		// �÷��̾�� �ذ���� �Ÿ��� Ȯ��
		// �÷��̾ �������� ������ ������, true
		if (_find == false) {
			_find = checkPlayer(player->Getpt());
		}
		if (_find) {
			if (_state != FLOWER_STATE::SHOW) {
				// ����� ������ ������ �� �浹 ����
				_crush = true;
				float x = this->_pt.x - player->Getpt().x;
				float y = this->_pt.y - player->Getpt().y;
				// �÷��̾���� �Ÿ��� Ȯ��
				// �Ÿ��� ��������� �����Ѵ�.
				if ((sqrtf((x*x) + (y * y)) < 450) && _attack == false) {
					_state = FLOWER_STATE::ATTACK;
				}
			}
		}
		int count = 0;
		if (_attack == true) {
			if (_time % 250 == 0) {
				// �ذ�� �Ѿ��� ��� false�� �Ǿ����� Ȯ��
				for (int i = 0; i < FLOWERBULLET; i++)
				{
					if (_bullet[i].GetFire()) break;
					count++;
				}
				// �ذ�� �Ѿ��� ��� false �̸�
				if (count == 3) {
					_attack = false;
				}
			}
		}

		if (_health < 0) {
			_state = FLOWER_STATE::DIE;
		}

		if (_find) {
			switch (_state) {
			case FLOWER_STATE::SHOW:
				_count++;
				if (_count % (FRAMESPEED * 2) == 0) {
					_index++;
					if (_index > 4) {
						_index = 0;
					}
					imagelist[(int)FLOWER_STATE::SHOW]->setFrameX(_index);
					if (_index == 4) {
						_state = FLOWER_STATE::IDLE;
					}
				}
				break;
			case FLOWER_STATE::IDLE:
				_count++;
				if (_count % FRAMESPEED == 0) {
					_index++;
					if (_index > 4) {
						_index = 0;
					}
					imagelist[(int)FLOWER_STATE::IDLE]->setFrameX(_index);
					if (_index == 4) {
						_state = FLOWER_STATE::MOVE_LEFT;
					}
				}
				break;
			case FLOWER_STATE::MOVE_LEFT:
				_count++;
				if (_count % FRAMESPEED == 0) {
					_pt.x -= 5; _movecount -= 5;
					_index++;
					if (_index > 2) {
						_index = 0;
					}
					imagelist[(int)FLOWER_STATE::MOVE_LEFT]->setFrameX(_index);
					if (_movecount < -150) {
						_state = FLOWER_STATE::MOVE_RIGHT;
					}
				}
				break;
			case FLOWER_STATE::MOVE_RIGHT:
				_count++;
				if (_count % FRAMESPEED == 0) {
					_pt.x += 5; _movecount += 5;
					_index++;
					if (_index > 2) {
						_index = 0;
					}
					imagelist[(int)FLOWER_STATE::MOVE_LEFT]->setFrameX(_index);
					if (_movecount > 150) {
						_state = FLOWER_STATE::MOVE_LEFT;
					}
				}
				break;
			case FLOWER_STATE::ATTACK:
				_count++;
				if (_count % FRAMESPEED == 0) {
					_index++;
					if (_index > 2) {
						_index = 0;
					}
					imagelist[(int)FLOWER_STATE::ATTACK-1]->setFrameX(_index);
					if (_index == 2) {
						_attack = true;
						for (int i = 0; i < FLOWERBULLET; i++)
						{
							if (_bullet[i].GetFire()) continue;
							POINT _impt = { _pt.x, _pt.y - 50 };
							_bullet[i].Fire(_impt);
						}
						_state = FLOWER_STATE::IDLE;
						_bullet[0].SetAngle(PI / 3.0f);
						_bullet[1].SetAngle(PI / 2.0f);
						_bullet[2].SetAngle((PI / 3.0f) * 2.0f);
					}
				}
				break;
			case FLOWER_STATE::DIE:
				_crush = false;
				_count++;
				if (_count % FRAMESPEED == 0) {
					_index++;
					if (_index > 5) {
						_index = 0;
					}
					imagelist[(int)FLOWER_STATE::DIE-1]->setFrameX(_index);
					if (_index == 5) {
						_isDead = true;
						_find = false;
						UIMANAGER->SetScore(UIMANAGER->GetScore() + 300);
					}
				}
				break;
			}
		}

		// ==========================================================================================
		// ############################## �ذ�� �ȼ� �浹 ó�� ########################################
		// ==========================================================================================
		_probeY = _botpt.y + 5;
		for (int i = _probeY - 5; i <= _probeY; ++i)
		{
			//�ش� �̹����� HDC�������� x,i�� �ȼ��� �д´�. 
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("�ȼ�")->getMemDC(), _botpt.x, i);
			//COLORREF�� �����Ϳ��� �� rgb���� �޾ƿ´�. 
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			//rgb������ ����Ÿ�� �ƴ϶�� 
			if ((r == 222 && g == 222 && b == 0))
			{
				_jumppw = 0.0f;
				_pt.y = i - 33;
				break;
			}
		}
		if (_state == FLOWER_STATE::MOVE_LEFT) {
			_probeX = _leftpt.x - 5;
			for (int i = _probeX; i <= _probeX + 5; ++i)
			{
				//�ش� �̹����� HDC�������� x,i�� �ȼ��� �д´�. 
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("�ȼ�")->getMemDC(), i, _leftpt.y);
				//COLORREF�� �����Ϳ��� �� rgb���� �޾ƿ´�. 
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);
				//rgb������ �˻��Ѵ�.
				if ((r == 222 && g == 222 && b == 0))
				{
					_pt.x = i + 42;
					break;
				}
			}
		}
		else if (_state == FLOWER_STATE::MOVE_RIGHT) {
			_probeX = _rightpt.x + 5;
			for (int i = _probeX - 5; i <= _probeX; ++i)
			{
				//�ش� �̹����� HDC�������� x,i�� �ȼ��� �д´�. 
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("�ȼ�")->getMemDC(), i, _rightpt.y);
				//COLORREF�� �����Ϳ��� �� rgb���� �޾ƿ´�. 
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);
				//rgb������ �˻��Ѵ�. 
				if ((r == 222 && g == 222 && b == 0))
				{
					_pt.x = i - 42;
					break;
				}
			}
		}

		// ==========================================================================================
		// ############################ �ذ�� �÷��̾� �Ѿ� �浹 ó�� ##################################
		// ==========================================================================================
		for (int i = 0; i < BULLETMAX; i++) {
			RECT _imrc;
			if (!player->GetBullet()[i].getFire()) continue;
			if (IntersectRect(&_imrc, &_body, &player->GetBullet()[i].getRect()) && _crush == true)
			{
				// �÷��̾��� �Ѿ˿� ���̷����� ������ ü�°��� --
				_health--;
				// �浹�� �Ѿ��� false ó�� ���ش�.
				player->GetBullet()[i].setFire(false);
			}
		}

		// ==========================================================================================
		// ############################ �ذ�� �Ѿ� �÷��̾� �浹 ó�� ##################################
		// ==========================================================================================
		for (int i = 0; i < FLOWERBULLET; i++) {
			RECT _imrc;
			if (!_bullet[i].GetFire()) continue;
			if (IntersectRect(&_imrc, &player->GetCrush(), &_bullet[i].GetRect()) && player->GetisCrush())
			{
				if (!player->GetHit()) player->hitPlayer();
			}
		}
		// ==========================================================================================
		// ############################ �ذ�� �÷��̾� �浹 ó�� #######################################
		// ==========================================================================================
		RECT _imrc;
		if (IntersectRect(&_imrc, &player->GetCrush(), &_body) && player->GetisCrush()) {
			if (!player->GetHit()) player->hitPlayer();
		}
		
	}

	for (int i = 0; i < FLOWERBULLET; i++) {
		if (!_bullet[i].GetFire()) continue;
		_bullet[i].update();
	}


	_body = RectMakeCenter(_pt.x, _pt.y, 100, 85);
	// #################  RECT ���� ##########################################################
	_botpt = { _body.left + ((_body.right - _body.left) / 2) , _body.bottom - 14 };
	_leftpt = { _body.left + 15, _body.bottom - 42 };
	_rightpt = { _body.right - 15, _body.bottom - 42 };
	_bot = RectMakeCenter(_botpt.x, _botpt.y, 5, 10);
	_rightCheck = RectMakeCenter(_rightpt.x, _rightpt.y, 10, 5);
	_leftCheck = RectMakeCenter(_leftpt.x, _leftpt.y, 10, 5);
	// #################  RECT ���� ##########################################################
}


void Flower::render(void)
{
	//�÷��̾ ���������� ī�޶� �����ǥ�� ����
	RECT bodyRC;
	bodyRC.left = _body.left - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.top = _body.top - Camera::getSingleton()->GetCameraRect().top;
	bodyRC.right = _body.right - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.bottom = _body.bottom - Camera::getSingleton()->GetCameraRect().top;
	if (_find) {
		switch (_state)
		{
		case FLOWER_STATE::SHOW:
			imagelist[(int)FLOWER_STATE::SHOW]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case FLOWER_STATE::IDLE:
			imagelist[(int)FLOWER_STATE::IDLE]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case FLOWER_STATE::MOVE_LEFT:
			imagelist[(int)FLOWER_STATE::MOVE_LEFT]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case FLOWER_STATE::MOVE_RIGHT:
			imagelist[(int)FLOWER_STATE::MOVE_LEFT]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case FLOWER_STATE::ATTACK:
			imagelist[(int)FLOWER_STATE::ATTACK-1]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case FLOWER_STATE::DIE:
			imagelist[(int)FLOWER_STATE::DIE-1]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		}
	}

	for (int i = 0; i < BULLETMAX; i++) {
		if (!_bullet[i].GetFire()) continue;
		_bullet[i].render();
	}
}

bool Flower::checkPlayer(POINT playerpt)
{
	float x = this->_pt.x - playerpt.x;
	float y = this->_pt.y - playerpt.y;
	// �÷��̾�� �ذ���� �Ÿ��� 150 ���� �۾�����
	// �ذ�� ����
	if (sqrtf((x*x) + (y * y)) < 350) {
		return true;
	}
	else {
		return false;
	}
}
