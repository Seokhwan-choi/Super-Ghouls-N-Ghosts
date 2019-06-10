#pragma once
#include "gameNode.h"

class UI : public gameNode
{
private:
	
	RECT _num[5];
	RECT _score[5];
	RECT _time[4];
	RECT _timenum[5];
	RECT _life[2];
	RECT _lifeshape;
	RECT _timeshape;
	RECT _weapshape;

	WEAP _weap;
	bool _check;
public:
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void SetLife(int life);
	void SetTime(int time);
	void SetScore(int score);
	void SetWeap(WEAP weap);

	UI() {}
	~UI() {}
};

