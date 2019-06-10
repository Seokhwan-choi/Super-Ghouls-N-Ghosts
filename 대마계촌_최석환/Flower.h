#pragma once
#include "gameNode.h"
#include "FlowerBullet.h"
#include <math.h>
#define FLOWERBULLET 3
#define PI 3.141592f

enum class FLOWER_STATE : int 
{
	SHOW,						// �ذ�� ����
	IDLE,						// �ذ�� �⺻
	MOVE_LEFT,					// �ذ�� ���� �̵�
	MOVE_RIGHT,					// �ذ�� ������ �̵�
	ATTACK,						// �ذ�� ����
	DIE							// �ذ�� ����
};

class Flower : public gameNode
{
private:

	FlowerBullet* _bullet;			// �ذ�� �Ѿ� 
	RECT _body;						// �ذ�� RECT
	POINT _pt;						// �ذ�� ��ǥ
	int _health;					// �ذ�� ü��
	int _index;						// �ذ�� ������ �ε���
	int _count;						// �ذ�� ������ ī��Ʈ
	int _time;						// �ذ�� �ð� Ȯ��
	int _movecount;					// �ذ�� ���� ī��Ʈ

	float _gravity;					// �ذ�� �߷�
	float _jumppw;					// �ذ�� �����Ŀ�
	int _probeY;					// Y�� Ž��
	int _probeX;					// X�� Ž��
									
	POINT _botpt;					// �ذ�� ���� ��ǥ
	POINT _leftpt;					// �ذ�� ���� ��ǥ
	POINT _rightpt;					// �ذ�� ������ ��ǥ
	RECT _leftCheck;				// �ذ�� ���ʰ��� RECT
	RECT _rightCheck;				// �ذ�� �����ʰ��� RECT
	RECT _bot;						// �ذ�� �ٴڰ��� RECT

	FLOWER_STATE _state;			// �ذ�� ����
	bool _find;						// �ذ�� �÷��̾� ã�ҳ�?
	bool _show;						// �ذ�� �����ֳ�?
	bool _crush;					// �ذ�� �浹 ����
	bool _isDead;					// �ذ�� ����?
	bool _attack;					// �ذ�� ���ݰ���?

	vector<class image*> imagelist;

public:

	HRESULT init(int x, int y);
	void release(void);
	void update(class Player* player);
	void render(void);

	bool checkPlayer(POINT playerpt);


	Flower() {}
	~Flower() {}
};

