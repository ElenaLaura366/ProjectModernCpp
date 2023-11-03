module;
export module igame;

export import <vector>;
export import <algorithm>;
export import player;
export import turn;

namespace skribbl
{
	export class IGame
	{
	public:
		IGame() = default;
		virtual std::vector<Player* > leaderboard() = 0;
		virtual void start() = 0;
		virtual bool isRunning() const = 0;
	};
}