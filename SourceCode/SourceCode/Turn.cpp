module turn;
using skribbl::Turn;
using skribbl::WordHandler;

Turn::Turn()
	: 
	m_wordHandler{ nullptr }
{

}

Turn::Turn(Turn&& other) noexcept
	:
	m_wordHandler{ std::move(other.m_wordHandler) },
	m_answerTimestamps{ std::move(other.m_answerTimestamps) }
{
}

Turn& Turn::operator=(Turn&& other) noexcept
{
	if (this != &other)
	{
		
		m_wordHandler = std::move(other.m_wordHandler);
		m_answerTimestamps = std::move(other.m_answerTimestamps);
	}
	return *this;
}

void Turn::Reset()
{
	m_timer.Pause();
}

int8_t Turn::ScoreGuessingPlayer()
{
	std::chrono::seconds timeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(m_timer.GetElapsedTime());
	uint8_t time = timeInSeconds.count();
	return time < 30 ? kMaxScore : (60 - time) * 100 / 30;
}

uint8_t Turn::AvrageAnswerTime()
{
	return std::accumulate(m_answerTimestamps.begin(), m_answerTimestamps.end(), 0.0) / m_answerTimestamps.size();
}

int8_t Turn::ScoreDrawingPlayer()
{
	if (m_answerTimestamps.size() != 0)
	{
		uint8_t avrageTime = AvrageAnswerTime();
		return (60 - avrageTime) * 100 / 30;
	}
	else
		return (-1 * kMaxScore);
}

bool Turn::VerifyGuess(const std::string& guess)
{
	if (guess == m_wordHandler->GetWord())
	{
		std::chrono::seconds timeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(m_timer.GetElapsedTime());
		uint8_t time = timeInSeconds.count();
		m_answerTimestamps.push_back(time);
		return true;
	}
	else
		return false;
}

bool Turn::IsOver() const
{
	return m_timer.IsTimeUp();
}
