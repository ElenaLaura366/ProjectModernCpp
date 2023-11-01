export module game;

import igame;


export class Game : public IGame
{
public:
	Game();
	std::vector<Player* > leaderboard() override;
	void start() override;
	bool isRunning() const override;

private:
	std::vector<Player* > m_players;
	Turn* m_turn;
	bool m_isRunning;
};