#pragma once
#include <string>
#include <optional>
#include "Database.h"

namespace skribbl
{
	class Login
	{
	public:
		Login(Storage& login);
		//~Login();
		std::optional<User> authenticateUser(const std::string& username, const std::string& password);
	private:
		Storage& m_db;
	};
}