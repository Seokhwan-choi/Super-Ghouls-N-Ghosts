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
	IDLE1,				// ���̷��� ����1
	IDLE2,				// ���̷��� ����2
	IDLE3,				// ���̷��� ����3
	WALK,				// ���̷��� �ȱ�
	ATTACK,				// ���̷��� ����
	HIT,				// ���̷��� ����
	DEATH,				// ���̷��� ����
};

class skeleton : public gameNode
{
private:
	
	SKE_STATE _state;		// ���̷��� ���� Ȯ��
	bool _isLeft;			// ���̷��� ��,�� Ȯ��
	RECT _body;				// ���̷��� RECT

	POINT _pt;				// ���̷��� �߽� ��ǥ
	POINT _botpt;			// ���̷��� ���� ��ǥ
	POINT _leftpt;			// ���̷��� ���� ��ǥ
	POINT _rightpt;			// ���̷��� ������ ��ǥ
	RECT _leftCheck;		// ���̷��� ���ʰ��� RECT
	RECT _rightCheck;		// ���̷��� �����ʰ��� RECT
	RECT _bot;				// ���̷��� �ٴڰ��� RECT
	RECT _crushCheck;		// ���̷��� �浹���� RECT

	int _count;				// ���̷��� ������ ī��Ʈ
	int _index;				// ���̷��� ������ �ε���
	int _health;			// ���̷��� ü��
	int _crush;				// ���̷��� �浹����
	int _attacktime;		// ���̷��� ���� ��Ÿ��
	bool _show;				// ���̷��� �����ش�
	bool _attack;			// ���̷��� �������̳� ?
	bool _find;				// �÷��̾ ã����
	bool _isDead;			// ���̷��� �׾���?
	bool _isHit;			// ���̷��� �¾ҳ�?

	float _gravity;			// ���̷��� �߷�
	float _jumppw;			// ���̷��� �����Ŀ�

	int _probeY;			// Y�� Ž��
	int _probeX;			// X�� Ž��

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

