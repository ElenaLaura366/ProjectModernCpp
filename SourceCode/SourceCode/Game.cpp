import game;

Game::Game() : m_isRunning(false)
{
}

class CompareByScore
{
public:
	bool operator() (const Player* const firstPlayer, const Player* const secondPlayer) const
	{
		return firstPlayer->getScore() > secondPlayer->getScore();
	}
};

std::vector<Player*> Game::leaderboard()
{ 
	std::vector<Player* > leaderboard = m_players;
	std::sort(leaderboard.begin(), leaderboard.end(), CompareByScore()); 
	return leaderboard;
}

void Game::start()
{
	m_isRunning = true;
	//this will implement all the processes that happen within a game
	m_turn = new Turn();
	//smth like that, tho we don't know yet how to add more players and delete them when they enter the game
	//ofc, it is related to networking so we have to wait
	Player* newPlayer = new Player();
	m_players.push_back(newPlayer);
	//somehow we should add the players to the vector when they enter the game and remove them when they leave
	for (Player* currentDrawer : m_players)
		m_turn->reset(currentDrawer);
	// m_isRunning will become false after all 4 rounds end
}

bool Game::isRunning() const
{
	return m_isRunning;
}
