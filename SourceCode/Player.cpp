#include "Player.h"

Player::Player()
	:m_username("-"),
	m_score(0),
	m_isDrawing(0)
{}

Player::Player(std::string userName)
	:m_username(userName),
	m_score(0),
	m_isDrawing(0)
{}

uint16_t Player::getScore()
{
	return this->m_score;
}

std::string Player::getName()
{
	return this->m_username;
}

void Player::setUserName(std::string userName)
{
	this->m_username = userName;
}
void Player::setIsDrawing(bool isDrawing)
{
	this->m_isDrawing = isDrawing;
};

