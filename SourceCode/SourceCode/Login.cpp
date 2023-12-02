#include "Login.h"

skribbl::Login::Login(Storage& login)
	: m_db{ login }
{}

std::optional<User> skribbl::Login::authenticateUser(const std::string& username, const std::string& password)
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
