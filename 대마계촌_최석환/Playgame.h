#pragma once
#include "gameNode.h"
#include "Boss.h"
#include "Player.h"
#include "skeleton.h"
#include "Flower.h"
#include "Bird.h"
#include "UI.h"

class Playgame : public gameNode
{
private:
	vector<skeleton*> _enemy;	//���̷��� ���� Ŭ����
	vector<Flower*> _enemy2;	//�ذ�� ���� Ŭ����
	vector<Bird*> _enemy3;		//������ ���� Ŭ����
	Boss* _boss;				//���� ���� Ŭ����

	Player * _player;			// Player Ŭ����
	UI* _ui;					//UI Ŭ����
	image* _img;				//��׶��� �̹���
	image* _pixel;				//��׶��� �ȼ�
	int _time;					//�ð�üũ
public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	void initmonster();

	Playgame() {}
	~Playgame() {}
};

