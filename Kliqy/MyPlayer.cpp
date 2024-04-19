#include "MyPlayer.h"


MyPlayer::MyPlayer(int x, int y, int base, int height) :
	Shape(x, y),
	m_base(base),
	m_height(height)
{
}

double MyPlayer::radius()
{
	return m_base / 2.0;
}

int MyPlayer::base()
{
	return m_base;
}

int MyPlayer::height()
{
	return m_height;
}

void MyPlayer::draw(Gdiplus::Graphics& graphics)
{
	double x = m_x;
	double y = m_y;

	int m_Radius = (int)radius();
	graphics.DrawLine(m_pen, m_Radius, 0, -m_Radius, m_Radius);
	graphics.DrawLine(m_pen, -m_Radius, m_Radius, -m_Radius / 2, 0);
	graphics.DrawLine(m_pen, -m_Radius / 2, 0, -m_Radius, -m_Radius);
	graphics.DrawLine(m_pen, -m_Radius, -m_Radius, m_Radius, 0);


	//graphics.DrawLine(m_pen, x, y - m_height / 2, x + m_base / 2, y + m_height/2);
	//graphics.DrawLine(m_pen, x, y - m_height/2, x - m_base / 2, y + m_height/2);
	//graphics.DrawLine(m_pen, x - m_base / 2, y + m_height/2, x + m_base / 2, y + m_height/2);
}
