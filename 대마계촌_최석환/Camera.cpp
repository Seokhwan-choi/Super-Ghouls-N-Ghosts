#include "stdafx.h"
#include "Camera.h"

void Camera::SetCameraPosition(POINT pos)
{
	//우선 카메라 포지션 세팅
	this->pos = pos;
	//포지션대로 카메라 렉트도 세팅
	this->rc = RectMakeCenter(pos.x, pos.y, WINSIZEX, WINSIZEY);

	//이건 맵밖으로 나가는거 보정처리

	//맵제일 왼쪽 끝을 카메라 렉트가 나갔다면 보정
	if (rc.left < 0)
	{
		this->pos.x -= rc.left;
	}
	//맵 오른쪽 끝으로 카메라 렉트가 나갔다면(지금은 예를 들어서 맵사이즈가 2000이라고 가정함)
	else if (rc.right > 8612)
	{
		this->pos.x -= rc.right - 8612;
	}
	//이건 아래로 카메라가 나갈려고 한다면 보정처리(예를 들어서 맵사이즈 세로길이는 윈사이즈)
	if (rc.bottom > WINSIZEY)
	{
		this->pos.y -= rc.bottom - WINSIZEY;
	}

	if (rc.top < 0) {
		this->pos.y -= rc.top;
	}
	//좌표 보정이 끝났다면 다시 카메라 렉트도 보정하자
	this->rc = RectMakeCenter(this->pos.x, this->pos.y, WINSIZEX, WINSIZEY);
}
