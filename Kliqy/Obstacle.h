#pragma once

#pragma once
#include "Shape.h"
#include "MyTriangle.h"
#include <vector>

class Obstacle
{
private:
	double m_x;
	double m_y;
	float m_radius;
	int m_direction; // 1 = right-left, -1 = left-right
	MyTriangle* m_object;
	double m_Angle;
	unsigned int m_AliveTime;
	double m_scale;
	int m_vert;
public:
	Obstacle(double x, double y, float rad, HWND hWnd, int direction = 0);
	void update(double speed);
	void draw(Gdiplus::Graphics& graphics);
	void move(double x, double y);
	void setPos(double x, double y);
	std::vector<double> getPos();
	float getRadius();
};