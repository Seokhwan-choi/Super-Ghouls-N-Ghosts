#include "stdafx.h"
#include "TItle.h"


HRESULT TItle::init(void)
{
	_count = 0;
	_check = true;
	_alphabet = new image[26];
	for (int i = 0; i < 26; i++) 
	{
		char str[256];
		wsprintf(str, "alphabet/%d.bmp", i + 1);
		_alphabet[i].init(str, 32, 32, true, RGB(255, 0, 255));
	}
	IMAGEMANAGER->addImage("타이틀", "images/타이틀.bmp", 1000, 672);
	IMAGEMANAGER->addImage("점점", "alphabet/점점.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("검정", "alphabet/검정.bmp", 32, 32);

	for (int i = 0; i < 5; i++) {
		_press[i] = RectMakeCenter(32 * (i+1) + 150 +35, WINSIZEY / 2 + 100, 32, 32);
		_start[i] = RectMakeCenter(32 * (i + 1) + 600 + 35, WINSIZEY / 2 + 100, 32, 32);
		_folio[i] = RectMakeCenter(32 * (i + 1) + 620, WINSIZEY / 2 + 240, 32, 32);
	}

	for (int i = 0; i < 4; i++) {
		_choi[i] = RectMakeCenter(32 * (i + 1) + 150 + 125, WINSIZEY / 2 + 70 + 100, 32, 32);
		_seok[i] = RectMakeCenter(32 * (i + 1) + 300 + 125, WINSIZEY / 2 + 70 + 100, 32, 32);
		_hwan[i] = RectMakeCenter(32 * (i + 1) + 450 + 125, WINSIZEY / 2 + 70 + 100, 32, 32);
		_week[i] = RectMakeCenter(32 * (i + 1) + 320, WINSIZEY / 2 + 240, 32, 32);
		_port[i] = RectMakeCenter(32 * (i + 1) + 470, WINSIZEY / 2 + 240, 32, 32);
	}

	for (int i = 0; i < 7; i++) {
		_enter[i] = RectMakeCenter(32 * (i + 1) + 350 + 35, WINSIZEY / 2 + 100, 32, 32);
	}

	for (int i = 0; i < 3; i++) {
		_one[i] = RectMakeCenter(32 * (i + 1) + 200, WINSIZEY / 2 + 240, 32, 32);
	}

	_title = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 1000, 672);
	
	return S_OK;
}

void TItle::release(void)
{
}

void TItle::update(void)
{
	_count++;
	if ((_count % 25) == 0) {
		if (_check == true) {
			_check = false;
		}
		else {
			_check = true;
		}
	}
}

void TItle::render(void)
{
	IMAGEMANAGER->render("타이틀", getMemDC(), _title.left, _title.top);
	if ( _check ) 
	{
		//cout << "Show Title" << endl;
		_alphabet[15].render(getMemDC(), _press[0].left, _press[0].top);
		_alphabet[17].render(getMemDC(), _press[1].left, _press[1].top);
		_alphabet[4].render(getMemDC(), _press[2].left, _press[2].top);
		_alphabet[18].render(getMemDC(), _press[3].left, _press[3].top);
		_alphabet[18].render(getMemDC(), _press[4].left, _press[4].top);

		IMAGEMANAGER->render("점점", getMemDC(), _enter[0].left, _enter[0].top);
		_alphabet[4].render(getMemDC(), _enter[1].left, _enter[1].top);
		_alphabet[13].render(getMemDC(), _enter[2].left, _enter[2].top);
		_alphabet[19].render(getMemDC(), _enter[3].left, _enter[3].top);
		_alphabet[4].render(getMemDC(), _enter[4].left, _enter[4].top);
		_alphabet[17].render(getMemDC(), _enter[5].left, _enter[5].top);
		IMAGEMANAGER->render("점점", getMemDC(), _enter[6].left, _enter[6].top);

		_alphabet[18].render(getMemDC(), _start[0].left, _start[0].top);
		_alphabet[19].render(getMemDC(), _start[1].left, _start[1].top);
		_alphabet[0].render(getMemDC(), _start[2].left, _start[2].top);
		_alphabet[17].render(getMemDC(), _start[3].left, _start[3].top);
		_alphabet[19].render(getMemDC(), _start[4].left, _start[4].top);
	}
	else {
		//cout << "Hide Title" << endl;
		IMAGEMANAGER->render("검정", getMemDC(), _press[0].left, _press[0].top);
		IMAGEMANAGER->render("검정", getMemDC(), _press[1].left, _press[1].top);
		IMAGEMANAGER->render("검정", getMemDC(), _press[2].left, _press[2].top);
		IMAGEMANAGER->render("검정", getMemDC(), _press[3].left, _press[3].top);
		IMAGEMANAGER->render("검정", getMemDC(), _press[4].left, _press[4].top);

		IMAGEMANAGER->render("검정", getMemDC(), _enter[0].left, _enter[0].top);
		IMAGEMANAGER->render("검정", getMemDC(), _enter[1].left, _enter[1].top);
		IMAGEMANAGER->render("검정", getMemDC(), _enter[2].left, _enter[2].top);
		IMAGEMANAGER->render("검정", getMemDC(), _enter[3].left, _enter[3].top);
		IMAGEMANAGER->render("검정", getMemDC(), _enter[4].left, _enter[4].top);
		IMAGEMANAGER->render("검정", getMemDC(), _enter[5].left, _enter[5].top);
		IMAGEMANAGER->render("검정", getMemDC(), _enter[6].left, _enter[6].top);

		IMAGEMANAGER->render("검정", getMemDC(), _start[0].left, _start[0].top);
		IMAGEMANAGER->render("검정", getMemDC(), _start[1].left, _start[1].top);
		IMAGEMANAGER->render("검정", getMemDC(), _start[2].left, _start[2].top);
		IMAGEMANAGER->render("검정", getMemDC(), _start[3].left, _start[3].top);
		IMAGEMANAGER->render("검정", getMemDC(), _start[4].left, _start[4].top);
	}

	_alphabet[2].render(getMemDC(), _choi[0].left, _choi[0].top);
	_alphabet[7].render(getMemDC(), _choi[1].left, _choi[1].top);
	_alphabet[14].render(getMemDC(), _choi[2].left, _choi[2].top);
	_alphabet[8].render(getMemDC(), _choi[3].left, _choi[3].top);

	_alphabet[18].render(getMemDC(), _seok[0].left, _seok[0].top);
	_alphabet[4].render(getMemDC(), _seok[1].left, _seok[1].top);
	_alphabet[14].render(getMemDC(), _seok[2].left, _seok[2].top);
	_alphabet[10].render(getMemDC(), _seok[3].left, _seok[3].top);

	_alphabet[7].render(getMemDC(), _hwan[0].left, _hwan[0].top);
	_alphabet[22].render(getMemDC(), _hwan[1].left, _hwan[1].top);
	_alphabet[0].render(getMemDC(), _hwan[2].left, _hwan[2].top);
	_alphabet[13].render(getMemDC(), _hwan[3].left, _hwan[3].top);

	_alphabet[14].render(getMemDC(), _one[0].left, _one[0].top);
	_alphabet[13].render(getMemDC(), _one[1].left, _one[1].top);
	_alphabet[4].render(getMemDC(), _one[2].left, _one[2].top);

	_alphabet[22].render(getMemDC(), _week[0].left, _week[0].top);
	_alphabet[4].render(getMemDC(), _week[1].left, _week[1].top);
	_alphabet[4].render(getMemDC(), _week[2].left, _week[2].top);
	_alphabet[10].render(getMemDC(), _week[3].left, _week[3].top);

	_alphabet[15].render(getMemDC(), _port[0].left, _port[0].top);
	_alphabet[14].render(getMemDC(), _port[1].left, _port[1].top);
	_alphabet[17].render(getMemDC(), _port[2].left, _port[2].top);
	_alphabet[19].render(getMemDC(), _port[3].left, _port[3].top);

	_alphabet[5].render(getMemDC(), _folio[0].left, _folio[0].top);
	_alphabet[14].render(getMemDC(), _folio[1].left, _folio[1].top);
	_alphabet[11].render(getMemDC(), _folio[2].left, _folio[2].top);
	_alphabet[8].render(getMemDC(), _folio[3].left, _folio[3].top);
	_alphabet[14].render(getMemDC(), _folio[4].left, _folio[4].top);


	//for (int i = 0; i < 5; i++) {
	//	if (_check) {
	//		Rectangle(getMemDC(), _press[i]);
	//		Rectangle(getMemDC(), _start[i]);
	//	}
	//	Rectangle(getMemDC(), _folio[i]);
	//}
	//
	//for (int i = 0; i < 4; i++) {
	//	Rectangle(getMemDC(), _choi[i]);
	//	Rectangle(getMemDC(), _seok[i]);
	//	Rectangle(getMemDC(), _hwan[i]);
	//	Rectangle(getMemDC(), _week[i]);
	//	Rectangle(getMemDC(), _port[i]);
	//}
	//
	//for (int i = 0; i < 7; i++) {
	//	if (_check) {
	//		Rectangle(getMemDC(), _enter[i]);
	//	}
	//}
	//for (int i = 0; i < 3; i++) {
	//	Rectangle(getMemDC(), _one[i]);
	//}
}
