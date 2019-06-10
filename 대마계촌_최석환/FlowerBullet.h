#pragma once
#include "gameNode.h"
#include <math.h>
#define PI 3.141592f
class FlowerBullet : public gameNode
{
private:
	enum LR {
		LEFT,
		RIGHT
	};
	RECT _rc;				// ÇØ°ñ²É ÃÑ¾Ë RECT
	POINT _pt;				// ÇØ°ñ²É ÃÑ¾Ë ÁÂÇ¥
	int _count;				// ÇØ°ñ²É ÃÑ¾Ë ÇÁ·¹ÀÓ Ä«¿îÆ®
	int _index;				// ÇØ°ñ²É ÃÑ¾Ë ÇÁ·¹ÀÓ ÀÎµ¦½º
	int _time;				// ÇØ°ñ²É ÃÑ¾Ë Áß·Â ½Ã°£
	float _gravity;			// ÇØ°ñ²É ÃÑ¾Ë Áß·Â(Æ÷¹°¼±)
	float _angle;			// ÇØ°ñ²É ÃÑ¾Ë °¢µµ(Æ÷¹°¼±)
	bool _fire;				// ÇØ°ñ²É ÃÑ¾Ë ¹ß»ç
	LR _state;				// ÇØ°ñ²É ÃÑ¾Ë »óÅÂ
	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	RECT GetRect() { return _rc; }
	bool GetFire() { return _fire; }
	void SetAngle(float angle) { _angle = angle; }

	FlowerBullet() {}
	~FlowerBullet() {}

	void move();
	void Fire(POINT pt);
};

