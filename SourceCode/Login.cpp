#include "Login.h"

skribbl::Login::Login() :m_username("-"), m_password("-")
{};

skribbl::Login::Login(const std::string& username, const std::string& password)
	: m_username(username), m_password(password) {
}

std::string skribbl::Login::getUsername() const
{
	return m_username;
}

std::string skribbl::Login::getPassword() const
{
	return m_password;
}

void skribbl::Login::setUsername(const std::string& username)
{
	this->m_username = username;
}

void skribbl::Login::setPassword(const std::string& password)
{
	this->m_password = password;
}

bool skribbl::Login::verifyParola(const std::string& password) const
{
	return this->m_password == password;
}

bool skribbl::Login::verifyUsername(const std::string& username) const
{
	return this->m_username == username;
}

bool skribbl::Login::verifyLogin(const std::string& username, const std::string& password) const
{
	return verifyParola(password) && verifyUsername(username);
}
