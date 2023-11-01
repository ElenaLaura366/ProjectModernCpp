export module game;

import igame;


class Game : public IGame
{
public:
	Game();
	~Game();
	Game(const Game& otherGame);
	Game& operator=(const Game& otherGame);
	std::vector<Player* > leaderboard() override;
	void start() override;
	bool isRunning() const override;

private:
	std::vector<Player* > m_players;
	Turn* m_turn;
	bool m_isRunning;
};