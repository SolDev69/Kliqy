#pragma once
#include "Shape.h"
#include "Obstacle.h"
#include <vector>
#include <string>
#include <windows.h>
#include <gdiplus.h>
#pragma warning (disable:28251)

// GDI+ libraries 
#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;

class Player;

class Game
{
private:
	Player* m_player;
	std::vector<Obstacle*> m_Obstacles;
	bool m_isRunning;
	int m_frequency;
	int m_startingFreq;
	std::wstring m_string;
	int m_localTime;
	bool m_gameStarted;
	bool m_gameCompleted;
	PointF* m_StringSpawn;
public:
	Game(HWND& hWnd);
	bool isGameRunning();
	void startGame();
	~Game();
	Player* getPlayer();
	void update(unsigned long elapsed);
	void setGameStarted(bool set);
	void render(Gdiplus::Graphics& g, int gc);
	std::vector<Obstacle*>& getObstacles();
	void resetLocalTime();
	void setFrequency(int a);
};