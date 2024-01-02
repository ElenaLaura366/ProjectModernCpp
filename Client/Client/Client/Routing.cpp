#include "Routing.h"

#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <QDebug>
#include <QString>

Routing::Routing()
	: m_url{ "http://localhost:18080" },
	m_playerName{ "" },
	m_lobbyCode{ 0 }
{
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
		std::cout << "Submited answer :)\n";
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

	auto resp = crow::json::load(response.text);
	return QString::number(resp["seconds"].u());
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

bool Routing::GetDrawing()
{
	std::vector<int> dr{ {1, 2, 3} };
	auto response = cpr::Get(
		cpr::Url{ m_url + "/get_drawing" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
			{ "playerName", m_playerName },
		}
	);

	auto answers = crow::json::load(response.text);

	return true;
}

QString Routing::GetWord() const
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/get_drawing" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);

	auto resp = crow::json::load(response.text);
	std::string strWord = std::string(resp["word"]);
	return QString::fromStdString(strWord);
}

QString Routing::GetRound() const
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/game_state" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);

	auto resp = crow::json::load(response.text);
	return QString::fromStdString(std::string(resp["state"]));
}

bool Routing::IsDrawingPlayer()
{
	auto response = cpr::Get(
		cpr::Url{ m_url + "/drawing_player" },
		cpr::Parameters{
			{ "lobbyCode", m_lobbyCode },
		}
	);

	auto resp = crow::json::load(response.text);
	if (std::string(resp["playerName"]) == m_playerName)
		return true;

	return false;

}

void Routing::SendDrawing(const DrawingConfig& drawing)
{
	std::vector<int> dr{ {1, 2, 3} };
	auto response = cpr::Put(
		cpr::Url{ m_url + "/send_drawing" },
		cpr::Payload{
			{ "lobbyCode", m_lobbyCode },
			{ "playerName", m_playerName },
			//{ "drawing", std::to_string(dr)}
		}
	);
}

bool Routing::ExitGame()
{
	auto response = cpr::Put(
		cpr::Url{ m_url + "/remove" },
		cpr::Parameters{
			{ "lobbyCode",  m_lobbyCode},
			{ "playerName", m_playerName },
		}
	);
	if (response.status_code == 200 || response.status_code == 201) {
		m_lobbyCode = "x";
		return true;
	}
	return false;
}

std::string Routing::GetLobbyCode() const
{
    return m_lobbyCode;
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
		auto resp = crow::json::load(response.text);
		m_playerName = resp["playerName"].s();
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
		auto resp = crow::json::load(response.text);
		m_playerName = resp["playerName"].s();
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
		auto resp = crow::json::load(response.text);
		m_lobbyCode = resp["lobbyCode"].u();
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
		auto resp = crow::json::load(response.text);
		m_lobbyCode = resp["lobbyCode"].s();
		return true;
	}

	return false;
}
