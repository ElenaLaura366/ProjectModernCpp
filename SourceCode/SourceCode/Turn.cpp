module turn;
using skribbl::Turn;
using skribbl::WordHandler;
using skribbl::Player;

import <numeric>;

Turn::Turn()
	: m_playerDrawing{ nullptr },
	m_wordHandler{ nullptr }
{

}

Turn::Turn(const std::shared_ptr<Player> player)
{
	m_playerDrawing = player;
	m_wordHandler = std::make_shared<WordHandler>("wordsFile.txt");
}


Turn::Turn(Turn&& other) noexcept
	: m_playerDrawing{ std::move(other.m_playerDrawing) },
	m_wordHandler{ std::move(other.m_wordHandler) },
	m_answerTimestamps{ std::move(other.m_answerTimestamps) }
{
}

Turn& Turn::operator=(Turn&& other) noexcept
{
	if (this != &other)
	{
		m_playerDrawing = std::move(other.m_playerDrawing);
		m_wordHandler = std::move(other.m_wordHandler);
		m_answerTimestamps = std::move(other.m_answerTimestamps);
	}
	return *this;
}

void Turn::setPlayerDrawing(const std::shared_ptr<Player> player)
{
	m_playerDrawing = player;
}

void Turn::setAllGuessed(bool value)
{
	m_allGuessed = value;
}

void Turn::reset(std::shared_ptr<Player> player)
{
	m_playerDrawing = player;
	m_wordHandler->update();
	m_timer.pause();
}

int8_t Turn::scoreGuessingPlayer()
{
	std::chrono::seconds timeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(m_timer.getElapsedTime());
	uint8_t time = timeInSeconds.count();
	return time < 30 ? kMaxScore : (60 - time) * 100 / 30;
}

uint8_t Turn::avrageAnswerTime()
{
	return std::accumulate(m_answerTimestamps.begin(), m_answerTimestamps.end(), 0.0) / m_answerTimestamps.size();
}

int8_t Turn::scoreDrawingPlayer()
{
	if (m_answerTimestamps.size() != 0)
	{
		uint8_t avrageTime = avrageAnswerTime();
		return (60 - avrageTime) * 100 / 30;
	}
	else
		return (-1 * kMaxScore);
}

bool Turn::verifyGuess(const std::string& guess)
{
	if (guess == m_wordHandler->getWord())
	{
		std::chrono::seconds timeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(m_timer.getElapsedTime());
		uint8_t time = timeInSeconds.count();
		m_answerTimestamps.push_back(time);
		return true;
	}
	else
		return false;
}

bool Turn::isTurnOver() const
{
	return m_allGuessed || m_timer.isTimeUp();
}
