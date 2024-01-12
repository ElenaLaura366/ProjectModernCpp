module turn;
using skribbl::Turn;

Turn::Turn(const std::function<void()>& callbackEndTurn, const std::function<void()>& callbackHint)
{
	m_timer = std::make_unique<Timer>(callbackEndTurn, callbackHint);
}

Turn::Turn(Turn&& other) noexcept
	: m_answerTimestamps{ std::move(other.m_answerTimestamps) }
{
	// empty
}

Turn& Turn::operator=(Turn&& other) noexcept
{
	if (this != &other)
	{
		m_answerTimestamps = std::move(other.m_answerTimestamps);
	}
	return *this;
}

void Turn::Start()
{
	m_timer->Start(m_currentWord.size() / 2);
}

void Turn::Reset()
{
	m_timer->Restart(m_currentWord.size() / 2);
	m_answerTimestamps.clear();
}

int8_t Turn::ScoreGuessingPlayer() const
{
	std::chrono::seconds timeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(m_timer->GetElapsedTime());
	uint8_t time = timeInSeconds.count();
	return time < 30 ? kMaxScore : (60 - time) * 100 / 30;
}

int8_t Turn::GetMinimGuessingScore() const
{
	return (-1 * kMaxScore) / 2;
}

uint8_t Turn::AvrageAnswerTime() const
{
	return std::accumulate(m_answerTimestamps.begin(), m_answerTimestamps.end(), 0.0) / m_answerTimestamps.size();
}

int8_t Turn::ScoreDrawingPlayer() const
{
	if (m_answerTimestamps.size() != 0)
	{
		uint8_t avrageTime = AvrageAnswerTime();
		return (60 - avrageTime) * 100 / 60;
	}
	else
		return (-1 * kMaxScore);
}

bool Turn::VerifyGuess(const std::string& guess)
{
	if (guess == m_currentWord)
	{
		std::chrono::seconds timeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(m_timer->GetElapsedTime());
		uint8_t time = timeInSeconds.count();
		m_answerTimestamps.push_back(time);
		return true;
	}
	else
		return false;
}

bool Turn::IsOver() const
{
	return m_timer->IsTimeUp();
}

uint8_t Turn::GetRemainingTime() const
{
	return m_timer->GetRemainingTime();
}

void Turn::SetCurrentWord(const std::string& word)
{
	m_currentWord = word;
}
