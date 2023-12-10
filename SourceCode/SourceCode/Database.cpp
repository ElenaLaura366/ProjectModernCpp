#include "Database.h"

skribbl::Database::Database(Storage& db)
	: m_db{ db }
{}

void skribbl::Database::syncSchema()
{
	m_db.sync_schema();
}

bool skribbl::Database::checkUserExists(const std::string& username)
{
	auto user = m_db.get_all<User>(sql::where(sql::c(&User::m_username) == username));
	return !user.empty();
}

void skribbl::Database::createNewUser(const std::string& username, const std::string& password)
{
	m_db.insert(User{ -1, username, password, 0 });
}

std::optional<User> skribbl::Database::authenticateUser(const std::string& username, const std::string& password)
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

void skribbl::Database::addGameHistory(int id, int gameId, int poits)
{
    m_db.insert(GameHistory{ -1, id, gameId, poits });
}
