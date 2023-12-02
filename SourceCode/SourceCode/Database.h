#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

struct User {
	int m_id;
	std::string m_username;
	std::string m_password;
	int m_nrGamesPlayed;
};

struct Word {
	int m_id;
	std::string m_name;
};

inline auto createDatabase(const std::string& filename) 
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Users",
			sql::make_column("id", &User::m_id, sql::primary_key().autoincrement()),
			sql::make_column("username", &User::m_username),
			sql::make_column("password", &User::m_password),
			sql::make_column("nrGamesPlayed", &User::m_nrGamesPlayed)
		),
		sql::make_table(
			"Words",
			sql::make_column("id", &Word::m_id, sql::primary_key().autoincrement()),
			sql::make_column("username", &Word::m_name)
		)
	);
}

class Database
{
};

