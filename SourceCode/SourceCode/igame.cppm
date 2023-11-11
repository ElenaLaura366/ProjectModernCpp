module;
export module igame;

export import turn;
export import <algorithm>;
export import <memory>;

namespace skribbl
{
	export using IGamePtr = std::shared_ptr<class IGame>;

	export class IGame
	{
	public:
		static IGamePtr Factory();
		virtual ~IGame() = default;
		virtual std::vector<Player* > leaderboard() = 0;
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual void addPlayer(Player* player) = 0;
		virtual bool isRunning() const = 0;
	};
}