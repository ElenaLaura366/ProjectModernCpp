#pragma once

#include <algorithm>
#include <ranges>
#include "IGame.h"

import player;
import turn;


namespace skribbl
{

	class Game : public IGame
	{
	public:

		enum class State
		{
			WAITING,
			FIRST_ROUND,
			SECOND_ROUND,
			THIRD_ROUND,
			FOURTH_ROUND,
			GAME_OVER


		};

	public:
		static constexpr uint8_t kMaxPlayersNumber{ 8 };

	public:
		Game(skribbl::Database& m_db);
		~Game() = default;
		Game(const Game& otherGame) = delete;
		Game& operator=(const Game& otherGame) = delete;
		Game(Game&& otherGame) noexcept = default;
		Game& operator=(Game&& otherGame) noexcept = default;

		void Start() override;
		void RemovePlayer(const std::string& name) override;
		void ResetPlayersGuessed();
		bool VerifyAnswer(const std::string& name,const std::string& answer) override;
		bool AddPlayer(const std::string& name) override;
		void AddAnswer(const std::string& name, const std::string& answer) override;
		void SetDrawing(const std::string& drawing) override;
		void HandleAllPlayersGuessed();
		void HandleEndTurn();
		void AddCustomWord(const std::string& word) override;

		std::string GetWord() const override;
		std::string GetDrawingPlayer() const override;
		uint8_t GetTime() const override;
		std::vector <Answer> GetAnswers() const override;
		std::string GetDrawing() const override;
		std::vector<std::pair<std::string, int16_t>> GetLeaderboard() const override;
		std::string GetState() const override;
		std::vector<std::pair<std::string, int16_t>> GetPlayers() override;
		std::string GetHint() const override;
		bool HasStarted() const override;

		State GetNextState(State currentState);
		
	private:
		std::vector<Player::PlayerPtr> m_players;
		Turn::TurnPtr m_turn;
		State m_state;
		uint8_t m_playerGuessCount;
		std::vector<Answer> m_answers;
		std::string m_drawing;
		uint8_t m_drawingPlayerPossition;
		skribbl::Database& m_db;
		WordHandler::WordHandlerPtr m_wordHandler;
	};
}