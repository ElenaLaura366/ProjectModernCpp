#include "Game.h"

using skribbl::IGame;
using skribbl::Game;
using skribbl::Player;
using skribbl::Turn;

Game::Game()
	: m_turn{ nullptr }
{
}

IGame::IGamePtr IGame::Factory()
{
	return std::make_unique<Game>();
}

std::vector<std::pair<std::string, int16_t>> Game::GetLeaderboard()
{
	std::vector<std::pair<std::string, int16_t>> leaderboard;
	leaderboard.reserve(m_players.size());

	for (const auto& player : m_players)
	{
		leaderboard.push_back({ player->GetName(), player->GetScore() });
	}

	std::ranges::sort(leaderboard, [](const std::pair<std::string, int16_t>& firstPlayer, const std::pair<std::string, int16_t>& secondPlayer)
		{
			return firstPlayer.second > secondPlayer.second;
		}
	);

	return leaderboard;
}

Game::State Game::GetNextState(State currentState)
{
	return static_cast<State>(static_cast<int>(currentState) + 1);
}

void Game::Start()
{
	m_turn = std::make_unique<Turn>();

	m_state = Game::State::FIRST_ROUND;

	while (m_state != Game::State::GAME_OVER)
	{

		for (Player::PlayerPtr& player : m_players)
		{
			m_turn->Reset();
		}

		m_state = GetNextState(m_state);

		if (m_players.size() == 0)
			m_state = Game::State::GAME_OVER;
	}
}

bool Game::AddPlayer(const std::string& name)
{
	if (m_players.size() < kMaxPlayersNumber)
	{
		m_players.push_back(std::make_unique<Player>(name));
		return true;
	}
	return false;
}

std::string Game::GetState() const
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

void Game::RemovePlayer(const std::string& name)
{
	std::erase_if(m_players, [&name](const Player::PlayerPtr& player)
		{
			return player->GetName() == name;
		});
}

void skribbl::Game::VerifyAnswer(const std::string& name, const std::string& answer)
{
	if (m_turn->VerifyGuess(answer)) {
		for (auto& player : m_players)
		{
			if (player->GetName() == name) {
				player->UpdateScore(m_turn->ScoreGuessingPlayer());
				player->SetGuessed();
			}
		}
	}
}
