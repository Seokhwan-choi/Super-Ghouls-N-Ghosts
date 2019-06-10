#pragma once
#include "gameNode.h"
#include "Birdfeather.h"
#define FEATHERMAX 5

enum class BIRD_STATE : int {
	IDLE,						// ������ �⺻ ����
	IDLEJUMP,					// ������ �⺻���� ����
	//IDLETURN,					// ������ �⺻���ƿ��� ����
	JUMP,						// ������ ���� ����
	FLY,						// ������ ���� ����
	HIT,						// ������ ���� ����
	DIE							// ������ ���� ����
};

class Bird : public gameNode
{
private:
	Birdfeather* _birdfeather;	// ������ ����
	POINT _pt;					// ������ ��ǥ
	RECT _crushRect;			// ������ �浹 RECT
	RECT _body;					// ������ RECT
	float _gravity;				// ������ �߷�
	float _jumppw;				// ������ �����Ŀ�
	int _health;				// ������ ü��
	int _index;					// ������ ������ �ε���
	int _count;					// ������ ������ ī��Ʈ
	bool _isLeft;				// ������ ��,�� Ȯ��
	bool _find;					// ������ �÷��̾� ã�ҳ�?
	bool _isDead;				// ������ �׾���?
	bool _crush;				// ������ �浹����
	BIRD_STATE _state;			// ������ ����

	vector<class image*> imagelist;
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(class Player* player);
	void render(void);

	Bird() {}
	~Bird() {}
};

