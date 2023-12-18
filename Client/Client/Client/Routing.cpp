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

void Routing::SetPlayerName(const std::string& playerName)
{
	m_playerName = playerName;
}

void Routing::SetLobbyCode(uint16_t lobbyCode)
{
	m_lobbyCode = lobbyCode;
}

bool Routing::SendAnswer(const std::string& answer)
{
	auto response = cpr::Put(
		cpr::Url{ m_url + "/send_answer" },
		cpr::Parameters{
			{ "lobbyCode",  std::to_string(m_lobbyCode)},
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

std::vector<QString> Routing::GetAnswers()
{
	cpr::Response response = cpr::Get(
		cpr::Url{ m_url + "/get_answers" }, 
		cpr::Parameters{ { {"lobbyCode"}, std::to_string(m_lobbyCode) } }
	);

	if (response.status_code == 204)
		return std::vector<QString>();

	std::vector<QString> answerList;
	auto answers = crow::json::load(response.text);
	for (auto answer : answers)
	{
		std::string mess = std::string(answer["playerName"]);
		std::string message = mess + ": " + std::string(answer["answer"]);
		QString text = QString::fromStdString(message);
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
			{ "lobbyCode", std::to_string(m_lobbyCode) },
			{ "playerName", m_playerName },
		}
	);

	auto answers = crow::json::load(response.text);

	return true;
}

void Routing::SendDrawing(const DrawingConfig& drawing)
{
	std::vector<int> dr{ {1, 2, 3} };
	auto response = cpr::Put(
		cpr::Url{ m_url + "/send_drawing" },
		cpr::Payload{
			{ "lobbyCode", std::to_string(m_lobbyCode) },
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
			{ "lobbyCode",  std::to_string(m_lobbyCode)},
			{ "playerName", m_playerName },
		}
	);
	if (response.status_code == 200 || response.status_code == 201) {
		m_lobbyCode = 0;
		return true;
	}
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

	if (response.status_code == 200 || response.status_code == 201){
		auto resp = crow::json::load(response.text);
		m_playerName = std::string(resp["playerName"]);
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
		m_playerName = std::string(resp["playerName"]);
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
		m_lobbyCode = resp["lobbyCode"].u();
		return true;
	}

	return false;
}
