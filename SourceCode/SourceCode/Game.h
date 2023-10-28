#pragma once
#include "Turn.h"
#include <vector>
#include <algorithm>

class Game
{
public:
	Game();
	std::vector<Player* > leaderboard();


private:
	std::vector<Player* > m_players;
	Turn* m_turn;

	class CompareByScore
	{
	public:
		//I don't know why but it don't work if i use const Player&
		bool operator() (Player& firstPlayer, Player& secondPlayer) const
		{
			return firstPlayer.getScore() > secondPlayer.getScore();
		}
	};
};

