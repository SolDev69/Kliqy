#include "Shape.h"
#include <Windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

Shape::Shape(double x, double y) : m_thick(3.0), m_x(x), m_y(y)
{
	m_colour = RGB(255, 255, 255);
	m_pen = new Pen(Color(GetRValue(m_colour), GetGValue(m_colour), GetBValue(m_colour)), m_thick);
	m_brush = new SolidBrush(Color(GetRValue(m_colour), GetGValue(m_colour), GetBValue(m_colour)));
}


Shape::~Shape()
{
	if (m_pen)
		delete m_pen;
	m_pen = nullptr;
	if (m_brush)
		delete m_brush;
	m_brush = nullptr;
}

