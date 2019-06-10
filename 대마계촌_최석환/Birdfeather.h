#pragma once
#include "gameNode.h"
class Birdfeather : public gameNode
{
private:
	RECT _body;			// ������ ���� RECT
	POINT _pt;			// ������ ���� ��ǥ
	float _gravity;		// ������ ���� �߷�
	int _count;			// ������ ���� ������ ī��Ʈ
	int _index;			// ������ ���� ������ �ε���
	bool _check;		// ������ ���� Ȯ��
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool GetCheck() { return _check; }
	void Boom(POINT playerpt);
	void move();

	Birdfeather() {}
	~Birdfeather() {}
};

