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

Player::Player(std::shared_ptr<Player> player)
{
	if (player != nullptr) {
		this->m_username = player->m_username;
		this->m_score = player->m_score;
		this->m_guessed = player->m_guessed;
	}
	else {
		this->m_username = "-";
		this->m_score = 0;
		this->m_guessed = false;
	}
}

Player::Player(const Player& player)
	: m_username{ player.getName() },
	m_score{ player.getScore() },
	m_guessed{ player.getGuessed() }
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

