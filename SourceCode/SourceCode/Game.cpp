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
	m_wordHandler = std::make_unique<WordHandler>(m_db);
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
	m_turn = std::make_unique<Turn>([this]() {HandleEndTurn(); }, [this]() {GetHint(); });

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
	return (m_drawingPlayerPossition < m_players.size()) ? m_players[m_drawingPlayerPossition]->GetUsername() : "\0";
}

uint8_t Game::GetTime() const
{
	return m_turn->GetRemainingTime();
}

const std::vector<Answer>& Game::GetAnswers() const
{
	return m_answers;
}

const std::string& Game::GetDrawing() const
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

std::vector<uint8_t> Game::GetHint() const
{
	return m_wordHandler->GenerateHint();
}

bool skribbl::Game::HasStarted() const
{
	return m_state != Game::State::WAITING;
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
	for (size_t i = 0; i < m_players.size(); i++)
	{
		if (!m_players[i]->HasGuessed() && i != m_drawingPlayerPossition)
		{
			m_players[i]->UpdateScore(m_turn->GetMinimGuessingScore());
		}
	}

	if (m_wordHandler->AreCustomWordsLeft())
	{
		m_wordHandler->UpdateCustomWordScore(m_turn->GetTurnScore());
	}

	m_drawingPlayerPossition++;
	if (m_drawingPlayerPossition == m_players.size())
	{
		m_state = GetNextState(m_state);
		m_drawingPlayerPossition = 0;
		if (m_state == Game::State::GAME_OVER)
		{
			HandleEndGame();
			return;
		}
	}

	ResetPlayersGuessed();
	m_wordHandler->Reset();
	m_turn->SetCurrentWord(m_wordHandler->GetWord());
	m_turn->Reset();
}

void skribbl::Game::HandleEndGame()
{
	m_db.AddGameHistory(GetPlayers());
	m_wordHandler->AddCustomWordsToDatabase(m_players.size());
}

void skribbl::Game::AddCustomWord(const std::string& word)
{
	m_wordHandler->AddCustomWord(word);
}

uint8_t skribbl::Game::GetNumberCustomWord()
{
	return m_wordHandler->GetNumberCustomWord();
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