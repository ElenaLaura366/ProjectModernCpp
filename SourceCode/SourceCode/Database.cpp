#include "Database.h"

skribbl::Database::Database(Storage& db)
	: m_db{ db }
{}

void skribbl::Database::SyncSchema()
{
	m_db.sync_schema();
}

bool skribbl::Database::CheckUserExists(const std::string& username)
{
	auto user = m_db.get_all<User>(sql::where(sql::c(&User::m_username) == username));
	return !user.empty();
}

void skribbl::Database::CreateNewUser(const std::string& username, const std::string& password)
{
	m_db.insert(User{ -1, username, password, 0 });
}

std::optional<User> skribbl::Database::AuthenticateUser(const std::string& username, const std::string& password)
{
    auto users = m_db.get_all<User>(sql::where(sql::c(&User::m_username) == username));
    if (!users.empty())
    {
        const auto& user = users.front();
        if (user.m_password == password)
        {
            return user;
        }
    }
    return std::nullopt;
}

void skribbl::Database::AddGameHistory(int playerId, int gameId, int points)
{
	m_db.insert(GameHistory{ -1, playerId, gameId, points });
}
