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

	bool SendLogin(const std::string& username, const std::string& password);
	bool SendRegister(const std::string& username, const std::string& password);
	bool SendJoinLobby(std::string lobbyCode);
	bool SendCreateLobby(std::string& username);
	bool SendAnswer(const std::string& answer);
	void SendDrawing(const DrawingConfig& drawing);
	uint8_t GetTime(const std::string& answer);
	std::vector<QString> GetAnswers();
	bool GetDrawing();
	QString GetWord() const;
	bool IsDrawingPlayer();
	bool ExitGame();
	uint16_t GetLobbyCode() const;


private:
	std::string m_url;
	std::string m_playerName;
	uint16_t m_lobbyCode;
};

