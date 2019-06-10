#pragma once
#include "gameNode.h"

enum class WAY : int {
	LEFT,			// ����
	RIGHT,			// ������
	UP,				// ��
	DOWN			// �Ʒ�
};

class Bullet : public gameNode
{
private:
	int _time;			// �Ѿ� ���ӽð�
	bool _fire;			// �Ѿ� �߻� ����
	WAY _way;			// �Ѿ� ���� Ȯ��
	RECT _rc;			// �Ѿ� RECT
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

