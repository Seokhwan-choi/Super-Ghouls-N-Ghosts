#pragma once
#include "gameNode.h"
#include "FlowerBullet.h"
#include <math.h>
#define FLOWERBULLET 3
#define PI 3.141592f

enum class FLOWER_STATE : int 
{
	SHOW,						// ÇØ°ñ²É µîÀå
	IDLE,						// ÇØ°ñ²É ±âº»
	MOVE_LEFT,					// ÇØ°ñ²É ¿ÞÂÊ ÀÌµ¿
	MOVE_RIGHT,					// ÇØ°ñ²É ¿À¸¥ÂÊ ÀÌµ¿
	ATTACK,						// ÇØ°ñ²É °ø°Ý
	DIE							// ÇØ°ñ²É Á×À½
};

class Flower : public gameNode
{
private:

	FlowerBullet* _bullet;			// ÇØ°ñ²É ÃÑ¾Ë 
	RECT _body;						// ÇØ°ñ²É RECT
	POINT _pt;						// ÇØ°ñ²É ÁÂÇ¥
	int _health;					// ÇØ°ñ²É Ã¼·Â
	int _index;						// ÇØ°ñ²É ÇÁ·¹ÀÓ ÀÎµ¦½º
	int _count;						// ÇØ°ñ²É ÇÁ·¹ÀÓ Ä«¿îÆ®
	int _time;						// ÇØ°ñ²É ½Ã°£ È®ÀÎ
	int _movecount;					// ÇØ°ñ²É ¹«ºù Ä«¿îÆ®

	float _gravity;					// ÇØ°ñ²É Áß·Â
	float _jumppw;					// ÇØ°ñ²É Á¡ÇÁÆÄ¿ö
	int _probeY;					// YÃà Å½»ç
	int _probeX;					// XÃà Å½»ç
									
	POINT _botpt;					// ÇØ°ñ²É ¹ÙÅÒ ÁÂÇ¥
	POINT _leftpt;					// ÇØ°ñ²É ¿ÞÂÊ ÁÂÇ¥
	POINT _rightpt;					// ÇØ°ñ²É ¿À¸¥ÂÊ ÁÂÇ¥
	RECT _leftCheck;				// ÇØ°ñ²É ¿ÞÂÊ°¨Áö RECT
	RECT _rightCheck;				// ÇØ°ñ²É ¿À¸¥ÂÊ°¨Áö RECT
	RECT _bot;						// ÇØ°ñ²É ¹Ù´Ú°¨Áö RECT

	FLOWER_STATE _state;			// ÇØ°ñ²É »óÅÂ
	bool _find;						// ÇØ°ñ²É ÇÃ·¹ÀÌ¾î Ã£¾Ò³Ä?
	bool _show;						// ÇØ°ñ²É º¸¿©ÁÖ³Ä?
	bool _crush;					// ÇØ°ñ²É Ãæµ¹ °¡´É
	bool _isDead;					// ÇØ°ñ²É Á×À½?
	bool _attack;					// ÇØ°ñ²É °ø°Ý°¡´É?

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

