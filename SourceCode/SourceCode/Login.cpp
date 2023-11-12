#include "Login.h"

skribbl::Login::Login() :m_username("-"), m_password("-")
{};

skribbl::Login::Login(const std::string& username, const std::string& password)
	: m_username(username), m_password(password) {
}
