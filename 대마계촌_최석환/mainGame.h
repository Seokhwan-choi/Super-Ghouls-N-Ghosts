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
	End * _endScene;			// 게임종료
	Playgame * _playScene;		// 게임화면
	TItle* _titleScene;			// 시작화면
	gameNode* _currentScene;	// 현재 씬
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	mainGame() {}
	~mainGame() {}
};

