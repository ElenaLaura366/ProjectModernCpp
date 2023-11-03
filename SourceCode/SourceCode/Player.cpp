import player;
using skribbl::Player;

Player::Player()
	:m_username("-"),
	m_score(0),
	m_isDrawing(false),
	m_guessed(false)
{}

Player::Player(std::string username)
	:m_username(username),
	m_score(0),
	m_isDrawing(false),
	m_guessed(false)
{}

int16_t Player::getScore() const
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

bool Player::getGuessed()
{
	return m_guessed;
}

void Player::setUsername(std::string username)
{
	this->m_username = username;
}

void Player::setIsDrawing(bool isDrawing)
{
	this->m_isDrawing = isDrawing;
}

void Player::setGuessed(bool guessed)
{
	this->m_guessed = guessed;
}

/*void Player::updateScore(int16_t score)
{
	this->m_score = score;
};*/

