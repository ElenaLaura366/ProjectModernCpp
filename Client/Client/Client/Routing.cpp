#include "Routing.h"

#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <QDebug>
#include <QString>

Routing::Routing()
	: m_url{ "http://localhost:18080" }
	, m_playerName{ "" }
	, m_lobbyCode{ "" }
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
	return answerList;
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

	return result;
}

QString Routing::GetWord() const
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/get_word" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
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
	if (response.status_code == 200 || response.status_code == 201)
		return QString::fromLatin1(response.text.data());
	return QString("No Server Answer");
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
		if (response.text == m_playerName)
			return true;
	}
	else
		// exception ?
		return false;
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
		m_isDrawing = false;
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
		m_isDrawing = true;
		return true;
	}

	return false;
}

std::vector<QString> Routing::GetPlayers()
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/players" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);

	if (response.status_code != 200) 
	{
		return std::vector<QString>();
	}

	std::vector<QString> players;
	auto jsonResponse = crow::json::load(response.text);
	for (const auto& playerName : jsonResponse) 
	{
		std::string mess = std::string(playerName["playerName"]);
		players.push_back(QString::fromLatin1(mess.data()));
	}

	return players;
}
