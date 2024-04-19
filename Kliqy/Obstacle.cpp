#include "Obstacle.h"
#include "Player.h"
#include "Image.h"

Obstacle::Obstacle(double x, double y, float rad, HWND hWnd) :
	m_radius(rad),
	m_x(x),
	m_y(y),
	m_direction(abs(m_x) == m_x ? 1 : -1),
	m_Angle(90.0),
	m_AliveTime(0),
	m_scale(2.0)
{
	m_object = new MyTriangle(0, 0, m_radius * 2.0f, m_radius * sqrtf(3));
}


void Obstacle::update(double speed)
{
	move(-speed*m_direction, 0);
	this->m_AliveTime++;
}
void Obstacle::draw(Graphics& graphics)
{
	graphics.RotateTransform((REAL)(m_Angle * -m_direction), Gdiplus::MatrixOrderAppend);
	graphics.ScaleTransform((REAL)m_scale, (REAL)m_scale, MatrixOrderAppend);
	if ((this->m_x > 50 && m_direction < 0) || (this->m_x < (IMAGE_WIDTH - 50) && m_direction > 0))
	{
		// Is within range
		if (m_scale >= 1.0)
			m_scale -= 0.05;
	}
	graphics.TranslateTransform((float)m_x, (float)m_y, Gdiplus::MatrixOrderAppend);
	m_object->draw(graphics);
	graphics.ResetTransform();
}


void Obstacle::move(double x, double y)
{
	m_x += x;
	m_y += y;
}

void Obstacle::setPos(double x, double y)
{
	m_x = x;
	m_y = y;
}

std::vector<double> Obstacle::getPos()
{
	return { m_x, m_y };
}

float Obstacle::getRadius()
{
	return m_radius;
}
