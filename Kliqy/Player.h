#pragma once
#include "MyPlayer.h"
#include "Game.h"

class Player
{
	MyPlayer* m_object;
	double m_x;
	double m_y;
	int m_width, m_height;
	double m_JumpSpeed;
	float m_Angle;
	double m_Radius;
public:
	Player(HWND hWnd, int width, int height);
	double getRadius();
	double getJumpSpeed();
	~Player();
	void draw(Gdiplus::Graphics& graphics);
	void setPos(double x, double y);
	double move(double x, double y);
	void update();
	void handleInput(Game* currGame);

	std::vector<double> getPosition();

};

