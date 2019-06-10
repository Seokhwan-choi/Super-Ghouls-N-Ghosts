#include "stdafx.h"
#include "skeleton.h"
#include "Player.h"
#include "Bullet.h"
#include <math.h>
#define FRAMESPEED 10

HRESULT skeleton::init(int x, int y, SKE_STATE state)
{
	_gravity = 0.4f;									// 스켈레톤 중력 초기화
	_jumppw = 0.0f;										// 스켈레톤 점프파워 초기화
	this->_state = state;								// 스켈레톤 상태 초기화
	//this->_isLeft = isLeft;							// 스켈레톤 좌,우 초기화
	_attack = false;									// 스켈레톤 공격 초기화
	_crush = false;										// 스켈레톤 충돌가능 초기화
	_show = false;										// 스켈레톤 보여준다.
	_find = false;										// 스켈레톤이 플레이어를 찾았냐?
	_isDead = false;									// 스켈레톤 죽었냐?
	_isHit = false;										// 스켈레톤 맞았냐?
	_attacktime = 0;									// 스켈레톤 공격 쿨타임
	_count = 0;											// 스켈레톤 프레임 카운트 초기화
	_index = 0;											// 스켈레톤 프레임 인덱스 초기화
	_health = 5;										// 스켈레톤 체력 초기화
	_pt = { x, y };										// 스켈레톤 중심좌표 초기화
	_body = RectMakeCenter(_pt.x, _pt.y, 130, 100);		// 스켈레톤 위치 초기화
	

	image* newImage = nullptr;
	newImage = new image;
	newImage->init("images/스켈레톤_걷기.bmp", 520, 200, 4, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/스켈레톤_공격.bmp", 390, 200, 3, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/스켈레톤_땅올라오기.bmp", 1170, 100, 9, 1, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/스켈레톤_바닥올라오기.bmp", 1170, 100, 9, 1, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/스켈레톤_벽나옴.bmp", 910, 200, 7, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/스켈레톤_맞음.bmp", 130, 200, 1, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);
	newImage = new image;
	newImage->init("images/스켈레톤_죽음.bmp", 600, 200, 6, 2, true, RGB(255, 0, 255));
	this->imageList.push_back(newImage);

	// ================================================================================================================
	// ############################################## 스켈레톤 이미지 초기화 ##############################################
	// ================================================================================================================
	//IMAGEMANAGER->addFrameImage("스켈레톤_걷기", "images/스켈레톤_걷기.bmp", 520, 200, 4, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("스켈레톤_공격", "images/스켈레톤_공격.bmp", 390, 200, 3, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("스켈레톤_땅올라오기", "images/스켈레톤_땅올라오기.bmp", 1170, 100, 9, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("스켈레톤_바닥올라오기", "images/스켈레톤_바닥올라오기.bmp", 1170, 100, 9, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("스켈레톤_벽나옴", "images/스켈레톤_벽나옴.bmp", 910, 200, 7, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("스켈레톤_맞음", "images/스켈레톤_맞음.bmp", 130, 200, 1, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("스켈레톤_죽음", "images/스켈레톤_죽음.bmp", 600, 200, 6, 2, true, RGB(255, 0, 255));

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
		// 플레이어와 스켈레톤의 거리를 확인
		// 플레이어가 일정간격 안으로 들어오면, true
		if (_find == false) {
			_find = checkPlayer(player->Getpt());
		}
		if (_find) {
			// 플레이어를 계속 바라보게 해준다.
			if (this->_pt.x > player->Getpt().x) {
				_isLeft = true;
			}
			else {
				_isLeft = false;
			}
			// 스켈레톤 모습을 보여준다.
			_show = true;
			// 스켈레톤 초기 상태에 따라 등장 모습이 다르다.
			if (_state == SKE_STATE::IDLE1 ||
				_state == SKE_STATE::IDLE2 || _state == SKE_STATE::IDLE3) {
				showskeleton(_state);
			}
			else {
				// 모습을 완전히 들어냈을 때 충돌 가능
				_crush = true;
				float x = this->_pt.x - player->Getpt().x;
				float y = this->_pt.y - player->Getpt().y;
				// 플레이어와의 거리를 확인
				// 거리가 가까워지면 공격한다.
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
		// ############################## 스켈레톤 픽셀 충돌 처리 ######################################
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
				_pt.y = i - 40;
				break;
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
					_pt.x = i;
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
					_pt.x = i;
					break;
				}
			}
		}
		// ==========================================================================================
		// ########################### 스켈레톤 플레이어총알 충돌 처리 ###################################
		// ==========================================================================================
		for (int i = 0; i < BULLETMAX; i++) {
			RECT _imrc;
			if (!player->GetBullet()[i].getFire()) continue;
			if (IntersectRect(&_imrc, &_crushCheck, &player->GetBullet()[i].getRect()) && _crush == true)
			{
				// 플레이어의 총알에 스켈레톤이 맞으면 체력감소 --
				_health--;
				// 충돌된 총알은 false 처리 해준다.
				player->GetBullet()[i].setFire(false);
			}
		}
		if (_health < 0 ){//&& _state != SKE_STATE::DEATH) {
			_state = SKE_STATE::DEATH;
		}
		// ==========================================================================================
		// ########################### 스켈레톤 플레이어 충돌 처리 ######################################
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
	// #################  RECT 보정 ##########################################################
	_botpt = { _body.left + ((_body.right - _body.left) / 2) , _body.bottom - 14 };
	_leftpt = { _body.left + 15, _body.bottom - 50 };
	_rightpt = { _body.right - 15, _body.bottom - 50 };
	_bot = RectMakeCenter(_botpt.x, _botpt.y, 5, 10);
	_rightCheck = RectMakeCenter(_rightpt.x, _rightpt.y, 10, 5);
	_leftCheck = RectMakeCenter(_leftpt.x, _leftpt.y, 10, 5);
	_crushCheck = RectMakeCenter(_pt.x, _pt.y, 80, 80);
	// #################  RECT 보정 ##########################################################
	
}

void skeleton::render(void)
{
	RECT bodyRC;
	bodyRC.left = _body.left - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.top = _body.top - Camera::getSingleton()->GetCameraRect().top;
	bodyRC.right = _body.right - Camera::getSingleton()->GetCameraRect().left;
	bodyRC.bottom = _body.bottom - Camera::getSingleton()->GetCameraRect().top;
	// 플레이어와 가까워 졌을 때만 화면에 render해준다.
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
			// 왼쪽
			if (_isLeft) { 
				imageList[ImageWall]->setFrameY(0);
			}
			// 오른쪽
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
// 플레이어와 스케렐톤의 거리를 계산해서
// 플레이어가 주변에오면 스켈레톤이 등장
bool skeleton::checkPlayer(POINT playerpt)
{
	// 플레이어를 계속 바라보게 해준다.
	if (this->_pt.x > playerpt.x) {
		_isLeft = true;
	}
	else {
		_isLeft = false;
	}
	float x = this->_pt.x - playerpt.x;
	float y = this->_pt.y - playerpt.y;
	// 플레이어와 스켈레톤의 거리가 150 보다 작아지면
	// 스켈레톤 등장
	if (sqrtf((x*x) + (y * y)) < 350) {
		return true;
	}
	else {
		return false;
	}
}
