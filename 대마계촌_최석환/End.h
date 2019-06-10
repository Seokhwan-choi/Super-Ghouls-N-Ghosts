#pragma once
#include "gameNode.h"
class End : public gameNode
{
private:
	RECT _end;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	End() {}
	~End() {}
};

