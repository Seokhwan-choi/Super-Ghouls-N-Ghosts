#pragma once
#include "gameNode.h"

enum class WAY : int {
	LEFT,			// 왼쪽
	RIGHT,			// 오른쪽
	UP,				// 위
	DOWN			// 아래
};

class Bullet : public gameNode
{
private:
	int _time;			// 총알 지속시간
	bool _fire;			// 총알 발사 여부
	WAY _way;			// 총알 방향 확인
	RECT _rc;			// 총알 RECT
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	RECT getRect() { return _rc; }
	void setFire(bool fire) { _fire = fire; }
	bool getFire() { return _fire; }
	void setWay(WAY way) { _way = way; }
	
	void Fire(POINT pt);
	void move();

	Bullet() {}
	~Bullet() {}
};

