#include "stdafx.h"
#include "mainGame.h"
//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	
	_endScene = new End;
	_playScene = new Playgame;
	_titleScene = new TItle;
	_titleScene->init();

	_currentScene = _titleScene;


	return S_OK;
	//return S_OK; 아래에 코드가 있으면 안됨!!!
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();


	_playScene->release();
	_titleScene->release();
	SAFE_DELETE(_playScene);
	SAFE_DELETE(_titleScene)

}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void mainGame::update(void)
{
	gameNode::update();

	//(งಠل͜ಠ)ง 뚜싯뚜싯

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
		_isDebug = !_isDebug;

	_currentScene->update();
	if (UIMANAGER->GetLife() == 0) {
		_currentScene = _endScene;
		_endScene->init();
	}
	if (UIMANAGER->GetTime() == 0) {
		_currentScene = _endScene;
		_endScene->init();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {

		if (_currentScene == _endScene) {
			this->init();
		}
		_currentScene = _playScene;
		_currentScene->init();
	}
}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================
	//이곳에서 WM_PAINT에서 했던것을 처리하면 된다
	
	//현재씬만 렌더
	_currentScene->render();

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());
}
