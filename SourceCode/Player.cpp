#include "Player.h"

Player::Player()
	:m_username("-"),
	m_score(0),
	m_isDrawing(false),
	m_guesed(false)
{}

Player::Player(std::string userName)
	:m_username(userName),
	m_score(0),
	m_isDrawing(false),
	m_guesed(false)
{}

uint16_t Player::getScore()
{
	return this->m_score;
}

std::string Player::getName()
{
	return this->m_username;
}

bool Player::getIsDrawing()
{
	return this->m_isDrawing;
}

bool Player::getGuesed()
{
	return m_guesed;
}

void Player::setUserName(std::string userName)
{
	this->m_username = userName;
}

void Player::setIsDrawing(bool isDrawing)
{
	this->m_isDrawing = isDrawing;
}

void Player::setGuesed(bool guesed)
{
	this->m_guesed = guesed;
}

void Player::updateScore(int score)
{
	this->m_score = score;
};

