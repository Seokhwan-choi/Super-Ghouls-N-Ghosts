#pragma once
#include "singletonBase.h"
class Camera : public singletonBase<Camera>
{
private:
	POINT pos;
	RECT rc;
public:
	Camera() {}
	~Camera() {}

	void SetCameraPosition(POINT pos);

	RECT GetCameraRect()const { return this->rc; }
};

