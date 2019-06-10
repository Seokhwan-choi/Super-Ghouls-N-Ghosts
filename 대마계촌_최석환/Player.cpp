#include "stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_isLeft = false;								// �÷��̾� ��,�� ���� �ʱ�ȭ
	_isDead = false;								// �÷��̾� ��� �ʱ�ȭ
	_isArm = true;									// �÷��̾� ���� ���� ���� �ʱ�ȭ
	_isHit = false;									// �÷��̾� ��Ʈ �ʱ�ȭ
	_iscrush = false;								// �÷��̾� �浹���� �ʱ�ȭ
	_hittime = 0;									// �÷��̾� ��Ʈ Ÿ�� �ʱ�ȭ
	_state = IDLE;									// �÷��̾� ���� �ʱ�ȭ
	_count = 0;										// �÷��̾� ������ �ӵ� �ʱ�ȭ
	_index = 0;										// �÷��̾� ������ index �ʱ�ȭ
	_attcount = 0;									// �÷��̾� ���� ī��Ʈ �ʱ�ȭ
	_gravity = 0.4f;								// �÷��̾� �߷�
	_jumppw = 0.0f;									// �÷��̾� �����Ŀ�
	_time = 0;										// �߷��ۿ� Ÿ�̸� �ʱ�ȭ
	_pt = { 100, WINSIZEY-100 };					// �÷��̾� ��ǥ �ʱ�ȭ
	_width = 112; _height = 119;					// �÷��̾� RECT �ʱ�ȭ
	_jumpCount = 0;									// �÷��̾� ���� Ƚ�� �ʱ�ȭ

	_alpha = 125;									// �÷��̾� ���İ�

	_check = false;									// �÷��̾� RECT �����ִ� bool ����
	_bullet = new Bullet[BULLETMAX];				// �÷��̾� �Ѿ� �ʱ�ȭ
	for (int i = 0; i < BULLETMAX; i++) {
		_bullet[i].init();
	}
	_rc = { 0,0,0,0 };
	

	// ========================================================================================================
	// ################################## �÷��̾� �Ǹ� �̹��� �ʱ�ȭ #############################################
	// ========================================================================================================
	IMAGEMANAGER->addFrameImage("�Ǹ�_�⺻", "images/�Ǹ�_�⺻.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ǹ�_�޸���", "images/�Ǹ�_�޸���.bmp", 672, 238, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ǹ�_�ɱ�", "images/�Ǹ�_�ɱ�.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ǹ�_����", "images/�Ǹ�_����.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ǹ�_��ٸ�", "images/�Ǹ�_��ٸ�.bmp", 448, 119, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ǹ�_����", "images/�Ǹ�_����.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ǹ�_�ɱ����", "images/�Ǹ�_�ɱ����.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ǹ�_������", "images/�Ǹ�_������.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ǹ�_�Ʒ�����", "images/�Ǹ�_�Ʒ�����.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/����.bmp", 560, 238, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/����.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʾ���", "images/���ʾ���.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));


	// ========================================================================================================
	// ################################## �÷��̾� ���� �̹��� �ʱ�ȭ #############################################
	// ========================================================================================================
	IMAGEMANAGER->addFrameImage("����_�⺻", "images/����_�⺻.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�޸���", "images/����_�޸���.bmp", 672, 238, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�ɱ�", "images/����_�ɱ�.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����", "images/����_����.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_��ٸ�", "images/����_��ٸ�.bmp", 448, 119, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����", "images/����_����.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�ɱ����", "images/����_�ɱ����.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_������", "images/����_������.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�Ʒ�����", "images/����_�Ʒ�����.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));


	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	_time++;
	// �߷� �׻� ����
	_pt.y -= _jumppw;
	if (_time % 2 == 0) {
		_jumppw -= _gravity;
	}
	// �÷��̾� ���İ� ��� ��ȭ
	if (_time % 10 == 0) {
		_alpha += 125;
	}
	if (!_isDead) {	
		// ���� �¿�� ���鼭 �����ϸ� �������� * �ذ�
		// ���� �߿� ���� �¿�� ���� ���� �Ʒ� ����Ű ������ ���� �߿� �ɾ���
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && (_state != ATTACK && _state != SIT && _state != SITATTACK && _state != HIT && _state != DIE))
		{
			_isLeft = true;
			if (_state != JUMP && _state != JUMPATTACK) {
				_state = RUN;
			}
			_pt.x -= 4;
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && (_state != ATTACK && _state != SIT && _state != SITATTACK && _state != HIT && _state != DIE))
		{
			_isLeft = false;
			if (_state != JUMP && _state != JUMPATTACK) {
				_state = RUN;
			}
			_pt.x += 4;
		}

		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _state != HIT && _state != DIE && _jumpCount == 0) {
			if (_state == SITATTACK) {
				_state = SITATTACK;
			}
			else if (_state == IDLE || _state == RUN) {
				_state = SIT;
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && _state != HIT && _state != DIE) {
			if (_state == JUMP || _state == DOWNATTACK) {
				_state = JUMP;
			}
			else {
				_state = IDLE;
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _state != HIT && _state != DIE) {
			_isLeft = true;
			if (_state != JUMP) {
				_state = IDLE;
			}
			_index = 0;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _state != HIT && _state != DIE) {
			_isLeft = false;
			if (_state != JUMP) {
				_state = IDLE;
			}
			_index = 0;
		}
		// ========================================================================================================
		// ################################## �÷��̾� 'A' ������ �� (�� �� ) ########################################
		// ========================================================================================================
		if (KEYMANAGER->isOnceKeyDown('A') && _state != HIT && _state != DIE)
		{
			// ========================================================================================================
			// ############################## �÷��̾ �ɾ� �ִ��� Ȯ�� ( �ɱ� �� �� ) ###################################
			// ========================================================================================================
			if (_state == SIT || _state == SITATTACK) {
				_state = SITATTACK; POINT _impt;
				// ========================================================================================================
				// ######################## _attcount�� �������� ���������� �Ѿ� ��ǥ �ٸ� ####################################
				// ========================================================================================================
				_attcount++;
				for (int i = 0; i < BULLETMAX; i++) {
					if (_bullet[i].getFire()) continue;
					if (_isLeft) {
						_bullet[i].setWay(WAY::LEFT);
						if (_attcount % 2 == 0) {
							_impt = { _body.left ,  _body.top + (_body.bottom - _body.top) / 2 + 5 + 15 };
						}
						else {
							_impt = { _body.left, _body.top + (_body.bottom - _body.top) / 2 + 5 + 30 };
						}
					}
					else {
						_bullet[i].setWay(WAY::RIGHT);
						if (_attcount % 2 == 0) {
							_impt = { _body.right, _body.top + (_body.bottom - _body.top) / 2 + 5 + 15 };
						}
						else {
							_impt = { _body.right, _body.top + (_body.bottom - _body.top) / 2 + 5 + 30 };
						}
					}
					_bullet[i].Fire(_impt);
					break;
				}

			}
			// ========================================================================================================
			// ####################### �÷��̾ �����ϸ� �Ʒ� �������� Ȯ�� ( ���� �Ʒ� �� �� ) #############################
			// ========================================================================================================
			else if ((_state == DOWNATTACK || _state == JUMP) && KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_state = DOWNATTACK; POINT _impt;
				_attcount++;
				for (int i = 0; i < BULLETMAX; i++) {
					if (_bullet[i].getFire()) continue;
					// ========================================================================================================
					// ######################## _attcount�� �������� ���������� �Ѿ� ��ǥ �ٸ� ####################################
					// ========================================================================================================
					_bullet[i].setWay(WAY::DOWN);
					if (_attcount % 2 == 0) {
						_impt = { _body.left + (_body.right - _body.left) / 2 - 10, _body.bottom };
					}
					else {
						_impt = { _body.left + (_body.right - _body.left) / 2 + 10, _body.bottom };
					}
					_bullet[i].Fire(_impt);
					break;
				}
			}
			// ========================================================================================================
			// ############################# �÷��̾ �� �������� Ȯ�� ( �� �� �� ) ######################################
			// ========================================================================================================
			else if ((_state == UPATTACK || _state == IDLE) && KEYMANAGER->isStayKeyDown(VK_UP)) {
				_state = UPATTACK; POINT _impt;
				_attcount++;
				for (int i = 0; i < BULLETMAX; i++) 
				{
					if (_bullet[i].getFire()) continue;
					// ========================================================================================================
					// ######################## _attcount�� �������� ���������� �Ѿ� ��ǥ �ٸ� ####################################
					// ========================================================================================================
					_bullet[i].setWay(WAY::UP);
					if (_attcount % 2 == 0) {
						_impt = { _body.left + (_body.right - _body.left) / 2 - 10, _body.top };
					}
					else {
						_impt = { _body.left + (_body.right - _body.left) / 2 + 10, _body.top };
					}
					_bullet[i].Fire(_impt);
					break;
				}
			}
			// ========================================================================================================
			// ############################# �÷��̾ ���� �߿� ������ �����ٸ� ( ���� �� �� ) #############################
			// ========================================================================================================
			else if (_state == JUMP || _state == JUMPATTACK) {
				_state = JUMPATTACK; POINT _impt;
				_attcount++;
				for (int i = 0; i < BULLETMAX; i++) {
					if (_bullet[i].getFire()) continue;
					// ========================================================================================================
					// ######################## _attcount�� �������� ���������� �Ѿ� ��ǥ �ٸ� ####################################
					// ========================================================================================================
					if (_isLeft) {
						_bullet[i].setWay(WAY::LEFT);
						if (_attcount % 2 == 0) {
							_impt = { _body.left, _body.top + 56 + 15 };
						}
						else {
							_impt = { _body.left, _body.top + 56 + 25 };
						}
					}
					else {
						_bullet[i].setWay(WAY::RIGHT);
						if (_attcount % 2 == 0) {
							_impt = { _body.right, _body.top + 56 + 15 };
						}
						else {
							_impt = { _body.right, _body.top + 56 + 25 };
						}
					}
					_bullet[i].Fire(_impt);
					break;
				}
			}
			// ========================================================================================================
			// ############################# �÷��̾ �ƹ��͵� ������ �ʴ´ٸ� ( �� �� ) ##################################
			// ========================================================================================================
			else {
				_state = ATTACK; POINT _impt;
				_attcount++;
				for (int i = 0; i < BULLETMAX; i++) {
					if (_bullet[i].getFire()) continue;
					// ========================================================================================================
					// ######################## _attcount�� �������� ���������� �Ѿ� ��ǥ �ٸ� ####################################
					// ========================================================================================================
					if (_isLeft) {
						_bullet[i].setWay(WAY::LEFT);
						if (_attcount % 2 == 0) {
							_impt = { _body.left, _body.top + 56 + 15 };
						}
						else {
							_impt = { _body.left, _body.top + 56 + 25 };
						}
					}
					else {
						_bullet[i].setWay(WAY::RIGHT);
						if (_attcount % 2 == 0) {
							_impt = { _body.right, _body.top + 56 + 15 };
						}
						else {
							_impt = { _body.right, _body.top + 56 + 25 };
						}
					}
					_bullet[i].Fire(_impt);
					break;
				}
			}

		}

		if (KEYMANAGER->isOnceKeyDown('S') && (_state != JUMP && _state != ATTACK) && _jumpCount < 1) {
			_state = JUMP;
			_gravity = 0.4f;
			_jumppw = 6.0f;
			_jumpCount++;
		}
		if (KEYMANAGER->isOnceKeyDown('Q')) {
			if (_isArm) {
				_isArm = false;
			}
			else {
				_isArm = true;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('W')) {
			this->hitPlayer();
		}

		if (_isLeft)
		{
			// ========================================================================================================
			// ############################# �÷��̾� ������ �԰� ������ ���� ���� �� #######################################
			// ========================================================================================================
			if (_isArm)
			{
				armState(1);
			}
			else
			{
				// ========================================================================================================
				// ############################# �÷��̾� �Ǹ��̰� ������ ���� ���� �� #########################################
				// ========================================================================================================
				narmState(1);
			}
		}
		else
		{
			// ========================================================================================================
			// ############################# �÷��̾� �������԰� �������� ���� ���� �� ######################################
			// ========================================================================================================
			if (_isArm)
			{
				armState(0);
			}
			else
			{
				// ========================================================================================================
				// ############################# �÷��̾� �Ǹ��̰� �������� ���� ���� �� ########################################
				// ========================================================================================================
				narmState(0);

			}
		}

		for (int i = 0; i < BULLETMAX; i++) 
		{
			if (!_bullet[i].getFire()) continue;
			_bullet[i].update();
		}
		// =========================================================================================
		// ############################# �÷��̾� �ȼ� �浹 ���� ######################################
		// =========================================================================================
		if (_jumppw < 0)
		{
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
					//���� y�� ���� height�� 
					_pt.y = i + 9;
					_jumppw = 0.0f;
					_jumpCount = 0;
					if (_state == JUMP) {
						_state = IDLE;
					}
					break;
				}
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
					_pt.x = i + 42;
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
					_pt.x = i - 42;
					break;
				}
			}
		}
		// =========================================================================================
		// ################################ �÷��̾� HIT �ʱ�ȭ ######################################
		// =========================================================================================
		if (_isHit) {
			_hittime++;
			if (_hittime > 150) {
				_isHit = false;
			}
		}
	}
	else {
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			this->init();
		}
	}
	// #################  RECT ���� ##########################################################
	Camera::getSingleton()->SetCameraPosition(_pt);	// ī�޶� �÷��̾ ���󰣴�.
	_body = RectMakeBottom(_pt.x, _pt.y, 112, 119); // �÷��̾� RECT �ʱ�ȭ
	_botpt = { _body.left + ((_body.right - _body.left) / 2) , _body.bottom - 14 };
	_leftpt = { _body.left + 15, _body.bottom - 60 };
	_rightpt = { _body.right - 15, _body.bottom - 60 };
	_bot = RectMakeCenter(_botpt.x, _botpt.y, 5, 10);
	_rightCheck = RectMakeCenter(_rightpt.x, _rightpt.y , 10, 5);
	_leftCheck = RectMakeCenter(_leftpt.x, _leftpt.y, 10, 5);
	_crushRect = RectMakeCenter(_pt.x, _pt.y, 80, 80);
	// #################  RECT ���� ##########################################################
}

void Player::render(void)
{
	//�÷��̾ ���������� ī�޶� �����ǥ�� ����
	RECT playerRC;
	playerRC.left = _body.left - Camera::getSingleton()->GetCameraRect().left;
	playerRC.top = _body.top -Camera::getSingleton()->GetCameraRect().top;
	playerRC.right = _body.right - Camera::getSingleton()->GetCameraRect().left;
	playerRC.bottom = _body.bottom -Camera::getSingleton()->GetCameraRect().top;

	if (!_isDead) {
		if (_isArm) {
			// ========================================================================================================
			// ##################################### �÷��̾� �������� ���� ##############################################
			// ========================================================================================================
			switch (_state) {
			case IDLE:
				IMAGEMANAGER->frameRender("����_�⺻", getMemDC(), playerRC.left, playerRC.top);
				break;
			case RUN:
				IMAGEMANAGER->frameRender("����_�޸���", getMemDC(), playerRC.left, playerRC.top);
				break;
			case SIT:
				IMAGEMANAGER->frameRender("����_�ɱ�", getMemDC(), playerRC.left, playerRC.top);
				break;
			case JUMP:
				IMAGEMANAGER->frameRender("����_����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case LADDER:
				IMAGEMANAGER->frameRender("����_��ٸ�", getMemDC(), playerRC.left, playerRC.top);
				break;
			case HIT:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("����", getMemDC(), playerRC.left, playerRC.top, 0, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("����", getMemDC(), playerRC.left, playerRC.top, 0, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("����", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case DIE:
				IMAGEMANAGER->frameRender("����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case ATTACK:
				IMAGEMANAGER->frameRender("����_����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case JUMPATTACK:
				IMAGEMANAGER->frameRender("����_����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case UPATTACK:
				IMAGEMANAGER->frameRender("����_������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case DOWNATTACK:
				IMAGEMANAGER->frameRender("����_�Ʒ�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case SITATTACK:
				IMAGEMANAGER->frameRender("����_�ɱ����", getMemDC(), playerRC.left, playerRC.top);
				break;
			}
		}
		else {
			// ========================================================================================================
			// ##################################### �÷��̾� �Ǹ� ���� #################################################
			// ========================================================================================================
			switch (_state) {
			case IDLE:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�⺻", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�⺻", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_�⺻", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case RUN:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�޸���", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�޸���", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_�޸���", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case SIT:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�ɱ�", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�ɱ�", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_�ɱ�", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case JUMP:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_����", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_����", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_����", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case LADDER:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_��ٸ�", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_��ٸ�", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_��ٸ�", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case HIT:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("����", getMemDC(), playerRC.left, playerRC.top, 0, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("����", getMemDC(), playerRC.left, playerRC.top, 0, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("����", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case DIE:
				IMAGEMANAGER->frameRender("����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case ATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_����", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_����", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_����", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case JUMPATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_����", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_����", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_����", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case UPATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_������", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_������", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_������", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case DOWNATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�Ʒ�����", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�Ʒ�����", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_�Ʒ�����", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case SITATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�ɱ����", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("�Ǹ�_�ɱ����", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("�Ǹ�_�ɱ����", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			}
		}
		for (int i = 0; i < BULLETMAX; i++) {
			if (!_bullet[i].getFire()) continue;
			_bullet[i].render();
		}
	}
	//char str[256];
	//sprintf(str, "_index : %d, _state : %d, _count : %d", _index, _state, _count);
	//TextOut(getMemDC(), 50, 50, str, strlen(str));

	if (_isDebug == true) {
		FrameRect(getMemDC(), playerRC, (255, 0, 0));
		FrameRect(getMemDC(), _body, (255, 0, 0));
		FrameRect(getMemDC(), _bot, (255, 0, 0));
		FrameRect(getMemDC(), _leftCheck, (255, 0, 0));
		FrameRect(getMemDC(), _rightCheck, (255, 0, 0));
	}

}

void Player::hitPlayer()
{
	_state = HIT;
	_jumppw = 0.8f;
	_isHit = true;
}

void Player::armState(int num)
{
	switch (_state)
	{
	case IDLE:
		IMAGEMANAGER->findImage("����_�⺻")->setFrameY(num);
		IMAGEMANAGER->findImage("����_�⺻")->setFrameX(_index);
		break;

	case RUN:
		_count++;
		IMAGEMANAGER->findImage("����_�޸���")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 5)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("����_�޸���")->setFrameX(_index);
		}
		break;

	case SIT:
		IMAGEMANAGER->findImage("����_�ɱ�")->setFrameY(num);
		IMAGEMANAGER->findImage("����_�ɱ�")->setFrameX(_index);
		break;

	case JUMP:
		_count++;
		IMAGEMANAGER->findImage("����_����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 1)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("����_����")->setFrameX(_index);
			if (_index == 1) {
				_index--;
			}
		}
		break;

	case LADDER:
		_count++;
		IMAGEMANAGER->findImage("����_��ٸ�")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 4)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("����_��ٸ�")->setFrameX(_index);
		}
		break;
	case HIT:
		_count++;
		if ( num == 1) _pt.x += 1;
		else _pt.x -= 1;
		IMAGEMANAGER->findImage("����")->setFrameY(num);
		IMAGEMANAGER->findImage("����")->setFrameX(0);
		if (_count % 25 == 0) {
			_state = IDLE;
			_isArm = false;
		}
		break;
	case ATTACK:
		_count++;
		IMAGEMANAGER->findImage("����_����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("����_����")->setFrameX(_index);
			if (_index == 2) {
				_state = IDLE;
			}
		}
		break;
	case JUMPATTACK:
		_count++;
		IMAGEMANAGER->findImage("����_����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("����_����")->setFrameX(_index);
			if (_index == 2) {
				_state = JUMP;
			}
		}
		break;

	case UPATTACK:
		_count++;
		IMAGEMANAGER->findImage("����_������")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("����_������")->setFrameX(_index);
			if (_index == 2) {
				_state = IDLE;
			}
		}
		break;

	case DOWNATTACK:
		_count++;
		IMAGEMANAGER->findImage("����_�Ʒ�����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("����_�Ʒ�����")->setFrameX(_index);
			if (_index == 2) {
				_state = JUMP;
			}
		}
		break;

	case SITATTACK:
		_count++;
		IMAGEMANAGER->findImage("����_�ɱ����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("����_�ɱ����")->setFrameX(_index);
			if (_index == 2) {
				_state = SIT;
			}
		}
		break;
	}
}

void Player::narmState(int num)
{
	switch (_state)
	{
	case IDLE:
		IMAGEMANAGER->findImage("�Ǹ�_�⺻")->setFrameY(num);
		IMAGEMANAGER->findImage("�Ǹ�_�⺻")->setFrameX(_index);
		break;
	case RUN:
		_count++;
		IMAGEMANAGER->findImage("�Ǹ�_�޸���")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 6)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("�Ǹ�_�޸���")->setFrameX(_index);
		}
		break;
	case SIT:
		IMAGEMANAGER->findImage("�Ǹ�_�ɱ�")->setFrameY(num);
		IMAGEMANAGER->findImage("�Ǹ�_�ɱ�")->setFrameX(_index);
		break;
	case JUMP:
		_count++;
		IMAGEMANAGER->findImage("�Ǹ�_����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 1)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("�Ǹ�_����")->setFrameX(_index);
			if (_index == 1) {
				_index--;
			}
		}
		break;

	case LADDER:
		_count++;
		IMAGEMANAGER->findImage("�Ǹ�_��ٸ�")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 4)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("�Ǹ�_��ٸ�")->setFrameX(_index);
		}
		break;
	case HIT:
		_count++;
		if (num == 1) _pt.x += 1;
		else _pt.x -= 1;
		IMAGEMANAGER->findImage("����")->setFrameY(num);
		IMAGEMANAGER->findImage("����")->setFrameX(0);
		if (_count % 25 == 0) {
			_state = DIE;
		}
		break;
	case DIE:
		_iscrush = false;
		_count++;
		IMAGEMANAGER->findImage("����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 5)
			{
				_index = 0;
				
			}
			IMAGEMANAGER->findImage("����")->setFrameX(_index);
			if (_index == 5) {
				_isDead = true;
			}
		}
		break;
	case ATTACK:
		_count++;
		IMAGEMANAGER->findImage("�Ǹ�_����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("�Ǹ�_����")->setFrameX(_index);
			if (_index == 2) {
				_state = IDLE;
			}
		}
		break;
	case JUMPATTACK:
		_count++;
		IMAGEMANAGER->findImage("�Ǹ�_����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("�Ǹ�_����")->setFrameX(_index);
			if (_index == 2) {
				_state = JUMP;
			}
		}
		break;
	case UPATTACK:
		_count++;
		IMAGEMANAGER->findImage("�Ǹ�_������")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("�Ǹ�_������")->setFrameX(_index);
			if (_index == 2) {
				_state = IDLE;
			}
		}
		break;
	case DOWNATTACK:
		_count++;
		IMAGEMANAGER->findImage("�Ǹ�_�Ʒ�����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("�Ǹ�_�Ʒ�����")->setFrameX(_index);
			if (_index == 2) {
				_state = JUMP;
			}
		}
		break;
	case SITATTACK:
		_count++;
		IMAGEMANAGER->findImage("�Ǹ�_�ɱ����")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
				
			}
			IMAGEMANAGER->findImage("�Ǹ�_�ɱ����")->setFrameX(_index);
			if (_index == 2) {
				_state = SIT;
			}
		}
		break;
	}
}
