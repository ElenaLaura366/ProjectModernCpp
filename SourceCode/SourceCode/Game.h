#pragma once
#include "Turn.h"
#include <vector>

class Game
{
public:
	Game();

private:
	std::vector<Player* > m_players;
	Turn* m_turn;
};

