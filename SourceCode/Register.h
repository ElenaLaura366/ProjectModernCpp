#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

struct User {
	int id;
	std::string m_username;
	std::string m_password;
	int16_t m_nrGamesPlayed;
};

namespace skribbl
{
	class Register
	{
	public:
		Register();
	private:
		
	};
}