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

Player::Player(const Player& player)
	: m_username{ player.GetName() },
	m_score{ player.GetScore() },
	m_guessed{ player.GetGuessed() }
{}

Player& skribbl::Player::operator=(const Player & other)
{
	if (this != &other)
	{
		m_username = other.m_username;
		m_score = other.m_score;
		m_guessed = other.m_guessed;
	}
	return *this;
}

int16_t Player::GetScore() const
{
	return this->m_score;
}

std::string Player::GetName() const
{
	return this->m_username;
}

bool Player::GetGuessed() const
{
	return m_guessed;
}

void Player::SetUsername(const std::string& username)
{
	this->m_username = std::move(username);
}

void Player::SetGuessed()
{
	this->m_guessed = true;
}

void Player::SetScore(int16_t score)
{
	this->m_score = score;
};

