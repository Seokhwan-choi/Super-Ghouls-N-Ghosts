#include "stdafx.h"
#include "skeleton.h"
#include "Player.h"
#include "Bullet.h"
#include <math.h>
#define FRAMESPEED 10

HRESULT skeleton::init(int x, int y, SKE_STATE state)
{
	_gravity = 0.4f;									// ���̷��� �߷� �ʱ�ȭ
	_jumppw = 0.0f;										// ���̷��� �����Ŀ� �ʱ�ȭ
	this->_state = state;								// ���̷��� ���� �ʱ�ȭ
	//this->_isLeft = isLeft;							// ���̷��� ��,�� �ʱ�ȭ
	_attack = false;									// ���̷��� ���� �ʱ�ȭ
	_crush = false;										// ���̷��� �浹���� �ʱ�ȭ
	_show = false;										// ���̷��� �����ش�.
	_find = false;										// ���̷����� �÷��̾ ã�ҳ�?
	_isDead = false;									// ���̷��� �׾���?
	_isHit = false;										// ���̷��� �¾ҳ�?
	_attacktime = 0;									// ���̷��� ���� ��Ÿ��
	_count = 0;											// ���̷��� ������ ī��Ʈ �ʱ�ȭ
	_index = 0;											// ���̷��� ������ �ε��� �ʱ�ȭ
	_health = 5;										// ���̷��� ü�� �ʱ�ȭ
	_pt = { x, y };										// ���̷��� �߽���ǥ �ʱ�ȭ
	_body = RectMakeCenter(_pt.x, _pt.y, 130, 100);		// ���̷��� ��ġ �ʱ�ȭ
	

	image* newImage = nullptr;
	newImage = new image;
	newImage->init("images/���̷���_�ȱ�.bmp", 520, 200, 4, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/���̷���_����.bmp", 390, 200, 3, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/���̷���_���ö����.bmp", 1170, 100, 9, 1, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/���̷���_�ٴڿö����.bmp", 1170, 100, 9, 1, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/���̷���_������.bmp", 910, 200, 7, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/���̷���_����.bmp", 130, 200, 1, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/���̷���_����.bmp", 600, 200, 6, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);

	// ================================================================================================================
	// ############################################## ���̷��� �̹��� �ʱ�ȭ ##############################################
	// ================================================================================================================
	//IMAGEMANAGER->addFrameImage("���̷���_�ȱ�", "images/���̷���_�ȱ�.bmp", 520, 200, 4, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("���̷���_����", "images/���̷���_����.bmp", 390, 200, 3, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("���̷���_���ö����", "images/���̷���_���ö����.bmp", 1170, 100, 9, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("���̷���_�ٴڿö����", "images/���̷���_�ٴڿö����.bmp", 1170, 100, 9, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("���̷���_������", "images/���̷���_������.bmp", 910, 200, 7, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("���̷���_����", "images/���̷���_����.bmp", 130, 200, 1, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("���̷���_����", "images/���̷���_����.bmp", 600, 200, 6, 2, true, RGB(255, 0, 255));

	return S_OK;
}

void skeleton::release(void)
{
	for (int i = 0; i < imageList.size(); i++) {
		imageList[i]->release();
		SAFE_DELETE(imageList[i]);
	}
	imageList.clear();
}

void skeleton::update(class Player* player)
{
	_pt.y -= _jumppw;
	_jumppw -=_gravity;
	if (!_isDead) 
	{
		// �÷��̾�� ���̷����� �Ÿ��� Ȯ��
		// �÷��̾ �������� ������ ������, true
		if (_find == false) {
			_find = checkPlayer(player->Getpt());
		}
		if (_find) {
			// �÷��̾ ��� �ٶ󺸰� ���ش�.
			if (this->_pt.x > player->Getpt().x) {
				_isLeft = true;
			}
			else {
				_isLeft = false;
			}
			// ���̷��� ����� �����ش�.
			_show = true;
			// ���̷��� �ʱ� ���¿� ���� ���� ����� �ٸ���.
			if (_state == SKE_STATE::IDLE1 ||
				_state == SKE_STATE::IDLE2 || _state == SKE_STATE::IDLE3) {
				showskeleton(_state);
			}
			else {
				// ����� ������ ������ �� �浹 ����
				_crush = true;
				float x = this->_pt.x - player->Getpt().x;
				float y = this->_pt.y - player->Getpt().y;
				// �÷��̾���� �Ÿ��� Ȯ��
				// �Ÿ��� ��������� �����Ѵ�.
				if ((sqrtf((x*x) + (y * y)) < 100) && _attack == false) {
					_index = -1; _attack = true;
					_state = SKE_STATE::ATTACK;
				}
				else if (_state != SKE_STATE::ATTACK) {
					_state = SKE_STATE::WALK;
				}
			}
		}
		if (_attack == true) {
			_attacktime++;
			if (_attacktime % 100 == 0) {
				_attack = false;
			}
		}
		// ==========================================================================================
		// ############################## ���̷��� �ȼ� �浹 ó�� ######################################
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
				_pt.y = i - 40;
				break;
			}
		}
		if (_isLeft) {
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
					_pt.x = i;
					break;
				}
			}
		}
		else {
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
					_pt.x = i;
					break;
				}
			}
		}
		// ==========================================================================================
		// ########################### ���̷��� �÷��̾��Ѿ� �浹 ó�� ###################################
		// ==========================================================================================
		for (int i = 0; i < BULLETMAX; i++) {
			RECT _imrc;
			if (!player->GetBullet()[i].getFire()) continue;
			if (IntersectRect(&_imrc, &_crushCheck, &player->GetBullet()[i].getRect()) && _crush == true)
			{
				// �÷��̾��� �Ѿ˿� ���̷����� ������ ü�°��� --
				_health--;
				// �浹�� �Ѿ��� false ó�� ���ش�.
				player->GetBullet()[i].setFire(false);
			}
		}
		if (_health < 0 ){//&& _state != SKE_STATE::DEATH) {
			_state = SKE_STATE::DEATH;
		}
		// ==========================================================================================
		// ########################### ���̷��� �÷��̾� �浹 ó�� ######################################
		// ==========================================================================================
		RECT _imrc;
		if (IntersectRect(&_imrc, &_crushCheck, &player->GetCrush()) && player->GetisCrush() && _crush == true)
		{
			if (!player->GetHit()) player->hitPlayer();
		}

		switch (_state)
		{
		case SKE_STATE::ATTACK:
			if (_isLeft) 
			{
				imageList[ImageAttack]->setFrameY(1);
				
				_count++;
				if (_count % (FRAMESPEED * 2) == 0) {
					_index++;
					if (_index > 2) {
						_index = 0;
					}
					cout << _index << endl;
					imageList[ImageAttack]->setFrameX(_index);
					
					if (_index == 2) {
						RECT _imrc;
						if (IntersectRect(&_imrc, &_body, &player->GetCrush()) && player->GetisCrush() && _crush == true)
						{
							if (!player->GetHit()) player->hitPlayer();
						}
						_state = SKE_STATE::WALK;
					}
				}
			}
			else {
				imageList[ImageAttack]->setFrameY(0);
				
				_count++;
				if (_count % (FRAMESPEED * 2) == 0) {
					_index++;
					if (_index > 2) {
						_index = 0;
					}
					imageList[ImageAttack]->setFrameX(_index);
					
					if (_index == 2) {
						RECT _imrc;
						if (IntersectRect(&_imrc, &_body, &player->GetCrush()) && player->GetisCrush() && _crush == true)
						{
							if (!player->GetHit()) player->hitPlayer();
						}
						_state = SKE_STATE::WALK;
					}
				}
			}
			break;
		case SKE_STATE::WALK:
			if (_isLeft) {
				imageList[ImageWalk]->setFrameY(1);
				_count++;
				if (_count % (FRAMESPEED*2) == 0) {
					_pt.x -= 5;
					_index++;
					if (_index > 3) {
						_index = 0;
					}
					imageList[ImageWalk]->setFrameX(_index);
					if (_index == 3) {
						_state = SKE_STATE::WALK;
					}
				}
			}
			else {
				imageList[ImageWalk]->setFrameY(0);
				_count++;
				if (_count % (FRAMESPEED * 2) == 0) {
					_pt.x += 5;
					_index++;
					if (_index > 3) {
						_index = 0;
					}
					imageList[ImageWalk]->setFrameX(_index);
					if (_index == 3) {
						_state = SKE_STATE::WALK;
					}
				}
			}
			break;
		case SKE_STATE::HIT:
			_count++;
			if (_count & (FRAMESPEED * 2))
			{
				if (_isLeft) {
					imageList[ImageHit]->setFrameY(1);
					_state = SKE_STATE::DEATH;
				}
				else {
					imageList[ImageHit]->setFrameY(0);
					_state = SKE_STATE::DEATH;
				}
			}
			break;
		case SKE_STATE::DEATH:
			_crush = false;
			if (_isLeft) {
				imageList[ImageDie]->setFrameY(1);
				_count++;
				if (_count % FRAMESPEED  == 0) {
					_index++;
					if (_index > 5) {
						_index = 0;
					}
					imageList[ImageDie]->setFrameX(_index);
					if (_index == 5) {
						_isDead = true;
						_show = false;
						UIMANAGER->SetScore(UIMANAGER->GetScore() + 200);
					}
				}
			}
			else {
				imageList[ImageDie]->setFrameY(0);
				_count++;
				if (_count % FRAMESPEED == 0) {
					_index++;
					if (_index > 5) {
						_index = 0;
					}
					imageList[ImageDie]->setFrameX(_index);
					if (_index == 5) {
						_isDead = true;
						_show = false;
						_crush = false;
					}
				}
			}
			break;
		}
	}
	_body = RectMakeCenter(_pt.x, _pt.y, 130, 100);
	// #################  RECT ���� ##########################################################
	_botpt = { _body.left + ((_body.right - _body.left) / 2) , _body.bottom - 14 };
	_leftpt = { _body.left + 15, _body.bottom - 50 };
	_rightpt = { _body.right - 15, _body.bottom - 50 };
	_bot = RectMakeCenter(_botpt.x, _botpt.y, 5, 10);
	_rightCheck = RectMakeCenter(_rightpt.x, _rightpt.y, 10, 5);
	_leftCheck = RectMakeCenter(_leftpt.x, _leftpt.y, 10, 5);
	_crushCheck = RectMakeCenter(_pt.x, _pt.y, 80, 80);
	// #################  RECT ���� ##########################################################
	
}

void skeleton::render(void)
{
	RECT bodyRC;
	bodyRC.left = _body.left - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.top = _body.top - Camera::getSingleton()->GetCameraRect().top;
	bodyRC.right = _body.right - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.bottom = _body.bottom - Camera::getSingleton()->GetCameraRect().top;
	// �÷��̾�� ����� ���� ���� ȭ�鿡 render���ش�.
	if (_show) {
		switch (_state)
		{
		case SKE_STATE::IDLE1:
			imageList[ImageGroundUp]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case SKE_STATE::IDLE2:
			imageList[ImageFloorUp]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case SKE_STATE::IDLE3:
			imageList[ImageWall]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case SKE_STATE::WALK:
			imageList[ImageWalk]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case SKE_STATE::ATTACK:
			imageList[ImageAttack]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case SKE_STATE::HIT:
			imageList[ImageHit]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		case SKE_STATE::DEATH:
			imageList[ImageDie]->frameRender(getMemDC(), bodyRC.left, bodyRC.top);
			break;
		}
	}

	if (_isDebug) {
		FrameRect(getMemDC(), _crushCheck, RGB(255, 0, 0));
		FrameRect(getMemDC(), bodyRC, RGB(255, 0, 0));
		FrameRect(getMemDC(), _body, RGB(255, 0, 0));
		FrameRect(getMemDC(), _bot, RGB(255, 0, 0));
		FrameRect(getMemDC(), _leftCheck, RGB(255, 0, 0));
		FrameRect(getMemDC(), _rightCheck, RGB(255, 0, 0));
	}

}

void skeleton::showskeleton(SKE_STATE state)
{
		switch (state)
		{
		case SKE_STATE::IDLE1:
			imageList[ImageGroundUp]->setFrameY(0);
			
			_count++;
			if (_count % FRAMESPEED == 0) {
				_index++;
				if (_index > 8) {
					_index = 0;
				}
				imageList[ImageGroundUp]->setFrameX(_index);
				if (_index == 8) {
					_state = SKE_STATE::WALK;
				}
			}
			break;
		case SKE_STATE::IDLE2:
			imageList[ImageFloorUp]->setFrameY(0);
			_count++;
			if (_count % FRAMESPEED == 0) {
				_index++;
				if (_index > 8) {
					_index = 0;
				}
				imageList[ImageFloorUp]->setFrameX(_index);
				if (_index == 8)
				{
					_state = SKE_STATE::WALK;
				}
			}
			break;
		case SKE_STATE::IDLE3:
			// ����
			if (_isLeft) { 
				imageList[ImageWall]->setFrameY(0);
			}
			// ������
			else { 
				imageList[ImageWall]->setFrameY(1);
			}
			_count++;
			if (_count % FRAMESPEED == 0) {
				_index++;
				if (_index > 8) {
					_index = 0;
				}
				imageList[ImageWall]->setFrameX(_index);
				if (_index == 8) {
					_state = SKE_STATE::WALK;
				}
			}
			break;
		}
}
// �÷��̾�� ���ɷ����� �Ÿ��� ����ؼ�
// �÷��̾ �ֺ������� ���̷����� ����
bool skeleton::checkPlayer(POINT playerpt)
{
	// �÷��̾ ��� �ٶ󺸰� ���ش�.
	if (this->_pt.x > playerpt.x) {
		_isLeft = true;
	}
	else {
		_isLeft = false;
	}
	float x = this->_pt.x - playerpt.x;
	float y = this->_pt.y - playerpt.y;
	// �÷��̾�� ���̷����� �Ÿ��� 150 ���� �۾�����
	// ���̷��� ����
	if (sqrtf((x*x) + (y * y)) < 350) {
		return true;
	}
	else {
		return false;
	}
}
