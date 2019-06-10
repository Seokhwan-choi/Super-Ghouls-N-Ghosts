#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Bullet.h"
class Boss : public gameNode
{
private:
	enum BOSS_STATE {
		IDLE,
		BLOOD,
		DIE
	};
	RECT _body;			// 보스 RECT
	int _health;		// 보스 체력
	int _index;			// 보스 프레임 인덱스
	int _count;			// 보스 프레임 카운트
	bool _isDead;		// 보스 죽었냐?
	BOSS_STATE _state;  // 보스 상태
public:
	HRESULT init(void);
	void release(void);
	void update(class Player* player);
	void render(void);

	Boss() {}
	~Boss() {}
};

