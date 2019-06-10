#include "stdafx.h"
#include "Bird.h"
#include "Player.h"
#include "Bullet.h"
#define FRAMESPEED 5

HRESULT Bird::init(int x, int y)
{

	_index = 0;													// 독수리 프레임 인덱스 초기화
	_count = 0;													// 독수리 프레임 카운트 초기화
	_isLeft = true;												// 독수리 좌,우 초기화
	_isDead = false;											// 독수리 죽었냐?
	_find = false;												// 독수리가 플레이어 찾았냐?
	_crush = true;												// 독수리 충돌가능
	_health = 5;												// 독수리 체력
	_gravity = 0.3f;											// 독수리 중력 초기화
	_jumppw = 6.0f;												// 독수리 점프파워 초기화
	_pt = { x, y };												// 독수리 좌표 초기화
	_state = (BIRD_STATE)RND->range(2);							// 독수리 랜점 상태 초기화
	_body = RectMakeCenter(_pt.x, _pt.y, 125, 100);				// 독수리 RECT 초기화
	_crushRect = RectMakeCenter(_pt.x, _pt.y + 25, 100, 50);	// 독수리 충돌 RECT 초기화
	_birdfeather = new Birdfeather[FEATHERMAX];					// 독수리 깃털 초기화
	for (int i = 0; i < FEATHERMAX; i++) {
		_birdfeather[i].init();
	}

	image* newImage = nullptr;
	newImage = new image;
	newImage->init("images/독수리_기본털.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/독수리_기본점프.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/독수리_뜬다.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/독수리_날기.bmp", 750, 200, 6, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/독수리_맞음.bmp", 125, 200, 1, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);
	newImage = new image;
	newImage->init("images/독수리_죽음.bmp", 750, 200, 6, 2, true, RGB(255, 0, 255));
	imagelist.push_back(newImage);







	// ====================================================================================================================
	// ############################################ 독수리 이미지 초기화 #####################################################
	// ====================================================================================================================
	//IMAGEMANAGER->addFrameImage("독수리_기본돌아오기", "images/독수리_기본돌아오기.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("독수리_기본점프", "images/독수리_기본점프.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("독수리_기본털", "images/독수리_기본털.bmp", 625, 200, 5, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("독수리_뜬다", "images/독수리_뜬다.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("독수리_날기", "images/독수리_날기.bmp", 750, 200, 6, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("독수리_맞음", "images/독수리_맞음.bmp", 125, 200, 1, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("독수리_죽음", "images/독수리_죽음.bmp", 750, 200, 6, 2, true, RGB(255, 0, 255));
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
	// 플레이어와 독수리의 거리를 확인
	// 플레이어가 일정간격 안으로 들어오면, true
	if (!_isDead) 
	{
		float x = this->_pt.x - player->Getpt().x;
		float y = this->_pt.y - player->Getpt().y;
		// 플레이어와의 거리를 확인
		// 거리가 가까워지면 공격한다.
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
		//	IMAGEMANAGER->findImage("독수리_기본돌아오기")->setFrameY(1);
		//	if (_count % (FRAMESPEED*2) == 0) {
		//		_index++;
		//		if (_index > 5) {
		//			_index = 0;
		//		}
		//		IMAGEMANAGER->findImage("독수리_기본돌아오기")->setFrameX(_index);
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
		// ############################ 독수리 플레이어 총알 충돌 처리 ##################################
		// ==========================================================================================
		for (int i = 0; i < BULLETMAX; i++) {
			RECT _imrc;
			if (!player->GetBullet()[i].getFire()) continue;
			if (IntersectRect(&_imrc, &_crushRect, &player->GetBullet()[i].getRect()) && _crush == true)
			{
				// 플레이어의 총알에 스켈레톤이 맞으면 체력감소 --
				_health--;
				// 충돌된 총알은 false 처리 해준다.
				player->GetBullet()[i].setFire(false);
			}
		}

		// ==========================================================================================
		// ############################ 독수리 플레이어 충돌 처리 #######################################
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
	
	_crushRect = RectMakeCenter(_pt.x, _pt.y + 25, 100, 50);	// 독수리 충돌 RECT 초기화
	_body = RectMakeCenter(_pt.x, _pt.y, 125, 100);				// 독수리 RECT 초기화
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
		//	IMAGEMANAGER->frameRender("독수리_기본돌아오기", getMemDC(), bodyRC.left, bodyRC.top);
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
