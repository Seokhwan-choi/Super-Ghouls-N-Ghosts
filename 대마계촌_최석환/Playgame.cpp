#include "stdafx.h"
#include "Playgame.h"
#define SKELMMAX 16
#define FLOWMAX 5
#define BIRDMAX 8

HRESULT Playgame::init()
{
	//이곳에서 초기화를 한다
	_player = new Player;
	_player->init();

	for (int i = 0; i < SKELMMAX; i++) {
		_enemy.push_back(new skeleton);
	}
	
	for (int i = 0; i < BIRDMAX; i++) {
		_enemy3.push_back(new Bird);
	}
	
	for (int i = 0; i < FLOWMAX; i++) {
		_enemy2.push_back(new Flower);
	}
	_boss = new Boss;
	
	initmonster();

	_img = IMAGEMANAGER->addImage("배경", "images/마계촌배경.bmp", 8612, 672);
	_pixel = IMAGEMANAGER->addImage("픽셀", "images/픽셀충돌용배경.bmp", 8612, 672);

	_ui = new UI;
	_ui->init();
	return S_OK;
}

void Playgame::release(void)
{
	for (int i = 0; i < SKELMMAX; i++) {
		_enemy[i]->release();
	}
	for (int i = 0; i < FLOWMAX; i++) {
		_enemy2[i]->release();
	}
	for (int i = 0; i < BIRDMAX; i++) {
		_enemy3[i]->release();
	}

	for (int i = 0; i < _enemy.size(); i++) {
		_enemy[i]->release();
		SAFE_DELETE(_enemy[i]);
	}
	_enemy.clear();

	for (int i = 0; i < _enemy2.size(); i++) {
		_enemy2[i]->release();
		SAFE_DELETE(_enemy2[i]);
	}
	_enemy2.clear();

	for (int i = 0; i < _enemy3.size(); i++) {
		_enemy3[i]->release();
		SAFE_DELETE(_enemy3[i]);
	}
	_enemy3.clear();
}

void Playgame::update(void)
{
	_time++;
	gameNode::update();
	
	_player->update();
	_boss->update(_player);
	for (int i = 0; i < SKELMMAX; i++) {
		_enemy[i]->update(_player);
	}

	for (int i = 0; i < FLOWMAX; i++) {
		_enemy2[i]->update(_player);
	}
	
	for (int i = 0; i < BIRDMAX; i++) {
		_enemy3[i]->update(_player);
	}
	_ui->update();

	// 게임 시간 1초씩 감소
	if (_time % 100 == 0) {
		UIMANAGER->SetTime(UIMANAGER->GetTime() - 1);
	}

	if (_time % 150 == 0 && UIMANAGER->GetLife() > 0 && _player->GetisDead()) {
		UIMANAGER->SetLife(UIMANAGER->GetLife() - 1);
		_player->init();
		this->initmonster();
	}

	//if (UIMANAGER->GetTime() == 0) {
	//	UIMANAGER->SetLife(UIMANAGER->GetLife() - 1);
	//	_player->init();
	//	this->initmonster();
	//}

}

void Playgame::render(void)
{
	_img->render(getMemDC(), 0 - Camera::getSingleton()->GetCameraRect().left, 0 - Camera::getSingleton()->GetCameraRect().top);
	//_img->render(getMemDC(), 0, 0, _rcCamera.left + _img->getX(), _img->getY() + _rcCamera.top, CAMSIZEX, CAMSIZEY);
	if (_isDebug) {
		_pixel->render(getMemDC(), 0 - Camera::getSingleton()->GetCameraRect().left, 0 - Camera::getSingleton()->GetCameraRect().top);
	}

	_player->render();
	_boss->render();
	for (int i = 0; i < SKELMMAX; i++) {
		_enemy[i]->render();
	}

	for (int i = 0; i < FLOWMAX; i++) {
		_enemy2[i]->render();
	}

	for (int i = 0; i < BIRDMAX; i++) {
		_enemy3[i]->render();
	}
	_ui->render();
}

void Playgame::initmonster()
{
	
	_enemy[0]->init(996, 498, SKE_STATE::IDLE1);
	_enemy[1]->init(600, 430, SKE_STATE::IDLE2);
	_enemy[2]->init(731, 439, SKE_STATE::IDLE3);
	_enemy[3]->init(1930, 338, SKE_STATE::IDLE3);

	_enemy[4]->init(2550, 285, SKE_STATE::IDLE2);
	_enemy[5]->init(2645, 510, SKE_STATE::IDLE1);
	_enemy[6]->init(3157, 520, SKE_STATE::IDLE3);

	_enemy[7]->init(4057, 485, SKE_STATE::IDLE3);
	_enemy[8]->init(4293, 290, SKE_STATE::IDLE2);
	_enemy[9]->init(5282, 341, SKE_STATE::IDLE1);

	_enemy[10]->init(3930, 488, SKE_STATE::IDLE1);
	_enemy[11]->init(5900, 450, SKE_STATE::IDLE2);
	_enemy[12]->init(6124, 500, SKE_STATE::IDLE3);
	_enemy[13]->init(6279, 500, SKE_STATE::IDLE1);
	_enemy[13]->init(6435, 541, SKE_STATE::IDLE2);
	_enemy[14]->init(7621, 435, SKE_STATE::IDLE3);
	_enemy[15]->init(7878, 412, SKE_STATE::IDLE1);

	
	_enemy2[0]->init(3457, 509);
	_enemy2[1]->init(5753, 502);
	_enemy2[2]->init(4361, 468);
	_enemy2[3]->init(5142, 268);
	_enemy2[4]->init(8010, 468);

	
	_enemy3[0]->init(1100, 250);
	_enemy3[1]->init(1279, 268);
	_enemy3[2]->init(1893, 225);
	_enemy3[3]->init(3121, 375);
	_enemy3[4]->init(6048, 171);
	_enemy3[5]->init(8402, 143);
	_enemy3[6]->init(6882, 154);
	_enemy3[7]->init(6570, 362);

	
	_boss->init();


}
