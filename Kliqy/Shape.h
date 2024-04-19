#pragma once
#include <windows.h>
#include <gdiplus.h>
class Shape
{
protected:
	double m_x; // center of shape
	double m_y;

	//Windows specific
	COLORREF m_colour;
	float m_thick;
	Gdiplus::Pen* m_pen = nullptr;
	Gdiplus::Brush* m_brush = nullptr;
public:
	virtual void draw(Gdiplus::Graphics& graphics) = 0;	// Everybody has their own draw()
	Shape(double x, double y);
	~Shape();
};

