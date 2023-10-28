#pragma once
#include "Turn.h"
#include <vector>
#include <algorithm>

class Game
{
public:
	Game();
	std::vector<Player* > leaderboard();
	void start();
	bool isRunning();

private:
	std::vector<Player* > m_players;
	Turn* m_turn;
	bool m_isRunning;
};

