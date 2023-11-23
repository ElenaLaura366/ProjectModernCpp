#include <crow.h>
import game;
using skribbl::IGame;
using skribbl::Game;
using skribbl::Player;
using skribbl::Turn;

Game::Game() : m_state{ Game::State::LOADING }
{
}

IGame::IGamePtr IGame::Factory()
{
	return std::make_shared<Game>();
}

class CompareByScore
{
public:
	bool operator() (const std::shared_ptr<const Player> firstPlayer, std::shared_ptr<const Player> secondPlayer) const
	{
		return firstPlayer->getScore() > secondPlayer->getScore();
	}
};

std::vector < std::shared_ptr<Player>> Game::leaderboard()
{
	std::vector < std::shared_ptr<Player>> leaderboard = m_players;
	std::sort(leaderboard.begin(), leaderboard.end(), CompareByScore());
	return leaderboard;
}

void Game::start()
{
	m_turn = std::make_shared<Turn>();

	m_state = Game::State::FIRST_ROUND;

	while (m_state != Game::State::GAME_OVER)
	{

		for (std::shared_ptr<Player> player : m_players)
		{
			m_turn->reset(player);
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
}

void Game::addPlayer(const std::string& name)
{
	std::shared_ptr<Player> player = std::make_shared<Player>(name);

	m_players.push_back(player);
}

bool Game::verifyGuess(const std::string& guess)
{
	return m_turn->verifyGuess(guess);
}

