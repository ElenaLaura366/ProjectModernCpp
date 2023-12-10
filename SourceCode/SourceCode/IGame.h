#pragma once

#include <crow.h>
#include <memory>
#include <vector>
#include <string>

import player;

namespace skribbl
{

	class IGame
	{
	public:
		using IGamePtr = std::unique_ptr<class IGame>;

		static IGamePtr Factory();

	public:
		virtual ~IGame() = default;

		virtual void start(crow::SimpleApp& app) = 0;
		virtual void setUrl(std::string lobbyCode) = 0;
		virtual void removePlayer(const std::string& name) = 0;

		virtual bool addPlayer(const std::string& name) = 0;
		virtual std::vector<std::shared_ptr<Player>> leaderboard() = 0;
		virtual std::string getState() const = 0;
	};
}