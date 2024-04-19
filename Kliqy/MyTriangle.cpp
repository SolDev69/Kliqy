#include "MyTriangle.h"

void MyTriangle::draw(Gdiplus::Graphics& graphics)
{
	double x = m_x;
	double y = m_y;

	//int m_Radius = m_base / 2;
	//graphics.DrawLine(m_pen, m_Radius, 0, -m_Radius, m_Radius);
	//graphics.DrawLine(m_pen, -m_Radius, m_Radius, -m_Radius / 2, 0);
	//graphics.DrawLine(m_pen, -m_Radius / 2, 0, -m_Radius, -m_Radius);
	//graphics.DrawLine(m_pen, -m_Radius, -m_Radius, m_Radius, 0);


	graphics.DrawLine(m_pen, (int)x, (int)(y - m_height / 2), (int)(x + m_base / 2), (int)(y + m_height/2));
	graphics.DrawLine(m_pen, (int)x, (int)(y - m_height/2), (int)(x - m_base / 2), (int)(y + m_height/2));
	graphics.DrawLine(m_pen, (int)(x - m_base / 2), (int)(y + m_height/2), (int)(x + m_base / 2), (int)(y + m_height/2));
}

MyTriangle::MyTriangle(double x, double y, double base, double height) :
	Shape(x, y),
	m_base(base),
	m_height(height)
{
}

double MyTriangle::base()
{
	return m_base;
}

double MyTriangle::height()
{
	return m_height;
}
