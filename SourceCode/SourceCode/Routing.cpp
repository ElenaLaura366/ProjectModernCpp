#include "Routing.h"
using namespace skribbl;

void skribbl::Routing::run()
{
	/*
	-----------------------------------------------------------------------------------------------------------------
	
										-> HTTP RESPONSE STATUS CODES <-
	
		~This comment is provided for a better understanding of the standard/custom responses that the code uses~

		~For the sake of easier reading, the template will look something like:~ 
		Type of response:
			[response status code]
			*A small description.

		_none_ is used for no code


		Information: 
		
			_none_

		Successful:
		
			200
			*Ok. The request succeeded.
			
			201
			*Created. The request succeded and a new resorce was created.

		Redirection messages:

			_none_

		Client error:

			404
			*Not Found. The server cannot find the requested resource.

			409
			*Conflict. Request conflicts with the current state of the server. 
			*(ex: a lobby is full)

		Server error:

			503:
			*Service Unavailable. The server is not ready to handle the request.
			*(ex: server full; maximum number of games that can hold is reached)

		Custom:

			_none_

		
		~For more you can go to: 
		https://developer.mozilla.org/en-US/docs/Web/HTTP/Status#browser_compatibility 
		https://http.dev/status
		~

	-----------------------------------------------------------------------------------------------------------------
	*/



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

	std::unordered_map<uint16_t, IGame::IGamePtr> games; //the lobby code is the key and the game is the value;

	CROW_ROUTE(m_app, "/create_lobby")(
		[&games](const crow::request& req)
		{
			if (games.size() == kmaxGamesSupported)
				return crow::response(503, "Server full!");

			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_int_distribution<uint32_t> distr(kMinLobbyCode, kMaxLobbyCode);

			uint16_t lobbyCode = distr(eng);
			while (games.find(lobbyCode) != games.end())
				lobbyCode = distr(eng);

			games[lobbyCode] = IGame::Factory();

			crow::json::rvalue json = crow::json::load(req.body);
			std::string playerName = json["playerName"].s();
			games[lobbyCode]->addPlayer(playerName);

			crow::json::wvalue jsonResponse;
			jsonResponse["lobbyCode"] = lobbyCode;
			return crow::response(201, jsonResponse);
		}
		);

	CROW_ROUTE(m_app, "/join_lobby")(
		[&games](const crow::request& req)
		{
			crow::json::rvalue json = crow::json::load(req.body);
			uint16_t lobbyCode = json["lobbyCode"].u();

			if (games.find(lobbyCode) == games.end())
				return crow::response(404, "Lobby not found!");

			std::string playerName = json["playerName"].s();
			if (games[lobbyCode]->addPlayer(playerName))
			{
				crow::json::wvalue jsonResponse;
				jsonResponse["lobbyCode"] = lobbyCode;
				return crow::response(201, jsonResponse);
			}
			else
				return crow::response(409, "Lobby full!");
		}
		);

	CROW_ROUTE(m_app, "/start")(
		[&games, this](const crow::request& req)
		{
			/* when you press the start button the game will start*/
			crow::json::rvalue json = crow::json::load(req.body);
			uint16_t lobbyCode = json["lobbyCode"].u();

			games[lobbyCode]->start(this->m_app);

			return crow::response(200);
		}
	);
	
	m_app.port(18080).multithreaded().run();
	
}
