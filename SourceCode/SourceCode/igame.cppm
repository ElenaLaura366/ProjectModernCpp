module;
export module igame;

export import turn;
export import <algorithm>;

namespace skribbl
{
	export class IGame
	{
	public:
		IGame() = default;
		virtual std::vector<Player* > leaderboard() = 0;
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual void addPlayer(Player* player) = 0;
		virtual bool isRunning() const = 0;
	};
}