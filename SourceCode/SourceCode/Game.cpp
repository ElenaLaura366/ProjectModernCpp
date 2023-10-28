#include "Game.h"

Game::Game()
{
}

std::vector<Player*> Game::leaderboard()
{ 
	std::vector<Player* > leaderboard = m_players;
	std::sort(leaderboard.begin(), leaderboard.end(), CompareByScore()); 
	return leaderboard;
}
