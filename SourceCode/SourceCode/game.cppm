module;
export module game;

import igame;
import player;
import turn;
import <string>;
import <vector>;
import <memory>;
import <algorithm>;

namespace skribbl
{

	export class Game : public IGame
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

		void start() override;
		bool addPlayer(const std::string& name) override;
		
		std::vector<std::shared_ptr<Player>> leaderboard() override;
		std::string getState() const override;
		
	private:
		std::vector<std::shared_ptr<Player>> m_players;
		std::shared_ptr<Turn> m_turn;
		State m_state;
	};
}