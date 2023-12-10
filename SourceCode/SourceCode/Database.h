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

struct GameHistory {
	int m_id;
	int m_id_player;
	int m_id_game;
	int m_points;
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
			"GameHistory",
			sql::make_column("id", &GameHistory::m_id, sql::primary_key().autoincrement()),
			sql::make_column("user", &GameHistory::m_id_player),
			sql::make_column("game", &GameHistory::m_id_game),
			sql::make_column("points", &GameHistory::m_points)
		)
	);
}

using Storage = decltype(createDatabase(""));

namespace skribbl
{
	class Database
	{
	public:
		Database(Storage& db);
		//~Database();

		void syncSchema();
		bool checkUserExists(const std::string& username);
		void createNewUser(const std::string& username, const std::string& password);
		std::optional<User> authenticateUser(const std::string& username, const std::string& password);
		void addGameHistory(int id,int gameId, int poits);
	private:
		Storage& m_db;
	};
}
