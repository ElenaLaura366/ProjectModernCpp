module;
export module game;

export import igame;

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

	private:
		std::vector<std::shared_ptr<Player>> m_players;
		std::shared_ptr<Turn> m_turn;
		State m_state;
	};
}