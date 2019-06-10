#include "stdafx.h"
#include "UI.h"

HRESULT UI::init(void)
{
	_check = false;
	for (int i = 0; i < 5; i++) {
		_score[i] = RectMakeCenter(32 * (i + 1) + 64, 32, 32, 32);
	}

	for (int i = 0; i < 5; i++) {
		_num[i] = RectMakeCenter(32 * (i+1) + 64, 84, 32, 32);
	}

	for (int i = 0; i < 4; i++) {
		_time[i] = RectMakeCenter(32 * (i+1) + 416, 32, 32, 32);
	}

	for (int i = 0; i < 5; i++) {
		_timenum[i] = RectMakeCenter(32 * (i+1) + 400, 70, 32, 32);
	}

	for (int i = 0; i < 2; i++) {
		_life[i] = RectMakeCenter(32 * (i+1) + 864, 64, 32, 32);
	}

	_lifeshape = RectMakeCenter(832, 55, 60, 60);
	_timeshape = RectMakeCenter(WINSIZEX / 2 - 5, 64, 184, 80);
	_weapshape = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 45, 64, 60);

	IMAGEMANAGER->addImage("0", "FONT/0.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1", "FONT/1.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "FONT/2.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3", "FONT/3.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4", "FONT/4.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5", "FONT/5.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("6", "FONT/6.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("7", "FONT/7.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "FONT/8.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("9", "FONT/9.bmp", 32, 32, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("S", "FONT/S.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("C", "FONT/C.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("O", "FONT/O.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("R", "FONT/R.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("E", "FONT/E.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("T", "FONT/T.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("I", "FONT/I.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("M", "FONT/M.bmp", 32, 32, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("X", "FONT/X.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("점", "FONT/점.bmp", 32, 32, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("대거", "FONT/대거유아이.bmp", 64, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("창", "FONT/창유아이.bmp", 64, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("시간", "FONT/시간유아이.bmp", 184, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("목숨", "FONT/캐릭터목숨.bmp", 60, 60, true, RGB(255, 0, 255));
	return S_OK;
}

void UI::release(void)
{
}

void UI::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		if (_check == false) {
			_check = true;
		}
		else {
			_check = false;
		}
	}
}

void UI::render(void)
{
	IMAGEMANAGER->render("S", getMemDC(), _score[0].left, _score[0].top);
	IMAGEMANAGER->render("C", getMemDC(), _score[1].left, _score[1].top);
	IMAGEMANAGER->render("O", getMemDC(), _score[2].left, _score[2].top);
	IMAGEMANAGER->render("R", getMemDC(), _score[3].left, _score[3].top);
	IMAGEMANAGER->render("E", getMemDC(), _score[4].left, _score[4].top);

	this->SetLife(UIMANAGER->GetLife());
	this->SetTime(UIMANAGER->GetTime());
	this->SetScore(UIMANAGER->GetScore());
	this->SetWeap(UIMANAGER->GetWeap());

	IMAGEMANAGER->render("T", getMemDC(), _time[0].left, _time[0].top);
	IMAGEMANAGER->render("I", getMemDC(), _time[1].left, _time[1].top);
	IMAGEMANAGER->render("M", getMemDC(), _time[2].left, _time[2].top);
	IMAGEMANAGER->render("E", getMemDC(), _time[3].left, _time[3].top);

	IMAGEMANAGER->render("점", getMemDC(), _timenum[2].left, _timenum[2].top);
	IMAGEMANAGER->render("X", getMemDC(), _life[0].left, _life[0].top);

	IMAGEMANAGER->render("목숨", getMemDC(), _lifeshape.left, _lifeshape.top);
	IMAGEMANAGER->render("시간", getMemDC(), _timeshape.left, _timeshape.top);
	
	if (_check == true) {
		for (int i = 0; i < 5; i++) {
			Rectangle(getMemDC(), _num[i]);
		}

		for (int i = 0; i < 5; i++) {
			Rectangle(getMemDC(), _num[i]);
		}

		for (int i = 0; i < 4; i++) {
			Rectangle(getMemDC(), _time[i]);
		}

		for (int i = 0; i < 5; i++) {
			Rectangle(getMemDC(), _timenum[i]);
		}

		for (int i = 0; i < 2; i++) {
			Rectangle(getMemDC(), _life[i]);
		}

		FrameRect(getMemDC(), _lifeshape, RGB(255, 0, 0));
		FrameRect(getMemDC(), _timeshape, RGB(255, 0, 0));
		Rectangle(getMemDC(), _weapshape);
	}
}

void UI::SetLife(int life)
{
	string str = to_string(life);
	//if (str.length() == 1) {
		switch (str[0])
		{
		case '0':
			IMAGEMANAGER->render("0", getMemDC(), _life[1].left, _life[1].top);
			break;
		case '1':
			IMAGEMANAGER->render("1", getMemDC(), _life[1].left, _life[1].top);
			break;
		case '2':
			IMAGEMANAGER->render("2", getMemDC(), _life[1].left, _life[1].top);
			break;
		case '3':
			IMAGEMANAGER->render("3", getMemDC(), _life[1].left, _life[1].top);
			break;
		case '4':
			IMAGEMANAGER->render("4", getMemDC(), _life[1].left, _life[1].top);
			break;
		case '5':
			IMAGEMANAGER->render("5", getMemDC(), _life[1].left, _life[1].top);
			break;
		case '6':
			IMAGEMANAGER->render("6", getMemDC(), _life[1].left, _life[1].top);
			break;
		case '7':
			IMAGEMANAGER->render("7", getMemDC(), _life[1].left, _life[1].top);
			break;
		case '8':
			IMAGEMANAGER->render("8", getMemDC(), _life[1].left, _life[1].top);
			break;
		case '9':
			IMAGEMANAGER->render("9", getMemDC(), _life[1].left, _life[1].top);
			break;
		}
	//}
}
// 시간 계산해서 화면에 보여주는 함수
void UI::SetTime(int time)
{
	int min_sec[2] = { time / 60 , time % 60 };
	string str = to_string(min_sec[0]);
	if (str.length() == 1) {
		IMAGEMANAGER->render("0", getMemDC(), _timenum[0].left, _timenum[0].top);
		switch (str[0])
		{
		case '0':
			IMAGEMANAGER->render("0", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		case '1':
			IMAGEMANAGER->render("1", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		case '2':
			IMAGEMANAGER->render("2", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		case '3':
			IMAGEMANAGER->render("3", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		case '4':
			IMAGEMANAGER->render("4", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		case '5':
			IMAGEMANAGER->render("5", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		case '6':
			IMAGEMANAGER->render("6", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		case '7':
			IMAGEMANAGER->render("7", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		case '8':
			IMAGEMANAGER->render("8", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		case '9':
			IMAGEMANAGER->render("9", getMemDC(), _timenum[1].left, _timenum[1].top);
			break;
		}
	}
	else {
		for (int j = 0; j < 2; j++) {
			switch (str[j])
			{
			case '0':
				IMAGEMANAGER->render("0", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			case '1':
				IMAGEMANAGER->render("1", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			case '2':
				IMAGEMANAGER->render("2", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			case '3':
				IMAGEMANAGER->render("3", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			case '4':
				IMAGEMANAGER->render("4", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			case '5':
				IMAGEMANAGER->render("5", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			case '6':
				IMAGEMANAGER->render("6", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			case '7':
				IMAGEMANAGER->render("7", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			case '8':
				IMAGEMANAGER->render("8", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			case '9':
				IMAGEMANAGER->render("9", getMemDC(), _timenum[j].left, _timenum[j].top);
				break;
			}
		}
	}
	string str2 = to_string(min_sec[1]);
	if (str2.length() == 1) {
		IMAGEMANAGER->render("0", getMemDC(), _timenum[3].left, _timenum[3].top);
		switch (str2[0])
		{
		case '0':
			IMAGEMANAGER->render("0", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		case '1':
			IMAGEMANAGER->render("1", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		case '2':
			IMAGEMANAGER->render("2", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		case '3':
			IMAGEMANAGER->render("3", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		case '4':
			IMAGEMANAGER->render("4", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		case '5':
			IMAGEMANAGER->render("5", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		case '6':
			IMAGEMANAGER->render("6", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		case '7':
			IMAGEMANAGER->render("7", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		case '8':
			IMAGEMANAGER->render("8", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		case '9':
			IMAGEMANAGER->render("9", getMemDC(), _timenum[4].left, _timenum[4].top);
			break;
		}
	}
	else {
		for (int j = 0; j < 2; j++)
		{
			switch (str2[j])
			{
			case '0':
				IMAGEMANAGER->render("0", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			case '1':
				IMAGEMANAGER->render("1", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			case '2':
				IMAGEMANAGER->render("2", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			case '3':
				IMAGEMANAGER->render("3", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			case '4':
				IMAGEMANAGER->render("4", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			case '5':
				IMAGEMANAGER->render("5", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			case '6':
				IMAGEMANAGER->render("6", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			case '7':
				IMAGEMANAGER->render("7", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			case '8':
				IMAGEMANAGER->render("8", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			case '9':
				IMAGEMANAGER->render("9", getMemDC(), _timenum[j+3].left, _timenum[j+3].top);
				break;
			}
		}
	}
}
// 점수 계산해서 화면에 보여주는 함수
void UI::SetScore(int score)
{
	string str = to_string(score);
	for (int i = str.length()-1; i >= 0; i--) {
		switch (str[i])
		{
		case '0':
			IMAGEMANAGER->render("0", getMemDC(), _num[i].left, _num[i].top);
			break;
		case '1':
			IMAGEMANAGER->render("1", getMemDC(), _num[i].left, _num[i].top);
			break;
		case '2':
			IMAGEMANAGER->render("2", getMemDC(), _num[i].left, _num[i].top);
			break;
		case '3':
			IMAGEMANAGER->render("3", getMemDC(), _num[i].left, _num[i].top);
			break;
		case '4':
			IMAGEMANAGER->render("4", getMemDC(), _num[i].left, _num[i].top);
			break;
		case '5':
			IMAGEMANAGER->render("5", getMemDC(), _num[i].left, _num[i].top);
			break;
		case '6':
			IMAGEMANAGER->render("6", getMemDC(), _num[i].left, _num[i].top);
			break;
		case '7':
			IMAGEMANAGER->render("7", getMemDC(), _num[i].left, _num[i].top);
			break;
		case '8':
			IMAGEMANAGER->render("8", getMemDC(), _num[i].left, _num[i].top);
			break;
		case '9':
			IMAGEMANAGER->render("9", getMemDC(), _num[i].left, _num[i].top);
			break;
		}
	}

}

// 무기의 종류를 확인하고 화면에 보여주는 함수
void UI::SetWeap(WEAP weap)
{
	switch (_weap = weap)
	{
	case WEAP::SPEAR:
		IMAGEMANAGER->render("창", getMemDC(), _weapshape.left, _weapshape.top);
		break;
	case WEAP::DAGUE:
		IMAGEMANAGER->render("대거", getMemDC(), _weapshape.left, _weapshape.top);
		break;
	}
}
