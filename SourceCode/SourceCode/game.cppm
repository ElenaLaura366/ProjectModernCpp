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
			LOADING,
			FIRST_ROUND,
			SECOND_ROUND,
			THIRD_ROUND,
			FOURTH_ROUND,
			GAME_OVER
		};

	public:
		Game();
		~Game() = default;
		Game(const Game& otherGame) = delete;
		Game& operator=(const Game& otherGame) = delete;
		Game(Game&& otherGame) noexcept = default;
		Game& operator=(Game&& otherGame) noexcept = default;

		std::vector<std::shared_ptr<Player>> leaderboard() override;
		void start() override;
		void addPlayer(const std::string& name) override;
		bool verifyGuess(const std::string& guess) override;
		std::string getUrl() const;
		void setLobbyUrl(int lobbyCode);
		bool lobbyExists(int lobbyCode);


	private:
		std::vector<std::shared_ptr<Player>> m_players;
		std::shared_ptr<Turn> m_turn;
		State m_state;
		std::string m_url;
		std::vector<int> m_lobbyCodes;
	};
}