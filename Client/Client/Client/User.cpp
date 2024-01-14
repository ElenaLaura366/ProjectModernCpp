#include "User.h"

User::User()
{
	m_username = "";
	m_isAdmin = false ;
	m_lobbyCode = std::nullopt;
}

void User::setUsername(const std::string& username)
{
	m_username = QString::fromUtf8(username.c_str());
}

void User::setLobbyCode(const std::string& lobbyCode)
{
	m_lobbyCode = QString::fromUtf8(lobbyCode.c_str());
}

void User::setAdmin()
{
	m_isAdmin = true;
}

QString User::getUsername() const
{
	return m_username;
}

std::optional<QString> User::getLobbyCode()
{
	return m_lobbyCode;
}

void User::SetGameHistory(const std::vector<GameHistory>& history)
{
	m_gamesHistory = std::move(history);
}

std::vector<GameHistory> User::GetGameHistory()
{
	return m_gamesHistory;
}

