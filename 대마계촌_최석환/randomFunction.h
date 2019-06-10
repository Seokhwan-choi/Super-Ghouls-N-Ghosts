#pragma once
#include "singletonBase.h"

class randomFunction : public singletonBase <randomFunction>
{
public:
	HRESULT init(void);
	void release(void);

	//GetInt
	int range(int num);
	//GetFromIntTo
	int range(int fromNum, int toNum);
	//GetFloat
	float range(float num);
	//GetFromFloatTo
	float range(float fromNum, float toNum);

	randomFunction() {}
	~randomFunction() {}
};

