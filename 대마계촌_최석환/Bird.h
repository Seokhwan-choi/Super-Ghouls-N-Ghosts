#pragma once
#include "gameNode.h"
#include "Birdfeather.h"
#define FEATHERMAX 5

enum class BIRD_STATE : int {
	IDLE,						// 독수리 기본 상태
	IDLEJUMP,					// 독수리 기본점프 상태
	//IDLETURN,					// 독수리 기본돌아오기 상태
	JUMP,						// 독수리 점프 상태
	FLY,						// 독수리 날기 상태
	HIT,						// 독수리 맞음 상태
	DIE							// 독수리 죽음 상태
};

class Bird : public gameNode
{
private:
	Birdfeather* _birdfeather;	// 독수리 깃털
	POINT _pt;					// 독수리 좌표
	RECT _crushRect;			// 독수리 충돌 RECT
	RECT _body;					// 독수리 RECT
	float _gravity;				// 독수리 중력
	float _jumppw;				// 독수리 점프파워
	int _health;				// 독수리 체력
	int _index;					// 독수리 프레임 인덱스
	int _count;					// 독수리 프레임 카운트
	bool _isLeft;				// 독수리 좌,우 확인
	bool _find;					// 독수리 플레이어 찾았냐?
	bool _isDead;				// 독수리 죽었냐?
	bool _crush;				// 독수리 충돌가능
	BIRD_STATE _state;			// 독수리 상태

	vector<class image*> imagelist;
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(class Player* player);
	void render(void);

	Bird() {}
	~Bird() {}
};

