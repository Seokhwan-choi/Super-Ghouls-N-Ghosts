#include "stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_isLeft = false;								// 플레이어 좌,우 상태 초기화
	_isDead = false;								// 플레이어 사망 초기화
	_isArm = true;									// 플레이어 갑옷 착용 상태 초기화
	_isHit = false;									// 플레이어 히트 초기화
	_iscrush = false;								// 플레이어 충돌가능 초기화
	_hittime = 0;									// 플레이어 히트 타임 초기화
	_state = IDLE;									// 플레이어 상태 초기화
	_count = 0;										// 플레이어 프레임 속도 초기화
	_index = 0;										// 플레이어 프레임 index 초기화
	_attcount = 0;									// 플레이어 공격 카운트 초기화
	_gravity = 0.4f;								// 플레이어 중력
	_jumppw = 0.0f;									// 플레이어 점프파워
	_time = 0;										// 중력작용 타이머 초기화
	_pt = { 100, WINSIZEY-100 };					// 플레이어 좌표 초기화
	_width = 112; _height = 119;					// 플레이어 RECT 초기화
	_jumpCount = 0;									// 플레이어 점프 횟수 초기화

	_alpha = 125;									// 플레이어 알파값

	_check = false;									// 플레이어 RECT 보여주는 bool 변수
	_bullet = new Bullet[BULLETMAX];				// 플레이어 총알 초기화
	for (int i = 0; i < BULLETMAX; i++) {
		_bullet[i].init();
	}
	_rc = { 0,0,0,0 };
	

	// ========================================================================================================
	// ################################## 플레이어 맨몸 이미지 초기화 #############################################
	// ========================================================================================================
	IMAGEMANAGER->addFrameImage("맨몸_기본", "images/맨몸_기본.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맨몸_달리기", "images/맨몸_달리기.bmp", 672, 238, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맨몸_앉기", "images/맨몸_앉기.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맨몸_점프", "images/맨몸_점프.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맨몸_사다리", "images/맨몸_사다리.bmp", 448, 119, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맨몸_공격", "images/맨몸_공격.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맨몸_앉기공격", "images/맨몸_앉기공격.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맨몸_위공격", "images/맨몸_위공격.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맨몸_아래공격", "images/맨몸_아래공격.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("죽음", "images/죽음.bmp", 560, 238, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맞음", "images/맞음.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("갑옷얻음", "images/갑옷얻음.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));


	// ========================================================================================================
	// ################################## 플레이어 갑옷 이미지 초기화 #############################################
	// ========================================================================================================
	IMAGEMANAGER->addFrameImage("갑옷_기본", "images/갑옷_기본.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("갑옷_달리기", "images/갑옷_달리기.bmp", 672, 238, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("갑옷_앉기", "images/갑옷_앉기.bmp", 112, 238, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("갑옷_점프", "images/갑옷_점프.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("갑옷_사다리", "images/갑옷_사다리.bmp", 448, 119, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("갑옷_공격", "images/갑옷_공격.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("갑옷_앉기공격", "images/갑옷_앉기공격.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("갑옷_위공격", "images/갑옷_위공격.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("갑옷_아래공격", "images/갑옷_아래공격.bmp", 224, 238, 2, 2, true, RGB(255, 0, 255));


	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	_time++;
	// 중력 항상 적용
	_pt.y -= _jumppw;
	if (_time % 2 == 0) {
		_jumppw -= _gravity;
	}
	// 플레이어 알파값 계속 변화
	if (_time % 10 == 0) {
		_alpha += 125;
	}
	if (!_isDead) {	
		// 방향 좌우로 흔들면서 점프하면 무한점프 * 해결
		// 점프 중에 방향 좌우로 흔들고 나서 아래 방향키 누르면 점프 중에 앉아짐
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
		// ################################## 플레이어 'A' 눌렀을 때 (공 격 ) ########################################
		// ========================================================================================================
		if (KEYMANAGER->isOnceKeyDown('A') && _state != HIT && _state != DIE)
		{
			// ========================================================================================================
			// ############################## 플레이어가 앉아 있는지 확인 ( 앉기 공 격 ) ###################################
			// ========================================================================================================
			if (_state == SIT || _state == SITATTACK) {
				_state = SITATTACK; POINT _impt;
				// ========================================================================================================
				// ######################## _attcount를 증가시켜 던질때마다 총알 좌표 다름 ####################################
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
			// ####################### 플레이어가 점프하며 아래 누르는지 확인 ( 점프 아래 공 격 ) #############################
			// ========================================================================================================
			else if ((_state == DOWNATTACK || _state == JUMP) && KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_state = DOWNATTACK; POINT _impt;
				_attcount++;
				for (int i = 0; i < BULLETMAX; i++) {
					if (_bullet[i].getFire()) continue;
					// ========================================================================================================
					// ######################## _attcount를 증가시켜 던질때마다 총알 좌표 다름 ####################################
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
			// ############################# 플레이어가 위 누르는지 확인 ( 위 공 격 ) ######################################
			// ========================================================================================================
			else if ((_state == UPATTACK || _state == IDLE) && KEYMANAGER->isStayKeyDown(VK_UP)) {
				_state = UPATTACK; POINT _impt;
				_attcount++;
				for (int i = 0; i < BULLETMAX; i++) 
				{
					if (_bullet[i].getFire()) continue;
					// ========================================================================================================
					// ######################## _attcount를 증가시켜 던질때마다 총알 좌표 다름 ####################################
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
			// ############################# 플레이어가 점프 중에 공격을 누른다면 ( 점프 공 격 ) #############################
			// ========================================================================================================
			else if (_state == JUMP || _state == JUMPATTACK) {
				_state = JUMPATTACK; POINT _impt;
				_attcount++;
				for (int i = 0; i < BULLETMAX; i++) {
					if (_bullet[i].getFire()) continue;
					// ========================================================================================================
					// ######################## _attcount를 증가시켜 던질때마다 총알 좌표 다름 ####################################
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
			// ############################# 플레이어가 아무것도 누르지 않는다면 ( 공 격 ) ##################################
			// ========================================================================================================
			else {
				_state = ATTACK; POINT _impt;
				_attcount++;
				for (int i = 0; i < BULLETMAX; i++) {
					if (_bullet[i].getFire()) continue;
					// ========================================================================================================
					// ######################## _attcount를 증가시켜 던질때마다 총알 좌표 다름 ####################################
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
			// ############################# 플레이어 갑옷을 입고 왼쪽을 보고 있을 때 #######################################
			// ========================================================================================================
			if (_isArm)
			{
				armState(1);
			}
			else
			{
				// ========================================================================================================
				// ############################# 플레이어 맨몸이고 왼쪽을 보고 있을 때 #########################################
				// ========================================================================================================
				narmState(1);
			}
		}
		else
		{
			// ========================================================================================================
			// ############################# 플레이어 갑옷을입고 오른쪽을 보고 있을 때 ######################################
			// ========================================================================================================
			if (_isArm)
			{
				armState(0);
			}
			else
			{
				// ========================================================================================================
				// ############################# 플레이어 맨몸이고 오른쪽을 보고 있을 때 ########################################
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
		// ############################# 플레이어 픽셀 충돌 판정 ######################################
		// =========================================================================================
		if (_jumppw < 0)
		{
			_probeY = _botpt.y + 5;
			for (int i = _probeY - 5; i <= _probeY; ++i)
			{
				//해당 이미지의 HDC영역에서 x,i의 픽셀을 읽는다. 
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("픽셀")->getMemDC(), _botpt.x, i);
				//COLORREF의 데이터에서 각 rgb값을 받아온다. 
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);
				//rgb영역이 마젠타가 아니라면 
				if ((r == 222 && g == 222 && b == 0))
				{
					//공의 y는 볼의 height로 
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
				//해당 이미지의 HDC영역에서 x,i의 픽셀을 읽는다. 
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("픽셀")->getMemDC(), i, _leftpt.y);
				//COLORREF의 데이터에서 각 rgb값을 받아온다. 
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);
				//rgb영역을 검색한다.
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
				//해당 이미지의 HDC영역에서 x,i의 픽셀을 읽는다. 
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("픽셀")->getMemDC(), i, _rightpt.y);
				//COLORREF의 데이터에서 각 rgb값을 받아온다. 
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);
				//rgb영역을 검색한다. 
				if ((r == 222 && g == 222 && b == 0))
				{
					_pt.x = i - 42;
					break;
				}
			}
		}
		// =========================================================================================
		// ################################ 플레이어 HIT 초기화 ######################################
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
	// #################  RECT 보정 ##########################################################
	Camera::getSingleton()->SetCameraPosition(_pt);	// 카메라 플레이어를 따라간다.
	_body = RectMakeBottom(_pt.x, _pt.y, 112, 119); // 플레이어 RECT 초기화
	_botpt = { _body.left + ((_body.right - _body.left) / 2) , _body.bottom - 14 };
	_leftpt = { _body.left + 15, _body.bottom - 60 };
	_rightpt = { _body.right - 15, _body.bottom - 60 };
	_bot = RectMakeCenter(_botpt.x, _botpt.y, 5, 10);
	_rightCheck = RectMakeCenter(_rightpt.x, _rightpt.y , 10, 5);
	_leftCheck = RectMakeCenter(_leftpt.x, _leftpt.y, 10, 5);
	_crushRect = RectMakeCenter(_pt.x, _pt.y, 80, 80);
	// #################  RECT 보정 ##########################################################
}

void Player::render(void)
{
	//플레이어도 마찬가지로 카메라 상대좌표로 빼줌
	RECT playerRC;
	playerRC.left = _body.left - Camera::getSingleton()->GetCameraRect().left;
	playerRC.top = _body.top -Camera::getSingleton()->GetCameraRect().top;
	playerRC.right = _body.right - Camera::getSingleton()->GetCameraRect().left;
	playerRC.bottom = _body.bottom -Camera::getSingleton()->GetCameraRect().top;

	if (!_isDead) {
		if (_isArm) {
			// ========================================================================================================
			// ##################################### 플레이어 갑옷입은 상태 ##############################################
			// ========================================================================================================
			switch (_state) {
			case IDLE:
				IMAGEMANAGER->frameRender("갑옷_기본", getMemDC(), playerRC.left, playerRC.top);
				break;
			case RUN:
				IMAGEMANAGER->frameRender("갑옷_달리기", getMemDC(), playerRC.left, playerRC.top);
				break;
			case SIT:
				IMAGEMANAGER->frameRender("갑옷_앉기", getMemDC(), playerRC.left, playerRC.top);
				break;
			case JUMP:
				IMAGEMANAGER->frameRender("갑옷_점프", getMemDC(), playerRC.left, playerRC.top);
				break;
			case LADDER:
				IMAGEMANAGER->frameRender("갑옷_사다리", getMemDC(), playerRC.left, playerRC.top);
				break;
			case HIT:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맞음", getMemDC(), playerRC.left, playerRC.top, 0, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맞음", getMemDC(), playerRC.left, playerRC.top, 0, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맞음", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case DIE:
				IMAGEMANAGER->frameRender("죽음", getMemDC(), playerRC.left, playerRC.top);
				break;
			case ATTACK:
				IMAGEMANAGER->frameRender("갑옷_공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case JUMPATTACK:
				IMAGEMANAGER->frameRender("갑옷_공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case UPATTACK:
				IMAGEMANAGER->frameRender("갑옷_위공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case DOWNATTACK:
				IMAGEMANAGER->frameRender("갑옷_아래공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case SITATTACK:
				IMAGEMANAGER->frameRender("갑옷_앉기공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			}
		}
		else {
			// ========================================================================================================
			// ##################################### 플레이어 맨몸 상태 #################################################
			// ========================================================================================================
			switch (_state) {
			case IDLE:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_기본", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_기본", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_기본", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case RUN:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_달리기", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_달리기", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_달리기", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case SIT:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_앉기", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_앉기", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_앉기", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case JUMP:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_점프", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_점프", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_점프", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case LADDER:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_사다리", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_사다리", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_사다리", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case HIT:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맞음", getMemDC(), playerRC.left, playerRC.top, 0, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맞음", getMemDC(), playerRC.left, playerRC.top, 0, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맞음", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case DIE:
				IMAGEMANAGER->frameRender("죽음", getMemDC(), playerRC.left, playerRC.top);
				break;
			case ATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_공격", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_공격", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_공격", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case JUMPATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_공격", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_공격", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_공격", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case UPATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_위공격", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_위공격", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_위공격", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case DOWNATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_아래공격", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_아래공격", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_아래공격", getMemDC(), playerRC.left, playerRC.top);
				}
				break;
			case SITATTACK:
				if (_isHit) {
					if (_isLeft) {
						IMAGEMANAGER->alphaFrameRender("맨몸_앉기공격", getMemDC(), playerRC.left, playerRC.top, _index, 1, _alpha);
					}
					else {
						IMAGEMANAGER->alphaFrameRender("맨몸_앉기공격", getMemDC(), playerRC.left, playerRC.top, _index, 0, _alpha);
					}
				}
				else {
					IMAGEMANAGER->frameRender("맨몸_앉기공격", getMemDC(), playerRC.left, playerRC.top);
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
		IMAGEMANAGER->findImage("갑옷_기본")->setFrameY(num);
		IMAGEMANAGER->findImage("갑옷_기본")->setFrameX(_index);
		break;

	case RUN:
		_count++;
		IMAGEMANAGER->findImage("갑옷_달리기")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 5)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("갑옷_달리기")->setFrameX(_index);
		}
		break;

	case SIT:
		IMAGEMANAGER->findImage("갑옷_앉기")->setFrameY(num);
		IMAGEMANAGER->findImage("갑옷_앉기")->setFrameX(_index);
		break;

	case JUMP:
		_count++;
		IMAGEMANAGER->findImage("갑옷_점프")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 1)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("갑옷_점프")->setFrameX(_index);
			if (_index == 1) {
				_index--;
			}
		}
		break;

	case LADDER:
		_count++;
		IMAGEMANAGER->findImage("갑옷_사다리")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 4)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("갑옷_사다리")->setFrameX(_index);
		}
		break;
	case HIT:
		_count++;
		if ( num == 1) _pt.x += 1;
		else _pt.x -= 1;
		IMAGEMANAGER->findImage("맞음")->setFrameY(num);
		IMAGEMANAGER->findImage("맞음")->setFrameX(0);
		if (_count % 25 == 0) {
			_state = IDLE;
			_isArm = false;
		}
		break;
	case ATTACK:
		_count++;
		IMAGEMANAGER->findImage("갑옷_공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("갑옷_공격")->setFrameX(_index);
			if (_index == 2) {
				_state = IDLE;
			}
		}
		break;
	case JUMPATTACK:
		_count++;
		IMAGEMANAGER->findImage("갑옷_공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("갑옷_공격")->setFrameX(_index);
			if (_index == 2) {
				_state = JUMP;
			}
		}
		break;

	case UPATTACK:
		_count++;
		IMAGEMANAGER->findImage("갑옷_위공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("갑옷_위공격")->setFrameX(_index);
			if (_index == 2) {
				_state = IDLE;
			}
		}
		break;

	case DOWNATTACK:
		_count++;
		IMAGEMANAGER->findImage("갑옷_아래공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("갑옷_아래공격")->setFrameX(_index);
			if (_index == 2) {
				_state = JUMP;
			}
		}
		break;

	case SITATTACK:
		_count++;
		IMAGEMANAGER->findImage("갑옷_앉기공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("갑옷_앉기공격")->setFrameX(_index);
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
		IMAGEMANAGER->findImage("맨몸_기본")->setFrameY(num);
		IMAGEMANAGER->findImage("맨몸_기본")->setFrameX(_index);
		break;
	case RUN:
		_count++;
		IMAGEMANAGER->findImage("맨몸_달리기")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 6)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("맨몸_달리기")->setFrameX(_index);
		}
		break;
	case SIT:
		IMAGEMANAGER->findImage("맨몸_앉기")->setFrameY(num);
		IMAGEMANAGER->findImage("맨몸_앉기")->setFrameX(_index);
		break;
	case JUMP:
		_count++;
		IMAGEMANAGER->findImage("맨몸_점프")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 1)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("맨몸_점프")->setFrameX(_index);
			if (_index == 1) {
				_index--;
			}
		}
		break;

	case LADDER:
		_count++;
		IMAGEMANAGER->findImage("맨몸_사다리")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 4)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("맨몸_사다리")->setFrameX(_index);
		}
		break;
	case HIT:
		_count++;
		if (num == 1) _pt.x += 1;
		else _pt.x -= 1;
		IMAGEMANAGER->findImage("맞음")->setFrameY(num);
		IMAGEMANAGER->findImage("맞음")->setFrameX(0);
		if (_count % 25 == 0) {
			_state = DIE;
		}
		break;
	case DIE:
		_iscrush = false;
		_count++;
		IMAGEMANAGER->findImage("죽음")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 5)
			{
				_index = 0;
				
			}
			IMAGEMANAGER->findImage("죽음")->setFrameX(_index);
			if (_index == 5) {
				_isDead = true;
			}
		}
		break;
	case ATTACK:
		_count++;
		IMAGEMANAGER->findImage("맨몸_공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("맨몸_공격")->setFrameX(_index);
			if (_index == 2) {
				_state = IDLE;
			}
		}
		break;
	case JUMPATTACK:
		_count++;
		IMAGEMANAGER->findImage("맨몸_공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("맨몸_공격")->setFrameX(_index);
			if (_index == 2) {
				_state = JUMP;
			}
		}
		break;
	case UPATTACK:
		_count++;
		IMAGEMANAGER->findImage("맨몸_위공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("맨몸_위공격")->setFrameX(_index);
			if (_index == 2) {
				_state = IDLE;
			}
		}
		break;
	case DOWNATTACK:
		_count++;
		IMAGEMANAGER->findImage("맨몸_아래공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("맨몸_아래공격")->setFrameX(_index);
			if (_index == 2) {
				_state = JUMP;
			}
		}
		break;
	case SITATTACK:
		_count++;
		IMAGEMANAGER->findImage("맨몸_앉기공격")->setFrameY(num);
		if (_count % FRAMESPEED == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
				
			}
			IMAGEMANAGER->findImage("맨몸_앉기공격")->setFrameX(_index);
			if (_index == 2) {
				_state = SIT;
			}
		}
		break;
	}
}
