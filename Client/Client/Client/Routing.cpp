#include "Routing.h"

#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <QDebug>
#include <QString>

Routing::Routing()
	//: m_url{ "http://localhost:18080" }
	: m_url{ "http://25.46.224.159:18080" }
	, m_playerName{ "Not_Initialized" }
	, m_lobbyCode{ "" }
	, m_isDrawing{ false }
{
	// empty
}


bool Routing::SendAnswer(const std::string& answer)
{
	auto response = cpr::Put(
		cpr::Url{ m_url + "/send_answer" },
		cpr::Parameters{
			{ "lobbyCode",  m_lobbyCode},
			{ "playerName", m_playerName },
			{ "answer", answer }
		}
	);
	if (response.status_code == 200 || response.status_code == 201) {
		auto resp = crow::json::load(response.text);
		auto our = response.text.find("true") != response.text.npos;

		return true;
	}
	return false;
}

bool Routing::SendGameHistory(const std::vector<GameHistory>& gameHistory)
{
	// send game history
	


	return false;
}

QString Routing::GetTime()
{
	cpr::Response response = cpr::Get(
		cpr::Url{ m_url + "/get_time" },
		cpr::Parameters{ { {"lobbyCode"}, m_lobbyCode } }
	);

	return QString::fromLatin1(response.text.data());
}

std::vector<QString> Routing::GetAnswers()
{
	cpr::Response response = cpr::Get(
		cpr::Url{ m_url + "/get_answers" },
		cpr::Parameters{ { {"lobbyCode"}, m_lobbyCode } }
	);

	if (response.status_code == 204)
		return std::vector<QString>();

	std::vector<QString> answerList;
	auto answers = crow::json::load(response.text);
	for (auto answer : answers)
	{
		std::string mess = std::string(answer["playerName"]);
		std::string message = mess + ": " + std::string(answer["answer"]);
		QString text = QString::fromLatin1(message.data());
		answerList.push_back(text);
	}
	return std::move(answerList);
}

DrawingConfig Routing::GetDrawing()
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/get_drawing" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);

	auto answers = crow::json::load(response.text);

	DrawingConfig result;
	if (response.text.size() == 0)
		return result;
	std::istringstream ss(response.text);
	std::string line;

	while (std::getline(ss, line, '/'))
	{
		std::vector<QPoint> points;
		std::istringstream lineStream(line);
		std::string pointX, pointY;

		while (lineStream >> pointX)
		{
			lineStream >> pointY;

			QPoint point(std::stoi(pointX), std::stoi(pointY));
			points.push_back(point);
		}

		result.push_back(points);
	}

	return std::move(result);
}

QString Routing::GetWord() const
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/get_word" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
			{ "playerName", m_playerName }
		}
	);
	return QString::fromLatin1(response.text.data());
}

QString Routing::GetHint() const
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/get_hint" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);

	return QString::fromLatin1(response.text.data());
}

QString Routing::GetRound() const
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/game_state" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);
	if (response.status_code == 200)
		return QString::fromLatin1(response.text.data());
	return QString("No Server Answer");
}

QString Routing::GetPlayer() const
{
	return  QString::fromUtf8(m_playerName.c_str());
}

bool Routing::IsDrawingPlayer()
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/drawing_player" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);

	if (response.status_code == 200 || response.status_code == 201) {
		if (response.text == m_playerName) {
			m_isDrawing = true;
			return true;
		}
		else {
			m_isDrawing = false;
			return false;
		}
	}
}

void Routing::SendDrawing(const DrawingConfig& drawing)
{
	std::string drawingStr;
	for (const auto& line : drawing)
	{
		for (const auto& point : line)
		{
			drawingStr.append(std::to_string(point.x()));
			drawingStr.append(" ");
			drawingStr.append(std::to_string(point.y()));
			drawingStr.append(" ");
		}
		drawingStr.append("/");
	}

	auto response = cpr::Put(
		cpr::Url{ m_url + "/send_drawing" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
			{ "drawing", drawingStr }
		}
	);
}

bool Routing::GetIsDrawing() const
{
	return m_isDrawing;
}

bool Routing::ExitGame()
{
	if (m_lobbyCode != "x") {

		auto response = cpr::Put(
			cpr::Url{ m_url + "/remove" },
			cpr::Parameters{
				{ "lobbyCode",  m_lobbyCode},
				{ "playerName", m_playerName },
			}
		);
		if (response.status_code == 204) {
			m_lobbyCode = "x";
			return true;
		}
	}
	return false;
}

std::string Routing::GetLobbyCode() const
{
	return m_lobbyCode;
}

bool Routing::SendStartGame()
{
	auto response = cpr::Put(
		cpr::Url{ m_url + "/start" },
		cpr::Parameters{
			{"lobbyCode", m_lobbyCode}
		}
	);

	if (response.status_code == 204)
		return true;
	return false;
}

bool Routing::SendLogin(const std::string& username, const std::string& password) {
	auto response = cpr::Put(
		cpr::Url{ m_url + "/login" },
		cpr::Parameters{
			{"username", username},
			{"password", password}
		}
	);

	if (response.status_code == 200 || response.status_code == 201) {
		m_playerName = response.text;
		return true;
	}

	return false;
}

bool Routing::SendRegister(const std::string& username, const std::string& password) {
	auto response = cpr::Put(
		cpr::Url{ m_url + "/register" },
		cpr::Parameters{
			{"username", username},
			{"password", password}
		}
	);

	if (response.status_code == 200 || response.status_code == 201) {
		m_playerName = response.text;
		return true;
	}

	return false;
}

bool Routing::SendJoinLobby(std::string lobbyCode)
{
	auto response = cpr::Put(
		cpr::Url{ m_url + "/join_lobby" },
		cpr::Parameters{
			{"lobbyCode", lobbyCode},
			{"playerName", m_playerName}
		}
	);

	if (response.status_code == 200 || response.status_code == 201) {
		m_lobbyCode = lobbyCode;
		return true;
	}

	return false;
}

bool Routing::SendCreateLobby(std::string& username)
{
	auto response = cpr::Put(
		cpr::Url{ m_url + "/create_lobby" },
		cpr::Parameters{
			{"playerName", username}
		}
	);

	if (response.status_code == 200 || response.status_code == 201) {
		m_lobbyCode = response.text;
		return true;
	}

	return false;
}

std::vector<User> Routing::GetPlayers()
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/players" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);

	if (response.status_code != 200)
	{
		return std::vector<User>();
	}

	std::vector<User> players;
	auto jsonResponse = crow::json::load(response.text);
	for (const auto& playerName : jsonResponse)
	{
		std::string mess = std::string(playerName["playerName"]);
		User user;
		user.setUsername(mess);
		players.push_back(user);
	}

	return std::move(players);
}

std::vector<std::pair<QString, int16_t>> Routing::GetLeaderBoard()
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/players" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);

	if (response.status_code != 200)
	{
		return std::vector<std::pair<QString, int16_t>>();
	}

	std::vector<std::pair<QString, int16_t>> leaderBoard;
	auto jsonResponse = crow::json::load(response.text);
	for (const auto& playerInfo : jsonResponse)
	{
		QString playerName = QString::fromLatin1(std::string(playerInfo["playerName"]).data());
		int16_t score = playerInfo["score"].i();
		leaderBoard.emplace_back(playerName, score);
	}

	return std::move(leaderBoard);
}

std::string Routing::GetPlayerName() const
{
	return m_playerName;
}

std::vector<GameHistory> Routing::GetGamesHistory()
{
	auto response = cpr::Get(
		cpr::Url{m_playerName + "/gamesHistory"}, 
		cpr::Parameters{
			{"username", m_playerName}
		}
	);

	if (response.status_code != 200)
	{
		return std::vector<GameHistory>();
	}

	auto jsonResponse = crow::json::load(response.text);
	std::vector<GameHistory> gameHistory;
	for (const auto& game : jsonResponse)
	{
		std::string gameId = std::string(game["playerName"]);
		std::string points = std::string(game["date"]);
		gameHistory.emplace_back(std::make_pair( gameId, points ));
	}

	return gameHistory;
}
