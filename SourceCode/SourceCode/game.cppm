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
		~Game();
		Game(const Game& otherGame);
		Game& operator=(const Game& otherGame);
		Game(Game&& otherGame) noexcept;
		Game& operator=(Game&& otherGame) noexcept;

		std::vector<Player* > leaderboard() override;
		void start() override;
		void addPlayer(const std::string& name) override;
		bool verifyGuess(const std::string& guess) override;

	private:
		std::vector<Player* > m_players;
		Turn* m_turn;
		State m_state;
	};
}