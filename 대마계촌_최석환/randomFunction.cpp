#include "stdafx.h"
#include "randomFunction.h"

HRESULT randomFunction::init(void)
{
	//랜덤시드 초기화
	//srand(time(NULL));
	srand(GetTickCount());
	return S_OK;
}
void randomFunction::release(void)
{
}

//0 ~ (num-1) 사이의 랜덤값
int randomFunction::range(int num)
{
	return rand() % num;
}

//fromNum ~ toNum 사이의 랜덤값
int randomFunction::range(int fromNum, int toNum)
{
	return rand() % (toNum - fromNum + 1) + fromNum;
}

float randomFunction::range(float num)
{
	return ((float)rand() / (float)RAND_MAX) *num;
}

float randomFunction::range(float fromNum, float toNum)
{
	float rnd = (float)rand() / (float)RAND_MAX;
	return (rnd * (toNum - fromNum) + fromNum);
}
