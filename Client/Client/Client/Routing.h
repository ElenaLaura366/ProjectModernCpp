#pragma once

#include <cpr/cpr.h>
#include <crow.h>

#include "User.h"
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
	QString GetTime();
	std::vector<QString> GetAnswers();
	bool GetDrawing();
	QString GetHint() const;
	QString GetWord() const;
	QString GetRound() const;
	std::string GetLobbyCode() const;
	bool IsDrawingPlayer();
	bool ExitGame();
	std::vector<User> GetPlayers(const std::string& lobbyCode);

private:
	std::string m_url;
	std::string m_playerName;
	std::string m_lobbyCode;
};