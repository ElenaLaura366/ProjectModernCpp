import player;
using skribbl::Player;

Player::Player()
	:m_username("-"),
	m_score(0),
	m_isDrawing(false),
	m_guessed(false)
{}

Player::Player(const std::string& username)
	:m_username(std::move(username)),
	m_score(0),
	m_isDrawing(false),
	m_guessed(false)
{}

Player::Player(Player* player)
{
	m_guessed = player->getGuessed();
	m_score = player->getScore();
	m_isDrawing = player->getIsDrawing();
	m_guessed = player->getGuessed();
}

int16_t Player::getScore() const
{
	return this->m_score;
}

std::string Player::getName() const
{
	return this->m_username;
}

bool Player::getIsDrawing() const
{
	return this->m_isDrawing;
}

bool Player::getGuessed() const
{
	return m_guessed;
}

void Player::setUsername(const std::string& username)
{
	this->m_username = std::move(username);
}

void Player::setIsDrawing(bool isDrawing)
{
	this->m_isDrawing = isDrawing;
}

void Player::setGuessed(bool guessed)
{
	this->m_guessed = guessed;
}

void Player::setScore(int16_t score)
{
	this->m_score = score;
};

