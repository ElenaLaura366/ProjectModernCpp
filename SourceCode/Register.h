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

inline auto createUser(const std::string& filename) {
	return sql::make_storage(
		filename,
		sql::make_table(
			"Products",
			sql::make_column("username", &User::m_username, sql::primary_key()),
			sql::make_column("password", &User::m_password),
			sql::make_column("nrGamesPlayed", &User::m_nrGamesPlayed)
		)
	);
}

using UserTable = decltype(createUser(""));

namespace skribbl
{
	class Register
	{
	public:
		Register(UserTable& userTable);
	private:
		UserTable& m_db;
	};
}