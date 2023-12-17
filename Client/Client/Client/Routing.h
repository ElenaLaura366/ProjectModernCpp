#pragma once

#include <cpr/cpr.h>
#include <crow.h>

#include "DrawingAreaWidget.h";

class Routing
{
public:
	Routing();
	~Routing() = default;
	Routing(const Routing& other) = delete;
	Routing& operator=(const Routing& other) = delete;
	Routing(Routing&& other) noexcept = delete;
	Routing& operator=(Routing&& other) noexcept = delete;

	void SetPlayerName(const std::string& playerName);
	void SetLobbyCode(uint16_t lobbyCode);
	
	bool SendLogin(const std::string& username, const std::string& password);
	bool SendRegister(const std::string& username, const std::string& password);

	bool SendAnswer(const std::string& answer);
	std::vector<QString> GetAnswers();
	bool GetDrawing();
	void SendDrawing(const DrawingConfig& drawing);
	bool ExitGame();



private:
	std::string m_url;
	std::string m_playerName;
	uint16_t m_lobbyCode;
};

