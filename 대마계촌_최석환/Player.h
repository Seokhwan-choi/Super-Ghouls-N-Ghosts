#pragma once
#include "gameNode.h"
#include "Bullet.h"
#define BULLETMAX 20
#define FRAMESPEED 5

class Player : public gameNode
{
private:
	enum STATE {			
		IDLE,				// �÷��̾� �⺻ ����	
		RUN,				// �÷��̾� �޸��� ����
		SIT,				// �÷��̾� ���� ����
		JUMP,				// �÷��̾� ���� ����
		LADDER,				// �÷��̾� ��ٸ� ����
		HIT,				// �÷��̾� ���� ����
		DIE,				// �÷��̾� ���� ����
		ATTACK,				// �÷��̾� ���� ����
		UPATTACK,			// �÷��̾� �� ���� ����
		JUMPATTACK,			// �÷��̾� ���� ���� ����
		DOWNATTACK,			// �÷��̾� �Ʒ� ���� ����
		SITATTACK,			// �÷��̾� ���� ���� ����	
	};

	RECT _rc;				// �浹�� RECT
	RECT _crushRect;		// �÷��̾�/���� �浹 RECT
	bool _iscrush;			// �÷��̾� �浹���� ����
	bool _isDead;			// �÷��̾� ���
	bool _isLeft;			// �÷��̾� ��,�� Ȯ��
	bool _isArm;			// �÷��̾� ���� ���� Ȯ��
	bool _isHit;			// �÷��̾� ��Ʈ Ȯ��
	int _count;				// �÷��̾� ������ ī��Ʈ
	int _index;				// �÷��̾� ������ �ε���
	int _attcount;			// �÷��̾� ���� ī��Ʈ
	int _width;				// �÷��̾� �ʺ�
	int _height;			// �÷��̾� ����
	float _gravity;			// �÷��̾� �߷�
	float _jumppw;			// �÷��̾� �����Ŀ�
	int _time;				// �߷��ۿ� Ÿ�̸�
	int _jumpCount;			// ���� ī��Ʈ ( Ƚ�� ���� )
	int _hittime;			// �÷��̾� ��Ʈ Ÿ��
	

	STATE _state;			// �÷��̾� ���� ����
	RECT _body;				// �÷��̾� �̹��� RECT
	POINT _pt;				// �÷��̾� �߽� ��ǥ
	POINT _botpt;			// �÷��̾� ���� ��ǥ
	POINT _leftpt;			// �÷��̾� ���� ��ǥ
	POINT _rightpt;			// �÷��̾� ������ ��ǥ
	RECT _leftCheck;		// �÷��̾� ���ʰ��� RECT
	RECT _rightCheck;		// �÷��̾� �����ʰ��� RECT
	RECT _bot;				// �÷��̾� �ٴڰ��� RECT
	Bullet* _bullet;	    // �÷��̾� �Ѿ�
	int _probeY;			// Y Ž����
	int _probeX;			// X Ž����

	bool _check;			// Ȯ��
	int _alpha;				// ���İ�
	
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

