#pragma once
#include "gameNode.h"
class TItle : public gameNode
{
private:
	image* _alphabet;			//알파벳 이미지 담을 배열

	// PRESS ENTER START
	RECT _press[5];	RECT _enter[7]; RECT _start[5];
	// CHOI SEOK HWAN
	RECT _choi[4]; RECT _seok[4]; RECT _hwan[4];
	// ONE WEEK PORT FOLIO
	RECT _one[3]; RECT _week[4];
	RECT _port[4]; RECT _folio[5];
	RECT _title;

	int _count;
	bool _check;
				
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TItle() {}
	~TItle() {}
};

