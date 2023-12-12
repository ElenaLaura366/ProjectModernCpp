#include "Routing.h"

#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>

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

void Routing::SendAnswer(const std::string& answer)
{
	auto response = cpr::Put(
		cpr::Url{ m_url + "/answer" },
		cpr::Payload{
			{ "lobbyCode",  std::to_string(m_lobbyCode)},
			{ "playerName", m_playerName },
			{ "answer", answer }
		}
	);
	if (response.status_code == 200 || response.status_code == 201) {
		std::cout << "Submited answer :)\n";
	}
	else {
		std::cout << "There was a problem submiting the answer :(\n";
	}
}

void Routing::SendDrawing(const DrawingConfig& drawing)
{

}

void Routing::ExitGame()
{
	auto response = cpr::Put(
	    cpr::Url{ "http://localhost:18080/remove" },
	    cpr::Payload{
	        {"lobbyCode",  std::to_string(m_lobbyCode) },
	        { "playerName", m_playerName }
	    }
	);
	if (response.status_code == 200 || response.status_code == 201) {
	    std::cout << "exited :)\n";
	}
	else {
	    std::cout << "no exited the answer :(\n";
	}
}
