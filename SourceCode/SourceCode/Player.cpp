import player;
using skribbl::Player;

Player::Player()
	:m_username{ "-" },
	m_score{ 0 },
	m_guessed{ false }
{}

Player::Player(const std::string& username)
	:m_username{ std::move(username) },
	m_score{ 0 },
	m_guessed{ false }
{}

Player::Player(Player* player)
{
	m_guessed = player->getGuessed();
	m_score = player->getScore();
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

bool Player::getGuessed() const
{
	return m_guessed;
}

void Player::setUsername(const std::string& username)
{
	this->m_username = std::move(username);
}

void Player::setGuessed()
{
	this->m_guessed = true;
}

void Player::setScore(int16_t score)
{
	this->m_score = score;
};

