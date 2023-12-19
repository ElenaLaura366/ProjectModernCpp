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

	CROW_ROUTE(m_app, "/login")
		.methods(crow::HTTPMethod::PUT)(
			[this](const crow::request& req)
			{
				return GetLogin(req);
			}
	);


	CROW_ROUTE(m_app, "/register")
		.methods(crow::HTTPMethod::PUT)(
			[this](const crow::request& req)
			{
				return GetRegister(req);
			}
	);

	CROW_ROUTE(m_app, "/create_lobby")
		.methods(crow::HTTPMethod::PUT)(
			[this](const crow::request& req)
			{
				return CreateLobby(req);
			}
	);

	CROW_ROUTE(m_app, "/join_lobby")
		.methods(crow::HTTPMethod::PUT)(
			[this](const crow::request& req)
			{
				return JoinLobby(req);
			}
	);

	CROW_ROUTE(m_app, "/start")
		.methods(crow::HTTPMethod::PUT)(
			[this](const crow::request& req)
			{
				return StartGame(req);
			}
	);

	CROW_ROUTE(m_app, "/drawing_player")
		.methods(crow::HTTPMethod::GET)(
			[this](const crow::request& req)
			{
				return GetDrawingPlayer(req);
			}
	);

	CROW_ROUTE(m_app, "/send_answer")
		.methods(crow::HTTPMethod::PUT)(
			[this](const crow::request& req)
			{
				return ProcessAnswer(req);
			}
	);

	CROW_ROUTE(m_app, "/get_answers")
		.methods(crow::HTTPMethod::GET)(
			[this](const crow::request& req)
			{
				return GetAnswers(req);
			}
	);

	CROW_ROUTE(m_app, "/send_drawing")
		.methods(crow::HTTPMethod::PUT)(
			[this](const crow::request& req)
			{
				return ProcessDrawing(req);
			}
	);

	CROW_ROUTE(m_app, "/get_drawing")
		.methods(crow::HTTPMethod::GET)(
			[this](const crow::request& req)
			{
				return GetDrawing(req);
			}
	);

	CROW_ROUTE(m_app, "/get_time")
		.methods(crow::HTTPMethod::GET)(
			[this](const crow::request& req)
			{
				return GetTime(req);
			}
	);

	CROW_ROUTE(m_app, "/remove")
		.methods(crow::HTTPMethod::PUT)(
			[this](const crow::request& req)
			{
				return RemovePlayer(req);
			}
	);

	CROW_ROUTE(m_app, "/leaderboard")
		.methods(crow::HTTPMethod::GET)(
			[this](const crow::request& req)
			{
				return GetGameLeaderboard(req);
			}
	);

	CROW_ROUTE(m_app, "/game_state")
		.methods(crow::HTTPMethod::PUT)(
			[this](const crow::request& req)
			{
				return GetGameState(req);
			}
	);

	m_app.port(18080).multithreaded().run();
}

crow::response Routing::JoinLobby(const crow::request& req)
{
	uint16_t lobbyCode = std::stoi(req.url_params.get("lobbyCode"));

	if (m_games.find(lobbyCode) == m_games.end())
		return crow::response(404, "Lobby not found!");

	std::string playerName = req.url_params.get("playerName");
	if (m_games[lobbyCode]->AddPlayer(playerName))
	{
		crow::json::wvalue jsonResponse;
		jsonResponse["lobbyCode"] = lobbyCode;
		return crow::response(201, jsonResponse);
	}
	else
		return crow::response(409, "Lobby full!");
}

crow::response Routing::StartGame(const crow::request& req)
{
	crow::json::rvalue json = crow::json::load(req.body);
	uint16_t lobbyCode = json["lobbyCode"].u();

	m_games[lobbyCode]->Start();

	return crow::response(204);
}

crow::response Routing::CreateLobby(const crow::request& req)
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

	std::string playerName = req.url_params.get("playerName");
	m_games[lobbyCode]->AddPlayer(playerName);

	crow::json::wvalue jsonResponse;
	jsonResponse["lobbyCode"] = lobbyCode;
	return crow::response(201, jsonResponse);
}

crow::response Routing::GetGameLeaderboard(const crow::request& req)
{
	crow::json::rvalue json = crow::json::load(req.body);
	uint16_t lobbyCode = json["lobbyCode"].u();
	std::vector<std::pair<std::string, int16_t>> leaderboard = m_games[lobbyCode]->GetLeaderboard();

	std::vector<crow::json::wvalue> results;
	for (const auto& comp : leaderboard)
	{
		results.push_back(crow::json::wvalue{
			{"playerName", comp.first},
			{"score", comp.second}
			});
	}
	return crow::json::wvalue{ results };
}

crow::response Routing::RemovePlayer(const crow::request& req)
{
	uint16_t lobbyCode = std::stoi(req.url_params.get("lobbyCode"));
	std::string playerName = req.url_params.get("playerName");

	m_games[lobbyCode]->RemovePlayer(playerName);
	return crow::response(204);
}

crow::response Routing::ProcessAnswer(const crow::request& req)
{
	uint16_t lobbyCode = std::stoi(req.url_params.get("lobbyCode"));
	std::string playerName = req.url_params.get("playerName");
	std::string answer = req.url_params.get("answer");

	m_games[lobbyCode]->AddAnswer(playerName, answer);

	crow::json::wvalue jsonResponse;
	jsonResponse["playerName"] = playerName;
	jsonResponse["answer"] = answer;
	if (true/*m_games[lobbyCode]->VerifyAnswer(playerName, answer)*/)
		jsonResponse["hasGuessed"] = true;
	else
		jsonResponse["hasGuessed"] = false;
	return crow::response(200, jsonResponse);
}

crow::response skribbl::Routing::ProcessDrawing(const crow::request& req)
{
	return crow::response();
}

crow::response skribbl::Routing::GetDrawing(const crow::request& req)
{
	return crow::response();
}

crow::response skribbl::Routing::GetAnswers(const crow::request& req)
{
	uint16_t lobbyCode = std::stoi(req.url_params.get("lobbyCode"));

	std::vector<crow::json::wvalue> answers_json;
	auto answers = m_games[lobbyCode]->GetAnswers();
	if (answers.size() == 0)
		return crow::response(204);
	for (const auto& answer : answers)
	{
		answers_json.push_back(crow::json::wvalue{
			{"playerName", answer.playerName},
			{"answer", answer.answer}
			});
	}
	return crow::json::wvalue{ answers_json };
}

crow::response skribbl::Routing::GetDrawingPlayer(const crow::request& req)
{
	uint16_t lobbyCode = std::stoi(req.url_params.get("lobbyCode"));

	auto drawingPlayer = "player"; // m_games[lobbyCode].GetDrawingPlayer();

	crow::json::wvalue jsonResp;
	jsonResp["playerName"] = drawingPlayer;
	return crow::response(200, jsonResp);
}

crow::response Routing::GetGameState(const crow::request& req)
{
	crow::json::rvalue json = crow::json::load(req.body);
	uint16_t lobbyCode = json["lobbyCode"].u();

	return crow::response(200, m_games[lobbyCode]->GetState());
}

crow::response Routing::GetLogin(const crow::request& req)
{

	std::string password = req.url_params.get("password");
	std::string username = req.url_params.get("username");
	if (username == "admin" && password == "123")
		return crow::response(200);
	return crow::response(400);
}

crow::response skribbl::Routing::GetRegister(const crow::request& req)
{
	std::string password = req.url_params.get("password");
	std::string username = req.url_params.get("username");

	// check if there is any other person with the same username in database
	// add to the database

	return crow::response(200);
}

crow::response skribbl::Routing::GetTime(const crow::request& req)
{
	uint16_t lobbyCode = std::stoi(req.url_params.get("lobbyCode"));

	uint8_t seconds = 3; //m_games[lobbyCode]->GetTime();

	crow::json::wvalue jsonResp;
	jsonResp["seconds"] = seconds;

	return crow::response(200, jsonResp);
}
