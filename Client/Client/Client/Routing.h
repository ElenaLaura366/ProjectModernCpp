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

	void SendAnswer(const std::string& answer);
	void SendDrawing(const DrawingConfig& drawing);
	void ExitGame();

private:
	std::string m_url;
	std::string m_playerName;
	uint16_t m_lobbyCode;
};
