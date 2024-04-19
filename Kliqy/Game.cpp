#include "Game.h"
#include "Player.h"
#include "Image.h"
#include "Constants.h"

HWND* g_hWnd = new HWND;

Game::Game(HWND& hWnd) :
	m_isRunning(false),
	m_frequency(1000),
	m_startingFreq(m_frequency),
	m_gameStarted(false),
	m_gameCompleted(false),
	m_localTime(0)
{
	std::string baseString = c_GameName + "\nPress space / enter to start";
	m_string.assign(baseString.begin(), baseString.end());
	*g_hWnd = hWnd;
	m_player = new Player(*g_hWnd, 20, 20);
	m_player->setPos(IMAGE_WIDTH/2.0, IMAGE_HEIGHT/2.0);
	m_StringSpawn = new PointF(IMAGE_WIDTH / 4, 50);
}

bool Game::isGameRunning()
{
	return m_isRunning;
}

void Game::startGame()
{
	m_isRunning = true;
	m_player->setPos(IMAGE_WIDTH / 2.0, IMAGE_HEIGHT / 2.0);
}

Game::~Game()
{
	delete m_player;
	delete m_StringSpawn;
	for (Obstacle* o : m_Obstacles)
		delete o;
}

void Game::render(Gdiplus::Graphics& g, int gc)
{
	Font font(L"Arial", 16);
	SolidBrush brush(Color(255, 255, 255, 255));
	g.DrawString(m_string.c_str(), -1, &font, *m_StringSpawn, &brush);
	m_player->draw(g);
	for (Obstacle* o : m_Obstacles)
		o->draw(g);
}
std::vector<Obstacle*>& Game::getObstacles()
{
	return m_Obstacles;
}
void Game::resetLocalTime()
{
	m_localTime = 0;
}
void Game::update(unsigned long elapsed)
{
	m_frequency -= (int)elapsed;
	m_player->handleInput(this);
	if (m_isRunning)
	{
		m_StringSpawn->X = IMAGE_WIDTH / 2.0;
		m_localTime += elapsed;
		std::string newString = std::to_string(m_localTime / 1000);
		m_string.assign(newString.begin(), newString.end());

		if (m_frequency < 0)
		{
			int random = rand() % 2;
			const int c_debugLimit = 0;
			if (c_debugLimit == 0 ? true : (c_debugLimit > m_Obstacles.size()))
				m_Obstacles.push_back(new Obstacle((random == 0) ? IMAGE_WIDTH + 10 : - 10, rand() % IMAGE_HEIGHT, 10.0f, *g_hWnd));
			m_frequency = --m_startingFreq;
		}

		if (m_startingFreq == 10)
		{
			m_isRunning = false;
			m_gameCompleted = true;
		}
		m_player->update();
		for (Obstacle* o : m_Obstacles)
		{
			float distance = sqrtf(powf((float)o->getPos()[0] - (float)m_player->getPosition()[0], 2) + powf((float)o->getPos()[1] - (float)m_player->getPosition()[1], 2));
			if (distance <= o->getRadius() + m_player->getRadius())
			{
				// Collision
				m_isRunning = false;
			}
			o->update(5.0);
		}
	}
	else
	{
		if (m_gameStarted)
		{
			m_StringSpawn->X = IMAGE_WIDTH / 4;
			std::string endString = "ERROR: Endgame text not reached!";
			if (m_gameCompleted)
			{
				endString = "You won!\nScore: " + std::to_string(m_localTime) + "\nPress enter or space to restart!";
			}
			else
			{
				endString = "Game over!\nScore: " + std::to_string(m_localTime) + "\nPress enter or space to restart!";
			}
			m_string.assign(endString.begin(), endString.end());
		}
	}
}

void Game::setGameStarted(bool set)
{
	m_gameStarted = set;
}

Player* Game::getPlayer()
{
	return m_player;
}