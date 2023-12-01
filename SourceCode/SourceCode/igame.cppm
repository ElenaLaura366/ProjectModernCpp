module;
export module igame;

import player;
import <memory>;
import <vector>;
import <string>;

namespace skribbl
{

	export class IGame
	{
	public:
		using IGamePtr = std::shared_ptr<class IGame>;

	public:
		static IGamePtr Factory();
		virtual ~IGame() = default;
		virtual std::vector <std::shared_ptr<Player>> leaderboard() = 0;
		virtual void start() = 0;
		virtual void addPlayer(const std::string& name) = 0;
		virtual bool verifyGuess(const std::string& guess) = 0;
		virtual void setLobbyUrl(uint16_t lobbyCode) = 0;
		virtual std::string getUrl() const = 0;
		virtual uint16_t getLobbyCode() const = 0;
	};
}