#pragma once
#include "gameNode.h"
#define ImageWalk 0
#define ImageAttack 1
#define ImageGroundUp 2
#define ImageFloorUp 3
#define ImageWall 4
#define ImageHit 5
#define ImageDie 6



enum class SKE_STATE : int {
	IDLE1,				// 스켈레톤 등장1
	IDLE2,				// 스켈레톤 등장2
	IDLE3,				// 스켈레톤 등장3
	WALK,				// 스켈레톤 걷기
	ATTACK,				// 스켈레톤 공격
	HIT,				// 스켈레톤 맞음
	DEATH,				// 스켈레톤 죽음
};

class skeleton : public gameNode
{
private:
	
	SKE_STATE _state;		// 스켈레톤 상태 확인
	bool _isLeft;			// 스켈레톤 좌,우 확인
	RECT _body;				// 스켈레톤 RECT

	POINT _pt;				// 스켈레톤 중심 좌표
	POINT _botpt;			// 스켈레톤 바텀 좌표
	POINT _leftpt;			// 스켈레톤 왼쪽 좌표
	POINT _rightpt;			// 스켈레톤 오른쪽 좌표
	RECT _leftCheck;		// 스켈레톤 왼쪽감지 RECT
	RECT _rightCheck;		// 스켈레톤 오른쪽감지 RECT
	RECT _bot;				// 스켈레톤 바닥감지 RECT
	RECT _crushCheck;		// 스켈레톤 충돌감지 RECT

	int _count;				// 스켈레톤 프레임 카운트
	int _index;				// 스켈레톤 프레임 인덱스
	int _health;			// 스켈레톤 체력
	int _crush;				// 스켈레톤 충돌가능
	int _attacktime;		// 스켈레톤 공격 쿨타임
	bool _show;				// 스켈레톤 보여준다
	bool _attack;			// 스켈레톤 공격중이냐 ?
	bool _find;				// 플레이어를 찾았음
	bool _isDead;			// 스켈레톤 죽었냐?
	bool _isHit;			// 스켈레톤 맞았냐?

	float _gravity;			// 스켈레톤 중력
	float _jumppw;			// 스켈레톤 점프파워

	int _probeY;			// Y축 탐사
	int _probeX;			// X축 탐사

	vector <class image*> imageList;


public:

	HRESULT init(int x, int y, SKE_STATE state); 
	void release(void);
	void update(class Player* player);
	void render(void);

	int Gethealth() { return _health; }
	void Sethealth(int health) { _health = health; }

	void showskeleton(SKE_STATE state);
	bool checkPlayer(POINT playerpt);

	skeleton() {}
	~skeleton() {}
};

