#include "Routing.h"
using namespace skribbl;

void skribbl::Routing::run(IGame::IGamePtr& game)
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

	CROW_ROUTE(m_app, "/create_lobby")(
		[&game, &lobbyCodes](const crow::request& req)
		{
			crow::json::rvalue json = crow::json::load(req.body);
			uint16_t lobbyCode = json["lobbyCode"].u();
			if (std::find(lobbyCodes.begin(), lobbyCodes.end(), lobbyCode) == lobbyCodes.end())
			{
				game->setLobbyUrl(lobbyCode);
				lobbyCodes.push_back(lobbyCode);
			}
			else
				return crow::response(400, "Lobby already exists");

			std::string playerName = json["playerName"].s(); //here i get the name from the json
			game->addPlayer(playerName);
			return crow::response(200);
		}
		);
	CROW_ROUTE(m_app, "/start" /*THIS IS NOT COMPLETE, I'LL MAKE IT WORK*/)(
		[&game]()
		{
			/* when you press the start button the game will start*/
			game->start();
			return crow::response(200);
		}
		);




	m_app.port(18080).multithreaded().run();
}
