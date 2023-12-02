#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "Database.h"

namespace skribbl
{
	class Register
	{
	public:
		Register(Storage& registerTable);
		bool checkUserExists(const std::string& username);
		void createNewUser(const std::string& username, const std::string& password);
	private:
		Storage& m_db;
	};
}