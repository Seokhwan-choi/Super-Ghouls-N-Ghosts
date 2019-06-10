#pragma once
#include "gameNode.h"
#include <math.h>
#define PI 3.141592f
class FlowerBullet : public gameNode
{
private:
	enum LR {
		LEFT,
		RIGHT
	};
	RECT _rc;				// �ذ�� �Ѿ� RECT
	POINT _pt;				// �ذ�� �Ѿ� ��ǥ
	int _count;				// �ذ�� �Ѿ� ������ ī��Ʈ
	int _index;				// �ذ�� �Ѿ� ������ �ε���
	int _time;				// �ذ�� �Ѿ� �߷� �ð�
	float _gravity;			// �ذ�� �Ѿ� �߷�(������)
	float _angle;			// �ذ�� �Ѿ� ����(������)
	bool _fire;				// �ذ�� �Ѿ� �߻�
	LR _state;				// �ذ�� �Ѿ� ����
	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	RECT GetRect() { return _rc; }
	bool GetFire() { return _fire; }
	void SetAngle(float angle) { _angle = angle; }

	FlowerBullet() {}
	~FlowerBullet() {}

	void move();
	void Fire(POINT pt);
};

