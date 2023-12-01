#include "Routing.h"
using namespace skribbl;

void skribbl::Routing::run()
{
	/*
	we need route for login/register
	-route for creating the url for the game with game lobby code
	-route for chat getting the words from users
	-route for drowing
	-route for displaying leaderboard in left of every player and players username with it to display 
	*/
	CROW_ROUTE(m_app, "/login")(
		[/*get's database for users*/]()
		{
			return crow::response(200);
		}
		);
	CROW_ROUTE(m_app, "/register")(
		[/*get's database for users*/]()
		{
			return crow::response(200);
		}
		);

	std::vector<uint16_t> lobbyCodes;
	std::vector<IGame::IGamePtr> games;

	CROW_ROUTE(m_app, "/create_lobby")(
		[&games, &lobbyCodes](const crow::request& req)
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_int_distribution<uint32_t> distr(kMinLobbyCode, kMaxLobbyCode);

			uint16_t lobbyCode = distr(eng);
			while (std::find(lobbyCodes.begin(), lobbyCodes.end(), lobbyCode) != lobbyCodes.end())
				lobbyCode = distr(eng);

			IGame::IGamePtr game = IGame::Factory();
			game->setLobbyUrl(lobbyCode);
			lobbyCodes.push_back(lobbyCode);
			games.push_back(game);

			crow::json::rvalue json = crow::json::load(req.body);
			std::string playerName = json["playerName"].s(); //here i get the name from the json
			game->addPlayer(playerName);

			return crow::response(200);
		}
		);

	CROW_ROUTE(m_app, "/join_lobby")(
		[&games, &lobbyCodes](const crow::request& req)
		{
			crow::json::rvalue json = crow::json::load(req.body);
			uint16_t lobbyCode = json["lobbyCode"].u();


			auto lobbyit = std::find(lobbyCodes.begin(), lobbyCodes.end(), lobbyCode);
			if (lobbyit == lobbyCodes.end())
				return crow::response(400, "Lobby not found!");

			std::string playerName = json["playerName"].s();
			games[std::distance(lobbyCodes.begin(), lobbyit)]->addPlayer(playerName);

			return crow::response(200);
		}
		);

	CROW_ROUTE(m_app, "/start")(
		[&games, &lobbyCodes](const crow::request& req)
		{
			/* when you press the start button the game will start*/
			crow::json::rvalue json = crow::json::load(req.body);
			uint16_t lobbyCode = json["lobbyCode"].u();

			auto lobbyit = std::find(lobbyCodes.begin(), lobbyCodes.end(), lobbyCode);
			games[std::distance(lobbyCodes.begin(), lobbyit)]->start();

			return crow::response(200);
		}
		);




	m_app.port(18080).multithreaded().run();
}
