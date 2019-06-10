#pragma once
#include "End.h"
#include "TItle.h"
#include "Playgame.h"
#include "Player.h"

#define CAMSIZEX 1000
#define CAMSIZEY 672

class mainGame : public gameNode
{
private:
	End * _endScene;			// ��������
	Playgame * _playScene;		// ����ȭ��
	TItle* _titleScene;			// ����ȭ��
	gameNode* _currentScene;	// ���� ��
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	mainGame() {}
	~mainGame() {}
};

