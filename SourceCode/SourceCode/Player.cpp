import player;
using skribbl::Player;

Player::Player()
	:m_username{ "-" },
	m_score{ 0 }
{
	// empty
}

Player::Player(const std::string& username)
	:m_username{ std::move(username) },
	m_score{ 0 }
{
	// empty
}

Player::Player(const Player& player)
	: m_username{ player.GetUsername() },
	m_score{ player.GetScore() }
{
	// empty
}

Player& Player::operator=(const Player & other)
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
	return m_score;
}

std::string Player::GetUsername() const
{
	return m_username;
}

void Player::SetUsername(const std::string& username)
{
	m_username = std::move(username);
}

void Player::UpdateScore(int8_t score)
{
	m_score += score;
}

void Player::setGuessed(bool guessed)
{
	m_guessed = guessed;
}

bool Player::HasGuessed() const
{
	return m_guessed;
}
;

