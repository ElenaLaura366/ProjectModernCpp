import player;
using skribbl::Player;

Player::Player()
	:m_username{ "-" },
	m_score{ 0 }
{}

Player::Player(const std::string& username)
	:m_username{ std::move(username) },
	m_score{ 0 }
{}

Player::Player(const Player& player)
	: m_username{ player.GetUsername() },
	m_score{ player.GetScore() }
{}

Player& skribbl::Player::operator=(const Player & other)
{
	if (this != &other)
	{
		m_username = other.m_username;
		m_score = other.m_score;
	}
	return *this;
}

int16_t Player::GetScore() const
{
	return this->m_score;
}

std::string Player::GetUsername() const
{
	return this->m_username;
}

void Player::SetUsername(const std::string& username)
{
	this->m_username = std::move(username);
}

void Player::UpdateScore(int8_t score)
{
	this->m_score += score;
};

