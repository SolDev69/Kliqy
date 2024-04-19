#include "Player.h"
#include "Image.h"

double g_JumpHeight;

Player::Player(HWND hWnd, int width, int height) :
	m_x(0.0),
	m_y(0.0),
	m_JumpSpeed(5.0),
	m_Angle(0.0),
	m_width(width),
	m_height(height)
{
	g_JumpHeight = m_JumpSpeed;
	m_object = new MyPlayer(0, 0, width, height);
	m_Radius = sqrt(pow(m_object->base()/2, 2) + pow(m_object->height()/2, 2)) / 2.0;
}

double Player::getRadius()
{
	return m_Radius;
}

double Player::getJumpSpeed()
{
	return m_JumpSpeed;
}

Player::~Player()
{
	delete m_object;
}

void Player::draw(Gdiplus::Graphics& graphics)
{
	graphics.RotateTransform(m_Angle - 90, Gdiplus::MatrixOrderAppend);
	graphics.TranslateTransform((float)m_x, (float)m_y, Gdiplus::MatrixOrderAppend);
	m_object->draw(graphics);
	graphics.ResetTransform();
}

void Player::setPos(double x, double y)
{
	m_x = x;
	m_y = y;
}

double Player::move(double x, double y)
{
	double m_dx = m_x;
	double m_dy = m_y;
	m_x += x;
	m_y += y;
	return sqrt(pow(m_dx - m_x, 2) + pow(m_dy - m_y, 2));
}

void Player::update()
{
	if (m_Angle >= 360.0f)
		m_Angle = 0.0f;
}

int getElapsedTime();

void Player::handleInput(Game* currGame)
{
	if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_RETURN /* Enter key */))
	{
		currGame->startGame();
		currGame->setGameStarted(true);
		currGame->getObstacles().clear();
		currGame->resetLocalTime();
		currGame->setFrequency(1000);
	}

	if (currGame->isGameRunning())
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			if (m_x + m_width / 5 < IMAGE_WIDTH)
				if (m_x + m_Radius + 10 < IMAGE_WIDTH)
					move(m_width / 5, 0);
			m_Angle = 90.0f;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (m_x - m_width / 5 > 0)
				if (m_x-m_Radius-10 > 0)
					move(-m_width / 5, 0);
			m_Angle = 270.0f;
		}

		if (GetAsyncKeyState(VK_UP))
		{
			if (m_y - m_height/5 > 0)
				if (m_y - m_Radius - 10 > 0)
					move(0, -m_height / 5);
			m_Angle = 0.0f;
			int direction = GetAsyncKeyState(VK_RIGHT) ? 1 : GetAsyncKeyState(VK_LEFT) ? -1 : 0;
			m_Angle += 45.0f * direction;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			if (m_y + m_height / 5 < IMAGE_HEIGHT)
				if (m_y + m_Radius + 10 < IMAGE_HEIGHT)
					move(0, m_height / 5);
			m_Angle = 180.0f;
			int direction = GetAsyncKeyState(VK_RIGHT) ? 1 : GetAsyncKeyState(VK_LEFT) ? -1 : 0;
			m_Angle -= 45.0f * direction;
		}

	}
}

std::vector<double> Player::getPosition()
{
	return {m_x, m_y};
}