#include "Game.h"

using skribbl::IGame;
using skribbl::Game;
using skribbl::Player;
using skribbl::Turn;

Game::Game()
	: m_turn{ nullptr },
	m_state{ Game::State::WAITING }, m_url{ "/" }
{
}

IGame::IGamePtr IGame::Factory()
{
	return std::make_unique<Game>();
}

std::vector<std::shared_ptr<Player>> Game::leaderboard()
{
	std::vector<std::shared_ptr<Player>> leaderboard = m_players;
	std::ranges::sort(leaderboard, [](const std::shared_ptr<Player>& firstPlayer, const std::shared_ptr<Player>& secondPlayer)
		{
			return firstPlayer->getScore() > secondPlayer->getScore();
		}
	);
	return leaderboard;
}

Game::State Game::getNextState(State currentState)
{
	return static_cast<State>(static_cast<int>(currentState) + 1);
}

void Game::start(crow::SimpleApp& app)
{
	m_turn = std::make_shared<Turn>();

	m_state = Game::State::FIRST_ROUND;

	while (m_state != Game::State::GAME_OVER)
	{

		for (std::shared_ptr<Player> player : m_players)
		{
			m_turn->reset(player);
			app.route_dynamic(m_url + "/remove")(
				[this](const crow::request& req)
				{
					crow::json::rvalue json = crow::json::load(req.body);
					std::string playerName = json["playerName"].s();

					this->removePlayer(playerName);
					return crow::response(200);
				}
			);
		}

		m_state = getNextState(m_state);

		if (m_players.size() == 0)
			m_state = Game::State::GAME_OVER;
	}
}

bool Game::addPlayer(const std::string& name)
{
	if (m_players.size() < kMaxPlayersNumber)
	{
		m_players.push_back(std::make_shared<Player>(name));
		return true;
	}
	return false;
}

std::string Game::getState() const
{
	switch (m_state)
	{
	case Game::State::WAITING:
		return "Waiting";

	case Game::State::FIRST_ROUND:
		return "First Round";

	case Game::State::SECOND_ROUND:
		return "Second Round";

	case Game::State::THIRD_ROUND:
		return "Third Round";

	case Game::State::FOURTH_ROUND:
		return "Fourth Round";

	case Game::State::GAME_OVER:
		return "Game Over";
	}
}

void Game::setUrl(std::string lobbyCode)
{
	m_url += lobbyCode;
}

void Game::removePlayer(const std::string& name)
{
	std::erase_if(m_players, [&name](const std::shared_ptr<Player>& player)
		{
			return player->getName() == name;
		});
}
