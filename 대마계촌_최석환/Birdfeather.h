#pragma once
#include "gameNode.h"
class Birdfeather : public gameNode
{
private:
	RECT _body;			// µ¶¼ö¸® ±êÅĞ RECT
	POINT _pt;			// µ¶¼ú¸® ±êÅĞ ÁÂÇ¥
	float _gravity;		// µ¶¼ö¸® ±êÅĞ Áß·Â
	int _count;			// µ¶¼ö¸® ±êÅĞ ÇÁ·¹ÀÓ Ä«¿îÆ®
	int _index;			// µ¶¼ö¸® ±êÅĞ ÇÁ·¹ÀÓ ÀÎµ¦½º
	bool _check;		// µ¶¼ö¸® ±êÅĞ È®ÀÎ
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

