#pragma once
#include "gameNode.h"
#include "Bullet.h"
#define BULLETMAX 20
#define FRAMESPEED 5

class Player : public gameNode
{
private:
	enum STATE {			
		IDLE,				// 플레이어 기본 상태	
		RUN,				// 플레이어 달리기 상태
		SIT,				// 플레이어 앉음 상태
		JUMP,				// 플레이어 점프 상태
		LADDER,				// 플레이어 사다리 상태
		HIT,				// 플레이어 맞음 상태
		DIE,				// 플레이어 죽음 상태
		ATTACK,				// 플레이어 공격 상태
		UPATTACK,			// 플레이어 위 공격 상태
		JUMPATTACK,			// 플레이어 점프 공격 상태
		DOWNATTACK,			// 플레이어 아래 공격 상태
		SITATTACK,			// 플레이어 앉음 공격 상태	
	};

	RECT _rc;				// 충돌용 RECT
	RECT _crushRect;		// 플레이어/몬스터 충돌 RECT
	bool _iscrush;			// 플레이어 충돌가능 여부
	bool _isDead;			// 플레이어 사망
	bool _isLeft;			// 플레이어 좌,우 확인
	bool _isArm;			// 플레이어 갑옷 착용 확인
	bool _isHit;			// 플레이어 히트 확인
	int _count;				// 플레이어 프레임 카운트
	int _index;				// 플레이어 프레임 인덱스
	int _attcount;			// 플레이어 공격 카운트
	int _width;				// 플레이어 너비
	int _height;			// 플레이어 높이
	float _gravity;			// 플레이어 중력
	float _jumppw;			// 플레이어 점프파워
	int _time;				// 중력작용 타이머
	int _jumpCount;			// 점프 카운트 ( 횟수 제한 )
	int _hittime;			// 플레이어 히트 타임
	

	STATE _state;			// 플레이어 상태 저장
	RECT _body;				// 플레이어 이미지 RECT
	POINT _pt;				// 플레이어 중심 좌표
	POINT _botpt;			// 플레이어 바텀 좌표
	POINT _leftpt;			// 플레이어 왼쪽 좌표
	POINT _rightpt;			// 플레이어 오른쪽 좌표
	RECT _leftCheck;		// 플레이어 왼쪽감지 RECT
	RECT _rightCheck;		// 플레이어 오른쪽감지 RECT
	RECT _bot;				// 플레이어 바닥감지 RECT
	Bullet* _bullet;	    // 플레이어 총알
	int _probeY;			// Y 탐사축
	int _probeX;			// X 탐사축

	bool _check;			// 확인
	int _alpha;				// 알파값
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void SetPtY(int y) { _pt.y = y; }
	int GetWidth() { return _width; }
	int GetHeight() { return _height; }
	bool GetisCrush() { return _iscrush; }
	bool GetisDead() { return _isDead; }
	bool GetHit() { return _isHit; }
	Bullet* GetBullet() { return _bullet; }
	RECT GetCrush() { return _crushRect; }
	POINT Getpt() { return _pt; }


	void hitPlayer();
	void armState(int num);
	void narmState(int num);

	Player() {}
	~Player() {}
};

