#pragma once
#include <string>
#include <optional>
#include "Register.h"

namespace skribbl
{
	class Login
	{
	public:
		Login(UserTable& userTable);
		//~Login();
		std::optional<User> authenticateUser(const std::string& username, const std::string& password);
	private:
		UserTable& m_db;
	};
}