#pragma once

#include <string>
#include <vector>
#include <memory>
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
		static const uint8_t kMaxPlayersNumber = 8;

	public:
		Game();
		~Game() = default;
		Game(const Game& otherGame) = delete;
		Game& operator=(const Game& otherGame) = delete;
		Game(Game&& otherGame) noexcept = default;
		Game& operator=(Game&& otherGame) noexcept = default;

		void Start() override;
		void RemovePlayer(const std::string& name) override;

		bool AddPlayer(const std::string& name) override;
		std::vector<std::pair<std::string, int16_t>> GetLeaderboard() override;
		std::string GetState() const override;

		State GetNextState(State currentState);

	private:
		std::vector<Player::PlayerPtr> m_players;
		Turn::TurnPtr m_turn;
		State m_state;
	};
}