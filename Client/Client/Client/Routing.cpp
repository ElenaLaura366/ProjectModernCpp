#include "Routing.h"

#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <QDebug>

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
		cpr::Url{ m_url + "/answer" },
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

void Routing::SendDrawing(const DrawingConfig& drawing)
{
	std::vector<int> dr{ {1, 2, 3} };
	auto response = cpr::Put(
		cpr::Url{ m_url + "/drawing" },
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

	if (response.status_code == 200 || response.status_code == 201) 
		return true;

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

	if (response.status_code == 200 || response.status_code == 201)
		return true;
	
	return false;
}