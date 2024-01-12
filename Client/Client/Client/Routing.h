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

	bool SendStartGame();
	bool SendLogin(const std::string& username, const std::string& password);
	bool SendRegister(const std::string& username, const std::string& password);
	bool SendJoinLobby(std::string lobbyCode);
	bool SendCreateLobby(std::string& username);
	bool SendAnswer(const std::string& answer);
	bool SendGameHistory(const std::vector<GameHistory>& gameHistory);
	void SendDrawing(const DrawingConfig& drawing);
	bool GetIsDrawing() const;
	QString GetTime();
	std::vector<QString> GetAnswers();
	DrawingConfig GetDrawing();
	QString GetHint() const;
	QString GetWord() const;
	QString GetRound() const;
	QString GetPlayer() const;
	std::string GetLobbyCode() const;
	bool IsDrawingPlayer();
	bool ExitGame();
	std::vector<User> GetPlayers();
	std::vector<std::pair<QString, int16_t>> GetLeaderBoard();
	std::string GetPlayerName() const;
	std::vector<GameHistory> GetGamesHistory();
	void SendCustomWord(const std::string& word);

private:
	std::string m_url;
	std::string m_playerName;
	bool m_isDrawing;
	std::string m_lobbyCode;
};