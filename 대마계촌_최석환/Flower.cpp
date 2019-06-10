#include "stdafx.h"
#include "Flower.h"
#include "Player.h"
#include "Bullet.h"
#define FRAMESPEED 5

HRESULT Flower::init(int x, int y)
{
	_time = 0;										// 해골꽃 시간 초기화
	_index = 0;										// 해골꽃 프레임 인덱스 초기화
	_count = 0;										// 해골꽃 프레임 카운트 초기화
	_movecount = 0;									// 해골꽃 무빙 카운트
	_health = 5;									// 해골꽃 체력 초기화
	_gravity = 0.4f;								// 해골꽃 중력 초기화
	_jumppw = 0.0f;									// 해골꽃 점프파워 초기화
	_attack = false;								// 해골꽃 공격했냐?
	_find = false;									// 해골꽃 플레이어 찾았냐?
	_show = false;									// 해골꽃 보여주냐?
	_isDead = false;								// 해골꽃 죽음?
	_state = FLOWER_STATE::SHOW;					// 해골꽃 상태 초기화
	_pt = { x, y };									// 해골꽃 좌표 초기화
	_body = RectMakeCenter(_pt.x, _pt.y, 100, 85);	// 해골꽃 위치 초기화

	_bullet = new FlowerBullet[BULLETMAX];	// 해골꽃 총알 초기화
	for (int i = 0; i < BULLETMAX; i++) {
		_bullet[i].init();
	}

	image* newImage = nullptr;
	newImage = new image;
	newImage->init("images/해골꽃_등장.bmp", 500, 85, 5, 1, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/해골꽃_기본.bmp", 500, 85, 5, 1, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/해골꽃_이동.bmp", 300, 85, 3, 1, true, RGB(255, 0, 255)); 
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/해골꽃_공격.bmp", 200, 85, 2, 1, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/해골꽃_죽음.bmp", 600, 85, 6, 1, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);

	
	// ======================================================================================================
	// ########################################## 해골꽃 이미지 초기화 #########################################
	// ======================================================================================================
	//IMAGEMANAGER->addFrameImage("해골꽃_등장", "images/해골꽃_등장.bmp", 500, 85, 5, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("해골꽃_기본", "images/해골꽃_기본.bmp", 500, 85, 5, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("해골꽃_공격", "images/해골꽃_공격.bmp", 200, 85, 2, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("해골꽃_이동", "images/해골꽃_이동.bmp", 300, 85, 3, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("해골꽃_죽음", "images/해골꽃_죽음.bmp", 600, 85, 6, 1, true, RGB(255, 0, 255));
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
		// 플레이어와 해골꽃의 거리를 확인
		// 플레이어가 일정간격 안으로 들어오면, true
		if (_find == false) {
			_find = checkPlayer(player->Getpt());
		}
		if (_find) {
			if (_state != FLOWER_STATE::SHOW) {
				// 모습을 완전히 들어냈을 때 충돌 가능
				_crush = true;
				float x = this->_pt.x - player->Getpt().x;
				float y = this->_pt.y - player->Getpt().y;
				// 플레이어와의 거리를 확인
				// 거리가 가까워지면 공격한다.
				if ((sqrtf((x*x) + (y * y)) < 450) && _attack == false) {
					_state = FLOWER_STATE::ATTACK;
				}
			}
		}
		int count = 0;
		if (_attack == true) {
			if (_time % 250 == 0) {
				// 해골꽃 총알이 모두 false가 되었는지 확인
				for (int i = 0; i < FLOWERBULLET; i++)
				{
					if (_bullet[i].GetFire()) break;
					count++;
				}
				// 해골꽃 총알이 모두 false 이면
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
		// ############################## 해골꽃 픽셀 충돌 처리 ########################################
		// ==========================================================================================
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
				_jumppw = 0.0f;
				_pt.y = i - 33;
				break;
			}
		}
		if (_state == FLOWER_STATE::MOVE_LEFT) {
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
		else if (_state == FLOWER_STATE::MOVE_RIGHT) {
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

		// ==========================================================================================
		// ############################ 해골꽃 플레이어 총알 충돌 처리 ##################################
		// ==========================================================================================
		for (int i = 0; i < BULLETMAX; i++) {
			RECT _imrc;
			if (!player->GetBullet()[i].getFire()) continue;
			if (IntersectRect(&_imrc, &_body, &player->GetBullet()[i].getRect()) && _crush == true)
			{
				// 플레이어의 총알에 스켈레톤이 맞으면 체력감소 --
				_health--;
				// 충돌된 총알은 false 처리 해준다.
				player->GetBullet()[i].setFire(false);
			}
		}

		// ==========================================================================================
		// ############################ 해골꽃 총알 플레이어 충돌 처리 ##################################
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
		// ############################ 해골꽃 플레이어 충돌 처리 #######################################
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
	// #################  RECT 보정 ##########################################################
	_botpt = { _body.left + ((_body.right - _body.left) / 2) , _body.bottom - 14 };
	_leftpt = { _body.left + 15, _body.bottom - 42 };
	_rightpt = { _body.right - 15, _body.bottom - 42 };
	_bot = RectMakeCenter(_botpt.x, _botpt.y, 5, 10);
	_rightCheck = RectMakeCenter(_rightpt.x, _rightpt.y, 10, 5);
	_leftCheck = RectMakeCenter(_leftpt.x, _leftpt.y, 10, 5);
	// #################  RECT 보정 ##########################################################
}


void Flower::render(void)
{
	//플레이어도 마찬가지로 카메라 상대좌표로 빼줌
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
	// 플레이어와 해골꽃의 거리가 150 보다 작아지면
	// 해골꽃 등장
	if (sqrtf((x*x) + (y * y)) < 350) {
		return true;
	}
	else {
		return false;
	}
}
