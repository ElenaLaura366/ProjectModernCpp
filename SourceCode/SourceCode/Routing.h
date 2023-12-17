#pragma once
#include <crow.h>
#include <random>
#include <vector>
#include <unordered_map>
#include "IGame.h"

namespace skribbl
{
	class Routing
	{
	public:
		Routing() = default;
		~Routing() = default;
		Routing(const Routing& other) = delete;
		Routing& operator=(const Routing& other) = delete;
		Routing(Routing&& other) noexcept = delete;
		Routing& operator=(Routing&& other) noexcept = delete;
		
		void Run();

		static const uint16_t kMinLobbyCode = 10000;
		static const uint16_t kMaxLobbyCode = 65535;
		static const uint16_t kmaxGamesSupported = 8;

	private:
		crow::response JoinLobby(const crow::request& req);
		crow::response StartGame(const crow::request& req);
		crow::response CreateLobby(const crow::request& req);
		crow::response GetGameLeaderboard(const crow::request& req);
		crow::response RemovePlayer(const crow::request& req);
		crow::response ProcessAnswer(const crow::request& req);
		crow::response GetAnswers(const crow::request& req);
		crow::response GetGameState(const crow::request& req);
		crow::response GetLogin(const crow::request& req);
		crow::response GetRegister(const crow::request& req);

	private:
		crow::SimpleApp m_app;
		std::unordered_map<uint16_t, IGame::IGamePtr> m_games;
	};
}