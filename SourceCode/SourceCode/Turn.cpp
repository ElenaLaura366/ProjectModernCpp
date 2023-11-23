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
	// TO DO timer init
}

//Turn::Turn(const Turn& other)
//{
//	delete m_playerDrawing;
//	delete m_wordHandler;
//
//	m_playerDrawing = other.m_playerDrawing;
//	m_wordHandler = other.m_wordHandler;
//	m_answerTimestamps = other.m_answerTimestamps;
//}
//
//Turn& Turn::operator=(const Turn& other)
//{
//	if (this != &other)
//	{
//		delete m_playerDrawing;
//		delete m_wordHandler;
//		m_playerDrawing = other.m_playerDrawing;
//		m_wordHandler = other.m_wordHandler;
//		m_answerTimestamps = other.m_answerTimestamps;
//	}
//	return *this;
//}

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
	// TO DO reset timer
}

int8_t Turn::scoreGuessingPlayer()
{
	uint8_t time = 16; // get curent time from class Timer
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
		uint8_t time = 1; // TO DO timer.getTime()
		m_answerTimestamps.push_back(time);
		return true;
	}
	else
		return false;
}

bool Turn::isTurnOver() const
{
	return m_allGuessed /* OR time's up*/;
}
