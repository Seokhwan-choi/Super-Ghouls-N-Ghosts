#include "stdafx.h"
#include "Camera.h"

void Camera::SetCameraPosition(POINT pos)
{
	//�켱 ī�޶� ������ ����
	this->pos = pos;
	//�����Ǵ�� ī�޶� ��Ʈ�� ����
	this->rc = RectMakeCenter(pos.x, pos.y, WINSIZEX, WINSIZEY);

	//�̰� �ʹ����� �����°� ����ó��

	//������ ���� ���� ī�޶� ��Ʈ�� �����ٸ� ����
	if (rc.left < 0)
	{
		this->pos.x -= rc.left;
	}
	//�� ������ ������ ī�޶� ��Ʈ�� �����ٸ�(������ ���� �� �ʻ���� 2000�̶�� ������)
	else if (rc.right > 8612)
	{
		this->pos.x -= rc.right - 8612;
	}
	//�̰� �Ʒ��� ī�޶� �������� �Ѵٸ� ����ó��(���� �� �ʻ����� ���α��̴� ��������)
	if (rc.bottom > WINSIZEY)
	{
		this->pos.y -= rc.bottom - WINSIZEY;
	}

	if (rc.top < 0) {
		this->pos.y -= rc.top;
	}
	//��ǥ ������ �����ٸ� �ٽ� ī�޶� ��Ʈ�� ��������
	this->rc = RectMakeCenter(this->pos.x, this->pos.y, WINSIZEX, WINSIZEY);
}
