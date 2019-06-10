#pragma once
#include "singletonBase.h"

enum class WEAP : int {
	SPEAR,			// Ã¢
	DAGUE			// ´Ü°Ë
};

class uiManager : public singletonBase<uiManager>
{
private:
	int _score;
	int _life;
	int _time;
	WEAP _weap;
public:
	HRESULT init(void);
	void release(void);
	uiManager() {}
	~uiManager() {}

	int GetScore() { return _score; }
	void SetScore(int score) { _score = score; }
	int GetLife() { return _life; }
	void SetLife(int life) { _life = life; }
	int GetTime() { return _time; }
	void SetTime(int time) { _time = time; }
	WEAP GetWeap() { return _weap; }
	int SetWeap(WEAP weap) { _weap = weap; }
};

