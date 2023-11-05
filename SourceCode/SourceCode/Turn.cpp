import turn;
using skribbl::Turn;
using skribbl::WordGenerator;
using skribbl::Player;

Turn::Turn()
{}


Turn::Turn(Player* const player)
{
	m_playerDrawing = player;
	m_wordGenerator = new WordGenerator("wordsFile.txt");
	// TO DO timer init
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

int8_t Turn::score()
{
	// score for the players that guess
	uint8_t time = 16; // get curent time from class Timer
	return time < 30 ? k_maxScore : (60 - time) * 100 / 30;
}

bool Turn::verifyGuess(const std::string& guess)
{
	return guess == m_wordGenerator->getWord();
}

bool Turn::isTurnOver()
{
	// has time run out
	return false;
}
