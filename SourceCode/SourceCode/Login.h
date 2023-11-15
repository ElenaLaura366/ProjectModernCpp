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

		bool verifyParola(const std::string& password) const;
		bool verifyUsername(const std::string& username) const;
		bool verifyLogin(const std::string& username, const std::string& password) const;

		static auto getTableDefinition() {
			return sql::make_table("Login",
				sql::make_column("username", &Login::m_username, sql::primary_key()),
				sql::make_column("password", &Login::m_password)
			);
		}

	private:
		std::string m_username;
		std::string m_password;
	};
}