#include "Register.h"

skribbl::Register::Register(Storage& registerTable)
	: m_db{ registerTable }
{}

bool skribbl::Register::checkUserExists(const std::string& username)
{
	auto user = m_db.get_all<User>(sql::where(sql::c(&User::m_username) == username));
	return !user.empty();
}

void skribbl::Register::createNewUser(const std::string& username, const std::string& password)
{
	m_db.insert(User{ -1, username, password, 0 });
}
