module;
export module game;

export import igame;

namespace skribbl
{
	export class Game : public IGame
	{
	public:
		Game();
		~Game();
		Game(const Game& otherGame);
		Game& operator=(const Game& otherGame);
		Game(Game&& otherGame) noexcept;
		Game& operator=(Game&& otherGame) noexcept;

		std::vector<Player* > leaderboard() override;
		void start() override;
		void stop() override;
		void addPlayer(const std::string& name) override;
		bool isRunning() const override;

	private:
		std::vector<Player* > m_players;
		Turn* m_turn;
		bool m_isRunning;
	};
}