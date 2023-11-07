import turn;
using skribbl::Turn;
using skribbl::WordGenerator;
using skribbl::Player;

Turn::Turn()
	: m_playerDrawing{ nullptr },
	m_wordGenerator{ nullptr }
{}


Turn::Turn(Player* const player)
	: m_playerDrawing{ player }
{
	m_wordGenerator = new WordGenerator("wordsFile.txt");
	// TO DO timer init
}

Turn::Turn(const Turn& other)
{
	delete m_playerDrawing;
	delete m_wordGenerator;

	m_playerDrawing = other.m_playerDrawing;
	m_wordGenerator = other.m_wordGenerator;
	m_avrageAnswerTime = other.m_avrageAnswerTime;
}

Turn& Turn::operator=(const Turn& other)
{
	if (this != &other)
	{
		delete m_playerDrawing;
		delete m_wordGenerator;
		m_playerDrawing = other.m_playerDrawing;
		m_wordGenerator = other.m_wordGenerator;
		m_avrageAnswerTime = other.m_avrageAnswerTime;
	}
	return *this;
}

Turn::Turn(Turn&& other) noexcept
	: m_playerDrawing{ other.m_playerDrawing },
	m_wordGenerator{ other.m_wordGenerator },
	m_avrageAnswerTime {other.m_avrageAnswerTime}
{
	other.m_playerDrawing = nullptr;
	other.m_wordGenerator = nullptr;
	other.m_avrageAnswerTime = 0;
}

Turn& Turn::operator=(Turn&& other) noexcept
{
	if (this != &other)
	{
		delete m_playerDrawing;
		delete m_wordGenerator;

		m_playerDrawing = other.m_playerDrawing;
		other.m_playerDrawing = nullptr;
		m_wordGenerator = other.m_wordGenerator;
		other.m_wordGenerator = nullptr;
		m_avrageAnswerTime = other.m_avrageAnswerTime;
		other.m_avrageAnswerTime = 0;
	}
	return *this;
}

Turn::~Turn()
{
	delete m_playerDrawing;
	delete m_wordGenerator;
}

void Turn::reset(Player* player)
{
	m_playerDrawing = player;
	m_wordGenerator->update();
	// TO DO reset timer
}

int8_t Turn::scoreGuessingPlayer()
{
	uint8_t time = 16; // get curent time from class Timer
	return time < 30 ? k_maxScore : (60 - time) * 100 / 30;
}

int8_t Turn::scoreDrawingPlayer()
{
	return m_avrageAnswerTime == 0 ? (-1 * k_maxScore) : (60 - m_avrageAnswerTime) * 100 / 30;
}

bool Turn::verifyGuess(const std::string& guess)
{
	std::string cuv = m_wordGenerator->getWord();
	return guess == cuv;
}

bool Turn::isTurnOver()
{
	// has time run out
	return false;
}
