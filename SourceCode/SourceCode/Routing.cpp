#include "Routing.h"
using namespace skribbl;

void skribbl::Routing::Run()
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

			204
			*There is no content to send for this request, but the headers may be usefull.

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

	CROW_ROUTE(m_app, "/create_lobby")(
		[this](const crow::request& req)
		{
			return CreateLobby(req);
		}
		);

	CROW_ROUTE(m_app, "/join_lobby")(
		[this](const crow::request& req)
		{
			return JoinLobby(req);
		}
		);

	CROW_ROUTE(m_app, "/start")(
		[this](const crow::request& req)
		{
			return StartGame(req);
		}
	);
	CROW_ROUTE(m_app, "/remove")(
		[this](const crow::request& req)
		{
			return RemovePlayer(req);
		}
	);

	CROW_ROUTE(m_app, "/leaderboard")(
		[this](const crow::request& req)
		{
			return GetGameLeaderboard(req);
		}
	);
	
	m_app.port(18080).multithreaded().run();
	
}

crow::response skribbl::Routing::JoinLobby(const crow::request& req)
{
	crow::json::rvalue json = crow::json::load(req.body);
	uint16_t lobbyCode = json["lobbyCode"].u();

	if (m_games.find(lobbyCode) == m_games.end())
		return crow::response(404, "Lobby not found!");

	std::string playerName = json["playerName"].s();
	if (m_games[lobbyCode]->AddPlayer(playerName))
	{
		crow::json::wvalue jsonResponse;
		jsonResponse["lobbyCode"] = lobbyCode;
		return crow::response(201, jsonResponse);
	}
	else
		return crow::response(409, "Lobby full!");
}

crow::response skribbl::Routing::StartGame(const crow::request& req)
{
	crow::json::rvalue json = crow::json::load(req.body);
	uint16_t lobbyCode = json["lobbyCode"].u();

	m_games[lobbyCode]->Start();

	return crow::response(204);
}

crow::response skribbl::Routing::CreateLobby(const crow::request& req)
{
	if (m_games.size() == kmaxGamesSupported)
		return crow::response(503, "Server full!");

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<uint32_t> distr(kMinLobbyCode, kMaxLobbyCode);

	uint16_t lobbyCode = distr(eng);
	while (m_games.find(lobbyCode) != m_games.end())
		lobbyCode = distr(eng);

	m_games[lobbyCode] = IGame::Factory();

	crow::json::rvalue json = crow::json::load(req.body);
	std::string playerName = json["playerName"].s();
	m_games[lobbyCode]->AddPlayer(playerName);

	crow::json::wvalue jsonResponse;
	jsonResponse["lobbyCode"] = lobbyCode;
	return crow::response(201, jsonResponse);
}

crow::response skribbl::Routing::GetGameLeaderboard(const crow::request& req)
{
	crow::json::rvalue json = crow::json::load(req.body);
	uint16_t lobbyCode = json["lobbyCode"].u();
	std::vector<std::pair<std::string, int16_t>> leaderboard = m_games[lobbyCode]->GetLeaderboard();

	return crow::response(200);
}

crow::response skribbl::Routing::RemovePlayer(const crow::request& req)
{
	crow::json::rvalue json = crow::json::load(req.body);
	uint16_t lobbyCode = json["lobbyCode"].u();
	std::string playerName = json["playerName"].s();

	m_games[lobbyCode]->RemovePlayer(playerName);
	return crow::response(204);
}