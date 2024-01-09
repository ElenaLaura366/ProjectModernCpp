#include "Game.h"

using skribbl::IGame;
using skribbl::Game;
using skribbl::Player;
using skribbl::Turn;
using skribbl::Answer;

Game::Game(skribbl::Database& db)
	: m_turn{ nullptr },
	m_playerGuessCount{ 0 },
	m_drawingPlayerPossition{ kMaxPlayersNumber },
	m_db{ db }
{
	m_players.reserve(kMaxPlayersNumber);
}

IGame::IGamePtr IGame::Factory(skribbl::Database& db)
{
	return std::make_unique<Game>(db);
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
	m_wordHandler = std::make_unique<WordHandler>(m_db);

	m_state = Game::State::FIRST_ROUND;

	m_drawingPlayerPossition = 0;
	m_wordHandler->Reset();
	m_turn->SetCurrentWord(m_wordHandler->GetWord());
	m_turn->Start();
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

void Game::SetDrawing(const std::string& drawing)
{
	m_drawing = drawing;
}

std::string Game::GetWord() const
{
	return m_wordHandler->GetWord();
}

std::string Game::GetDrawingPlayer() const
{
	return (m_drawingPlayerPossition < kMaxPlayersNumber) ? m_players[m_drawingPlayerPossition]->GetUsername() : "\0";
}

uint8_t Game::GetTime() const
{
	return m_turn->GetRemainingTime();
}

std::vector<Answer> Game::GetAnswers() const
{
	return m_answers;
}

std::string Game::GetDrawing() const
{
	return m_drawing;
}

std::string Game::GetState() const
{
	std::vector<std::string> states{ "Waiting" , "First Round","Second Round", "Third Round" , "Fourth Round", "Game Over" };
	return states[static_cast<int>(m_state)];
}

std::vector<std::pair<std::string, int16_t>> Game::GetPlayers()
{
	std::vector<std::pair<std::string, int16_t>> players;
	for (const auto& player : m_players)
	{
		players.push_back({ player->GetUsername(), player->GetScore() });
	}
	return players;
}

std::string Game::GetHint() const
{
	return "";
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
	m_playerGuessCount = 0;
}

void Game::HandleEndTurn()
{
	// this function is to be given to the timer as a callback so that is being called when the timer runs out

	m_players[m_drawingPlayerPossition]->UpdateScore(m_turn->ScoreDrawingPlayer());
	for (auto& player : m_players)
	{
		if (!player->HasGuessed())
		{
			player->UpdateScore(m_turn->GetMinimGuessingScore());
		}
	}

	m_drawingPlayerPossition++;
	if (m_drawingPlayerPossition == m_players.size())
	{
		m_state = GetNextState(m_state);

		if (m_state == Game::State::GAME_OVER)
		{
			//HandleEndGame();
			return;
		}
	}

	ResetPlayersGuessed();
	m_wordHandler->Reset();
	m_turn->SetCurrentWord(m_wordHandler->GetWord());
	m_turn->Reset();
}

void Game::HandleAllPlayersGuessed()
{
	if (m_playerGuessCount != m_players.size() - 1)
		return;

	HandleEndTurn();
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
				HandleAllPlayersGuessed();
				return true;
			}
		}
	}
	return false;
}