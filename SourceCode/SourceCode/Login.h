#pragma once
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

namespace skribbl
{
	class Login
	{
	public:
		Login();
		Login(const std::string& username, const std::string& password);
		std::string getUsername() const;
		std::string getPassword() const;
		void setUsername(const std::string& username);
		void setPassword(const std::string& password);
	private:
		std::string m_username;
		std::string m_password;
	};
}