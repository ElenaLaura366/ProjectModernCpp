export module igame;

export import "Turn.h";
export import <vector>;
export import <algorithm>;

export class IGame
{
public:
	IGame() = default;
	virtual std::vector<Player* > leaderboard() = 0;
	virtual void start() = 0;
	virtual bool isRunning() const = 0;
};