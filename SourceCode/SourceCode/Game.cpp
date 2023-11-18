import game;
using skribbl::IGame;
using skribbl::Game;
using skribbl::Player;
using skribbl::Turn;

Game::Game() : m_turn(nullptr), m_state(Game::State::LOADING)
{
}

Game::~Game()
{
	for (uint16_t index = 0; index < m_players.size(); index++)
		delete m_players[index];
	delete m_turn;
}

Game::Game(const Game& otherGame)
{
	for (uint16_t index = 0; index < m_players.size(); index++)
		delete m_players[index];
	m_players.clear();
	delete m_turn;

	m_players = otherGame.m_players;
	m_turn = otherGame.m_turn;
	m_state = otherGame.m_state;
}

std::shared_ptr<IGame> IGame::Factory()
{
	return std::make_shared<Game>();
}

Game& Game::operator=(const Game& otherGame)
{
	if (this != &otherGame) {
		for (uint16_t index = 0; index < m_players.size(); index++)
			delete m_players[index];
		m_players.clear();
		delete m_turn;

		m_players = otherGame.m_players;
		m_turn = otherGame.m_turn;
		m_state = otherGame.m_state;
	}
	return *this;
}

Game::Game(Game&& otherGame) noexcept
{
	for (uint16_t index = 0; index < m_players.size(); index++)
		delete m_players[index];
	m_players.clear();
	delete m_turn;

	m_players = otherGame.m_players;
	otherGame.m_players.clear();
	m_turn = otherGame.m_turn;
	otherGame.m_turn = nullptr;
	m_state = otherGame.m_state;
	otherGame.m_state = Game::State::GAME_OVER;
}

Game& Game::operator=(Game&& otherGame) noexcept
{
	if (this == &otherGame)
	{
		for (uint16_t index = 0; index < m_players.size(); index++)
			delete m_players[index];
		m_players.clear();
		delete m_turn;

		m_players = otherGame.m_players;
		otherGame.m_players.clear();
		m_turn = otherGame.m_turn;
		otherGame.m_turn = nullptr;
		m_state = otherGame.m_state;
		otherGame.m_state = Game::State::GAME_OVER;
	}
	return *this;
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
	Turn* turn = new Turn; //new Turn(&m_players) we'll se in the future how to do this


	m_state = Game::State::FIRST_ROUND;
	
	while (m_state != Game::State::GAME_OVER)
	{

		for (Player* player : m_players)
		{
			turn->reset(player);
			//sends leaderboard to GUI
		}

		switch (m_state)
		{
		case Game::State::FIRST_ROUND:
		{
			m_state = Game::State::SECOND_ROUND;
			break;
		}
		case Game::State::SECOND_ROUND:
		{
			m_state = Game::State::THIRD_ROUND;
			break;
		}
		case Game::State::THIRD_ROUND:
		{
			m_state = Game::State::FOURTH_ROUND;
			break;
		}
		case Game::State::FOURTH_ROUND:
		{
			m_state = Game::State::GAME_OVER;
			break;
		}
		}

		if (m_players.size() == 0)
			m_state = Game::State::GAME_OVER;
	}
	delete turn;
}

void Game::addPlayer(const std::string& name)
{
	Player* player = new Player(name);
	m_players.push_back(player);
}

bool Game::verifyGuess(const std::string& guess)
{
	return m_turn->verifyGuess(guess);
}

