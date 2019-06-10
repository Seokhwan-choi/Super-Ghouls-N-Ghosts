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
	RECT _body;			// ���� RECT
	int _health;		// ���� ü��
	int _index;			// ���� ������ �ε���
	int _count;			// ���� ������ ī��Ʈ
	bool _isDead;		// ���� �׾���?
	BOSS_STATE _state;  // ���� ����
public:
	HRESULT init(void);
	void release(void);
	void update(class Player* player);
	void render(void);

	Boss() {}
	~Boss() {}
};

