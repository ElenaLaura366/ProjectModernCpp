#include "Game.h"

using skribbl::IGame;
using skribbl::Game;
using skribbl::Player;
using skribbl::Turn;
using skribbl::Answer;

Game::Game()
	: m_turn{ nullptr },
	m_playerGuessCount{ 0 }
{
	m_players.reserve(kMaxPlayersNumber);
}

IGame::IGamePtr IGame::Factory()
{
	return std::make_unique<Game>();
}

std::vector<std::pair<std::string, int16_t>> Game::GetLeaderboard() const
{
	std::vector<std::pair<std::string, int16_t>> leaderboard;
	leaderboard.reserve(m_players.size());

	for (const auto& player : m_players)
	{
		leaderboard.push_back({ player->GetUsername(), player->GetScore() });
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
			m_playerGuessCount = 0;
			m_turn->Reset();
			while (!m_turn->IsOver())
			{
				if (m_players.size() - 1 == m_playerGuessCount)
					m_turn->SetAllPlayersGuessed();
			}
			player->UpdateScore(m_turn->ScoreDrawingPlayer());
			ResetPlayersGuessed();
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

void Game::AddAnswer(const std::string& name, const std::string& answer)
{
	m_answers.emplace_back(name, answer);
}

std::string Game::GetWord() const
{
	return std::string();
}

std::string Game::GetDrawingPlayer() const
{
	return std::string();
}

uint8_t Game::GetTime() const
{
	return m_turn->GetRemainingTime();
}

std::vector<Answer> Game::GetAnswers() const
{
	return m_answers;
}

std::string Game::GetState() const
{
	std::vector<std::string> states{ "Waiting" , "First Round","Second Round", "Third Round" , "Fourth Round", "Game Over" };
	return states[static_cast<int>(m_state)];
}

void Game::RemovePlayer(const std::string& name)
{
	std::erase_if(m_players, [&name, this](const Player::PlayerPtr& player)
		{
			if (player->GetUsername() == name)
			{
				if (player->HasGuessed())
					m_playerGuessCount--;
				return true;
			}
			return false;
		});
}

void Game::ResetPlayersGuessed()
{
	for (auto& player : m_players)
	{
		player->setGuessed(false);
	}
}

bool Game::VerifyAnswer(const std::string& name, const std::string& answer)
{
	if (m_turn->VerifyGuess(answer))
	{
		for (auto& player : m_players)
		{
			if (player->GetUsername() == name)
			{
				player->UpdateScore(m_turn->ScoreGuessingPlayer());
				m_playerGuessCount++;
				return true;
			}
		}
	}
	return false;
}
