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
	vector<skeleton*> _enemy;	//스켈레톤 몬스터 클래스
	vector<Flower*> _enemy2;	//해골꽃 몬스터 클래스
	vector<Bird*> _enemy3;		//독수리 몬스터 클래스
	Boss* _boss;				//보스 몬스터 클래스

	Player * _player;			// Player 클래스
	UI* _ui;					//UI 클래스
	image* _img;				//백그라운드 이미지
	image* _pixel;				//백그라운드 픽셀
	int _time;					//시간체크
public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	void initmonster();

	Playgame() {}
	~Playgame() {}
};

