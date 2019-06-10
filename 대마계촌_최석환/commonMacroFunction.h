#pragma once
//=============================================================
//	## commomMacroFunction ##
//=============================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT 중심좌표에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//렉탱글함수 이용해서 사각 그리기
inline void RectagleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//일립스함수 이용해서 타원 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//일립스함수 이용해서 센터점에 타원 그리기
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//귀찮아서 Rectangle()함수 오버로딩으로 만들어둠
inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
inline void Ellipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//프레임렉트 함수 오버로딩(비어있는 렉트 만들기)
inline void FrameRect(HDC hdc, RECT rc, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FrameRect(hdc, &rc, brush);
	DeleteObject(brush);
}

inline RECT RectMakeBottom(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = x - width / 2;
	rc.right = x + width / 2;
	rc.top = y - height;
	rc.bottom = y;
	return rc;
}